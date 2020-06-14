#include "requestHandler.h"


ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}

void write_reply(char* reply)
{
	int r = open("reply", O_WRONLY);
	if(r < 0) perror("FIFO ERROR");
	write(r, reply, strlen(reply));
	close(r);
}

int count_char(char* string, char c)
{
	int r = 0;
	for(int i = 0; i < strlen(string); i++)
		if(string[i] == c) r++;
	return r;
}

void write_to_files(char *output, int id)
{
	char task_n[4];
	sprintf(task_n, "%d", id+1);
	int s = strlen(output);
	char size[10];
	sprintf(size, "%d", s);
	char *aux = (char*)malloc(sizeof(char)*60);
	strcat(aux,task_n);
	strcat(aux," ");
	strcat(aux, size);
	strcat(aux, "\n");
	int log = open("log", O_CREAT | O_APPEND | O_WRONLY, 0700);
	int idx = open("log.idx", O_CREAT | O_APPEND | O_WRONLY, 0700);
	write(idx, aux, strlen(aux));
	write(log, output, strlen(output));
	free(aux);
	close(log);
	close(idx);
}

void handle_alarm(int sig)
{
	kill(getpid(), SIGKILL);
}

void execute(char *cmds[], int n, int id)
{
	int fd[n][2];
	int pids[n];
	char *reply =(char*)malloc(sizeof(char) * 30);
	char aux[5];
	sprintf(aux,"%d", id+1);
	strcat(reply,"nova tarefa #");
	strcat(reply, aux);
	write_reply(reply);
	free(reply);
	//cria uma lista de pipes
	for(int i = 0; i < n; i++)
	{
		pipe(fd[i]);
	}
	int i;
	for(i = 0; i < n; i++)
	{
		pids[i] = fork();
		if(pids[i] < 0) perror("ERROR IN FORK");
		
		//Child
		else if(!pids[i])
		{
			int n_args = count_char(cmds[i], ' ') + 1;
			char *cmd = strtok(cmds[i], " ");
			char *args[n_args];
			int j = 0;
			while(cmd != NULL)
			{
				args[j] = cmd;
				printf("|%s|\n", args[j++]);
				cmd = strtok(NULL, " ");
			}
			args[j]=NULL;

			//First command
			if(i == 0)
			{
				if(dup2(fd[i][1], 1) < 0)
					perror("ERROR IN DUP");
			}
			//All commands except the first
			else
			{
				//reads from previous pipe
				if(dup2(fd[i-1][0], 0) < 0)
					perror("ERROR IN DUP1");

				//writes in next pipe
				if(dup2(fd[i][1], 1) < 0)
					perror("ERROR IN DUP2");
			}
			//close all copies of the pipes
			for(int k = 0; k < n; k++)
			{
				close(fd[k][0]);
				close(fd[k][1]);
			}
		
			if(execvp(args[0], args) < 0)
				perror("EXEC ERROR!\n");
			_exit(0);
		}
	}

//	Waits for all Children (dont know if needed yet);
	for(int k = 0; k < n; k++)
		waitpid(pids[k], NULL, 0);

	//Father reads the result from the last pipe
	for(int k = 0; k < n; k++)
	{
		if(k == n-1)
		{
			char* result =(char*) malloc(sizeof(char)*2048);
			char* aux =(char*)malloc(sizeof(char)*2048);
			close(fd[k][1]);
			if(dup2(fd[k][0], 0))
				perror("ERRO IN DUP3");
			close(fd[k][0]);			
			
			while(readln(0, aux))
			{
				strcat(result, aux);
				strcat(result, "\n");
			}
			write_to_files(result, id);
			free(result);
		}
		else
		{
			close(fd[k][0]);
			close(fd[k][1]);
		}
	}
/*	Waits for all Children (dont know if needed yet);
	for(int k = 0; k < n; k++)
		waitpid(pids[k], NULL, 0);*/

}

void parse_execute(Tasks *ts, int id, char* tmp)
{
	int n = count_char(tmp, '|') + 1;
	char *cmds[n];
	char *chain = strtok(tmp, "|");
	int j = 0;
	while(chain != NULL)
	{	
		cmds[j++] = chain;
		chain = strtok(NULL, "|");
	}
	if(ts->taskTime > 0)
	{
		alarm(ts->taskTime);
	}
	execute(cmds, n, id);
	ts->tasks[id].state = DEAD;
}

void execute_tasks(Tasks *ts, char* cmd)
{
	signal(SIGALRM, handle_alarm);
	int id = init_task(ts, cmd);
	char* tmp = strdup(ts->tasks[id].name);
	ts->tasks[id].state = ACTIVE;
	int i = 0;
	int pid = fork();
	if(!pid)
	{
		parse_execute(ts, id, tmp);
		_exit(0);
	}
	free(tmp);
	waitpid(-1, NULL, WNOHANG);
}

void show_finished(Tasks *ts)
{
	char *reply =(char*)malloc(sizeof(char)*1024);
	for(int i = 0; i < ts->size; i++)
	{
		if(ts->tasks[i].state == DEAD)
		{
			strcat(reply,"#");
			char id[3];
			sprintf(id, "%d", ts->tasks[i].id);
			strcat(reply,id);
			strcat(reply,", ");
			strcat(reply,ts->tasks[i].name);
			strcat(reply,"\n");
		}	
		
	}
	write_reply(reply);
	free(reply);
}

void show_active(Tasks *ts)
{
	char *reply =(char*)malloc(sizeof(char)*1024);
	strcat(reply, "NO TASKS RUNNING!");
	for(int i = 0; i < ts->size; i++)
	{
		if(ts->tasks[i].state == ACTIVE)
		{
			if(!i) memset(reply, 0, 1024);
			strcat(reply,"#");
			char id[3];
			sprintf(id, "%d", ts->tasks[i].id);
			strcat(reply,id);
			strcat(reply,", ");
			strcat(reply,ts->tasks[i].name);
			strcat(reply,"\n");
		}	
		
	}
	write_reply(reply);
	free(reply);
}

void show_output(int id)
{
	int idx = open("log.idx", O_RDONLY , 0700);
	int log = open("log", O_RDONLY , 0700);
	char* help =(char*) malloc(sizeof(char)*10);
	int offset = 0;
	int readbytes = 0;
	int flag = 1;
	char* token;
	while(flag)
	{
		readln(idx, help);
		token = strtok(help, " ");
		if(atoi(token) != id)
		{
			token = strtok(NULL, " ");
			offset += atoi(token);
		}
		else
		{
			token = strtok(NULL, " ");
			readbytes = atoi(token);
			flag = 0;
		}
	}
	free(help);	
	close(idx);
	lseek(log, offset, SEEK_SET);
	char *reply = malloc(sizeof(char) * readbytes);
	read(log, reply, readbytes);
	write_reply(reply);
	free(reply);
	close(log);
}

void help_shell(void)
{
	char *f[4];
	
	char *help = malloc(sizeof(char) * 256);
		
	f[0]="Execute a task -> (OPTION) executar p1 | p2 ... | pn\nDefine pipe-time -> (OPTION) tempo-inactividade <seconds>\n";
	f[1]="Define task-time -> (OPTION) tempo-execucao <seconds>\nList executing tasks -> (OPTION) listar\n";
	f[2]="List finished tasks -> (OPTION) historico\nEnd a running task -> (OPTION) terminar <task id>\n";
	f[3]="Show output -> (OPTION) output <task id>\nHelp -> (OPTION) ajuda\n";
	
	for(int i = 0;i<4;i++)
	{	
		strcat(help, f[i]);	
	}
	write_reply(help);
	free(help);

}

void help_cmd(void)
{
	
	char *f[3];

	char *help = malloc(sizeof(char) * 256);
	
	f[0]="Execute a task -> (OPTION) -e \"p1 | p2 ... | p3\"\nDefine pipe-time -> (OPTION) -i <seconds>\n";
	f[1]="Define task-time -> -m n\nList executing tasks -> -l\nList finished tasks -> -r\n";
	f[2]="End a running task -> -t <task id>\nShow output -> -o <task id>\nHelp -> -h\n";
	
	for(int i = 0;i<3;i++)
	{	
		strcat(help, f[i]);	
	}
	write_reply(help);
	free(help);
}


void handle_client_request(char* request, Tasks *tasks)
{
	char* cmd = strtok(request, " ");
	
	if(!strcmp(cmd, "-i"))
	{
		int time = atoi(strtok(NULL, " "));
		set_task_timer(tasks, time);
	}
	else if(!strcmp(cmd, "-m"))
	{
		int time = atoi(strtok(NULL, " "));
		set_pipe_timer(tasks, time);
	}
	else if(!strcmp(cmd, "-e"))
	{
		execute_tasks(tasks, request + 3);
	}
	else if(!strcmp(cmd, "-l"))
	{
		show_active(tasks);
	}
	else if(!strcmp(cmd, "-t"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	else if(!strcmp(cmd, "-r"))
	{
		show_finished(tasks);
	}
	else if(!strcmp(cmd, "-h"))
	{
		help_cmd();
	}
	else if(!strcmp(cmd, "-h2"))
	{
		help_shell();
	}
	else if(!strcmp(cmd, "-o"))
	{
		int id = atoi(strtok(NULL, " "));
		show_output(id);
	}
	else
	{
		printf("COMMAND ERRO");
	}
}

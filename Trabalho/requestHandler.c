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

void write_to_file(char *output)
{
	int fd = open("test", O_CREAT | O_WRONLY, 0700);
	write(fd, output, strlen(output));
	close(fd);
}

void execute(char *cmds[], int n)
{
	int fd[n][2];
	int pids[n];

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
				args[j++] = cmd;
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

	//Father reads the result from the last pipe
	for(int k = 0; k < n; k++)
	{
		if(k == n-1)
		{
			char* result = malloc(sizeof(char)*1024);
			char* aux = malloc(sizeof(char)*512);
			close(fd[k][1]);
			if(dup2(fd[k][0], 0))
				perror("ERRO IN DUP3");
			close(fd[k][0]);
			
			while(readln(0, aux))
			{
				strcat(result, aux);
				strcat(result,"\n");
			}
			write_to_file(result);
			free(aux);
			free(result);
		}
		else
		{
			close(fd[k][0]);
			close(fd[k][1]);
		}
	}
//	Waits for all Children (dont know if needed yet);
	for(int k = 0; k < n; k++)
		waitpid(pids[k], NULL, 0);

}

void parse_execute(Tasks *ts, int id)
{
	char* tmp = strdup(ts->tasks[id].name);
	int n = count_char(tmp, '|') + 1;
	char *cmds[n];
	char *chain = strtok(tmp, "|");
	int j = 0;
	while(chain != NULL)
	{	
		cmds[j++] = chain;
		chain = strtok(NULL, "|");
	}
	ts->tasks[id].state = ACTIVE;
	execute(cmds, n);
	char *reply = malloc(sizeof(char) * 30);
	strcat(reply,"nova tarefa #");
	char aux[5];
	sprintf(aux, "%d", ts->tasks[id].id);
	strcat(reply, aux);
	write_reply(reply);
	free(reply);
	ts->tasks[id].state = DEAD;
	free(tmp);
}

void execute_tasks(Tasks *ts, char* cmd)
{
	int id = init_task(ts, cmd);
	parse_execute(ts, id);
}

void show_finished(Tasks *ts)
{
	char *reply = malloc(sizeof(char)*1024);
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
		printf("%s\n", cmd);
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
		printf("%s\n", cmd);
	}
	else if(!strcmp(cmd, "-o"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	else
	{
		printf("COMMAND ERRO");
	}
}

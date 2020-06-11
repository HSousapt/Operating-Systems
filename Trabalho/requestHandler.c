#include "requestHandler.h"


ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}

int count_char(char* string, char c)
{
	int r = 0;
	for(int i = 0; i < strlen(string); i++)
		if(string[i] == c) r++;
	return r;
}

void execute(char *cmds[], int n)
{
	int fd[n][2];
	int pids[n];
	char* result = malloc(sizeof(char*)*1024);

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
			close(fd[k][1]);
			if(dup2(fd[k][0], 0))
				perror("ERRO IN DUP3");
			close(fd[k][0]);

			while(readln(0, result))
				printf("%s\n", result);
			memset(result, 0, 1024);
		}
		else
		{
			close(fd[k][0]);
			close(fd[k][1]);
		}
	}
	//Waits for all Children (dont know if needed yet);
	for(int k = 0; k < n; k++)
		waitpid(-1, NULL, 0);
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
	ts->tasks[id].state = DEAD;;
	free(tmp);
}

void execute_tasks(Tasks *ts, char* cmd)
{
	int id = init_task(ts, cmd);
	parse_execute(ts, id);
}

void show_finished(Tasks *ts)
{
	for(int i = 0; i < ts->size; i++)
	{
		if(ts->tasks[i].state == DEAD)
			printf("#%d, %s\n", ts->tasks[i].id, ts->tasks[i].name);
	}
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
		printf("ERRO\n");
	}
}

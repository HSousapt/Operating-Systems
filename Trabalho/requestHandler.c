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
	int status = 0;	

	//cria uma lista de pipes
	for(int i = 0; i < n;i++)
	{
		pipe(fd[i]);
	}
	int i;
	for(i = 0; i < n; i++)
	{
		pids[i] = fork();
		if(pids[i] < 0) perror("ERRO NO FORK\n");

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
			
			if(i == 0)
			{
				printf("Primeiro %s\n", args[0]);
				close(fd[i][0]);
				dup2(fd[i][1], 1);
				close(fd[i][1]);
				execvp(args[0], args);
				_exit(1);
			}
			else
			{
				printf("%s\n", args[0]);
				close(fd[i-1][1]);
				dup2(fd[i-1][0], 0);
				close(fd[i-1][0]);
				//close(fd[i][0]);
				//dup2(fd[i][1], 1);
				//close(fd[i][1]);
				execvp(args[0], args);
				_exit(1);
			}
		}
	}
}

void parse_execute(Tasks *ts, int id)
{
	int n = count_char(ts->tasks[id].name, '|') + 1;
	printf("%d\n", n);
	char *cmds[n];
	char *chain = strtok(ts->tasks[id].name, "|");
	int j = 0;
	while(chain != NULL)
	{	
		cmds[j++] = chain;
		chain = strtok(NULL, "|");
	}
	
	execute(cmds, n);
}

void execute_tasks(Tasks *ts, char* cmd)
{
	int id = init_task(ts, cmd);
	parse_execute(ts, id);
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
		printf("%s\n", cmd);
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

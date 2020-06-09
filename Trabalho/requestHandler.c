#include "requestHandler.h"


ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}

int count_pipes(char* string)
{
	int r = 0;
	for(int i = 0; i < strlen(string); i++)
		if(string[i] == '|') r++;
	return r;
}

void execute(char *cmds[], int n)
{
	for(int i = 0; i < n; i++)
	{
		int pid;
		if(!(pid = fork()))
			execlp(cmds[i], cmds[i], NULL);
		else
			waitpid(pid, NULL, 0);
	}
}

void parse_execute(Tasks *ts, int id)
{
	int n = count_pipes(ts->tasks[id].name)+ 1;
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

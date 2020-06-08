#include "requestHandler.h"


ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}

void execute_tasks(Tasks *ts, char* cmd)
{
	for(int i = 0; i < ts->size && ts->tasks[i].state != free; i++)
	{
		if(ts->tasks[i].state == free)
		{
			ts->tasks[i] = init_task(cmd, i+1);
		}
	}
		

	printf("Task -> %s, Task id -> %d\n", ts->tasks[0].name, ts->tasks[0].id);
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

#include "requestHandler.h"


ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}


void handle_client_request(char* request)
{
	char* cmd = strtok(request, " ");
	
	if(!strcmp(cmd, "-i"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	if(!strcmp(cmd, "-m"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	if(!strcmp(cmd, "-e"))
	{
		cmd = strtok(NULL, " ");
		printf("%s\n", cmd);
	}
	if(!strcmp(cmd, "-l"))
	{
		printf("%s\n", cmd);
	}
	if(!strcmp(cmd, "-t"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	if(!strcmp(cmd, "-r"))
	{
		printf("%s\n", cmd);
	}
	if(!strcmp(cmd, "-h"))
	{
		printf("%s\n", cmd);
	}
	if(!strcmp(cmd, "-o"))
	{
		int time = atoi(strtok(NULL, " "));
		printf("%d\n", time);
	}
	else
	{
		printf("ERRO\n");
	}
}

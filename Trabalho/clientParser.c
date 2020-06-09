#include "clientParser.h"

ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}


void send_request(char *code)
{
	mkfifo("request",0700);
	int request;
	request = open("request",O_WRONLY);
	if(request < 0) perror("ERRO");
	write(request,code,strlen(code));
	close(request);
}


void handle_cmd_shell()
{
	char buffer[50];
	while(readln(0, buffer))
	{
		char *request = malloc(sizeof(char)*30);
		strcat(request, buffer);
		send_request(request);
		free(request);
	}
}

void handle_cmd_line(char **cmds, int n)
{
	char *request = malloc(sizeof(char)*50);
	for(int i = 0; i < n; i++)
	{
		strcat(request, cmds[i]);
		strcat(request, " ");
	}
	request[strlen(request)-1] = '\0';
	send_request(request);
	free(request);
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


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


int main(int argc, char **argv)
{
	int client_pid = getpid();
	char pid[7];
	sprintf(pid,"%d", client_pid);
	char buffer[30];
	if(argc < 2)
	{
		while(readln(0, buffer))
		{
			char *request = malloc(sizeof(char)*30);
			strcat(request, buffer);
			send_request(request);
			free(request);
		}
	}
	else
	{
		printf("Em args -> Tratar mais tarde\n");
	}
}

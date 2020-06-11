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
	int request;
	request = open("request",O_WRONLY);
	if(request < 0) perror("ERROR");
	write(request,code,strlen(code));
	close(request);
}

void receive_reply()
{
	char* buffer = malloc(sizeof(char*)*1024);
	mkfifo("reply", 0700);
	int reply = open("reply", O_RDONLY);
	if(reply < 0) perror("FIFO ERROR");
	while(readln(reply, buffer))
		printf("%s\n", buffer);
	free(buffer);
	close(reply);
}

void help(void)
{
}


int parse_cmd(char* buff, char* request)
{
	int r = 1;
	char *token = strtok(buff," ");
	if(!strcmp(token,"tempo-inactividade"))
	{
		strcat(request, "-i ");
		token = strtok(NULL, " ");
		strcat(request, token);
		
	}
	else if(!strcmp(token,"tempo-execucao"))
	{
		strcat(request, "-m ");
		token = strtok(NULL, " ");
		strcat(request, token);
	}
	else if(!strcmp(token,"executar"))
	{
		strcat(request, "-e ");
		strcat(request, buff + 9);
	}
	else if(!strcmp(token,"listar"))
	{
		strcat(request, "-l");
	}
	else if(!strcmp(token,"terminar"))
	{
		strcat(request, "-t ");
		token = strtok(NULL, " ");
		strcat(request, token);
	}
	else if(!strcmp(token,"historico"))
	{
		strcat(request, "-r");
	}
	else if(!strcmp(token,"ajuda"))
	{
		help();
	}
	else if(!strcmp(token,"outpud"))
	{
		strcat(request, "-o ");
		token = strtok(NULL, " ");
		strcat(request, token);
	}
	else
		r = 0;

	return r;
}


void handle_cmd_shell()
{
	char buffer[50];
	write(1, "> ", 2);
	while(readln(0, buffer))
	{
		char* request = malloc(sizeof(char)*50);
		if(parse_cmd(buffer, request))
		{
			send_request(request);
			receive_reply();
		}
		else
			printf("UNKNOWN COMMAND!\n");
		write(1, "> ", 2);
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

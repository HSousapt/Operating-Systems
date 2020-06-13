#include "requestHandler.h"
#define MAXBUFF 30

int main(int argc, char **argv)
{
	int request;
	mkfifo("request", 0700);
	mkfifo("reply", 0700);
	
	Tasks tasks = init_tasks(10);
	while(1)
	{
		char buffer[MAXBUFF];
		memset(buffer, 0, MAXBUFF);
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE");
			return -1;
		}

		readln(request, buffer);
		close(request);
		handle_client_request(buffer, &tasks);
	}
	unlink("request");
	return 0;
}

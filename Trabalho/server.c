#include "requestHandler.h"
#define MAXBUFF 120

int main(int argc, char **argv)
{
	int request;
	mkfifo("request", 0700);
	mkfifo("reply", 0700);
	char* buffer = malloc(sizeof(char)*MAXBUFF);

	Tasks tasks = init_tasks(10);
	while(1)
	{
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE");
			return -1;
		}

		readln(request, buffer);
		close(request);
		printf("%s\n", buffer);
		handle_client_request(buffer, &tasks);
		memset(buffer, 0, MAXBUFF);

	}
	unlink("request");
	return 0;
}

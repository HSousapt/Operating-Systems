#include "requestHandler.h"

int main(int argc, char **argv)
{
	int request;
	char *buffer = malloc(sizeof(char)*50);
	mkfifo("request", 0700);

	Tasks tasks = init_tasks(10);
	while(1)
	{
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE\n");
			return -1;
		}

		readln(request, buffer);
		close(request);

		handle_client_request(buffer, &tasks);
		memset(buffer, 0, 30);
	}

	close(request);
	unlink("request");
	return 0;
}

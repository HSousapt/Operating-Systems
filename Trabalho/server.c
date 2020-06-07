#include "requestHandler.h"

int main(int argc, char **argv)
{
	int request;
	char *buffer = malloc(sizeof(char)*50);
	mkfifo("request", 0700);

	Tasks *tasks = init_tasks(10);
	for(int i = 0; i < 10; i++)
	{
		printf("%d e %d\n",tasks[i].taskTime, tasks[i].pipeTime);
	}
	while(1)
	{
		int task_counter = 0;
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE\n");
			return -1;
		}

		readln(request, buffer);
		close(request);

		handle_client_request(buffer);
		memset(buffer, 0, 30);
	}

	close(request);
	unlink("request");
	return 0;
}

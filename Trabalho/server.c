#include "requestHandler.h"

int main(int argc, char **argv)
{
	int request;
	mkfifo("request", 0700);
	mkfifo("reply", 0700);
	char *buffer = malloc(sizeof(char*)*30);
	
	Tasks tasks = init_tasks(10);
	while(1)
	{
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE");
			return -1;
		}

//		int pid;
//		if((pid = fork()) < 0) perror("FORK ERROR");
//		if(!pid)
//		{
//			char *buffer = malloc(sizeof(char*)*30);
			readln(request, buffer);
			handle_client_request(buffer, &tasks);
//			free(buffer);
			memset(buffer, 0 , 30);
//			_exit(0);
//		}
		close(request);
	}

	close(request);
	unlink("request");
	return 0;
}

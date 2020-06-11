#include "clientParser.h"


int main(int argc, char **argv)
{
	int client_pid = getpid();
	char pid[7];
	sprintf(pid,"%d", client_pid);
	if(argc < 2)
	{
		handle_cmd_shell();
	}
	else if(argc >= 2)
	{
		handle_cmd_line(argv + 1, argc - 1);
		receive_reply();
	}
	else
	{
		printf("ERROR IN CLIENT ARGUMENTS!!\n");
	}

	return 0;
}

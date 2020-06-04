#include "clientParser.h"


int main(int argc, char **argv)
{
	int client_pid = getpid();
	char pid[7];
	sprintf(pid,"%d", client_pid);
	char buffer[30];
	if(argc < 2)
	{
		handle_cmd_shell(buffer);
	}
	else if(argc > 2)
	{
		handle_cmd_line(argv + 1, argc - 1);
	}

	return 0;
}

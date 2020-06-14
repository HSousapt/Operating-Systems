#include "clientParser.h"


int main(int argc, char **argv)
{
	if(argc < 2)
	{
		handle_cmd_shell();
	}
	else if(argc >= 2)
	{
		handle_cmd_line(argv + 1, argc - 1);
	}
	else
	{
		printf("ERROR IN CLIENT ARGUMENTS!!\n");
	}

	return 0;
}

#include "clientParser.h"


int main(int argc, char **argv)
{
	if(argc < 2)
	{
		handle_cmd_shell();
	}
	else if(argc >= 2)
	{
		if(!strcmp(argv[1],"-f"))
		{
			int fd = open(argv[2], O_RDONLY, 0700);
			if(fd < 0) perror("FILE ERROR");
			char *buffer = malloc(sizeof(char) * 128);
			while(readln(fd, buffer))
			{
				int i = 0;
				int n = 1;
				char **input =(char**)malloc(sizeof(char*)*3);
				char *token= strtok(buffer, " ");
				input[i++] = token ;
				if(!strcmp(token, "-e") || !strcmp(token, "-t") || !strcmp(token, "-i") || !strcmp(token, "-m") || !strcmp(token, "-o"))
				{
					input[i] = buffer + 3;
					n = 2;
				}
				handle_cmd_line(input, n);
				free(input);
				memset(buffer, 0, 50);
			}
			free(buffer);
			close(fd);
		}
		else
			handle_cmd_line(argv + 1, argc - 1);
	}
	else
	{
		printf("ERROR IN CLIENT ARGUMENTS!!\n");
	}

	return 0;
}

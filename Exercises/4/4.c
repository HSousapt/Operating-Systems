#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


void execute(char **argv)
{
	execvp(argv[0],argv);
}


int main(int argc, char** argv)
{
	if(!strcmp(argv[1], "-i") && !strcmp(argv[3], "-o"))
	{
		int pid;
		int fd0 = open(argv[2], O_RDONLY, 0644);
		int fd1 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);

		dup2(fd0, 0);
		dup2(fd1, 1);

		if((pid = fork()) < 0) perror("FORK ERROR!!\n");
		else if(!pid)
		{		
			execute(argv + 5);
			_exit(0);
		}
		else
		{
			waitpid(-1, NULL, 0);
			close(fd0);
			close(fd1);	
		}
	}
	else if(!strcmp(argv[1], "-i"))
	{
		int fd0 = open(argv[2], O_RDONLY, 0644);
		dup2(fd0,0);
		int pid;

		if((pid = fork()) < 0) perror("FORK ERROR!!\n");
		else if(!pid)
		{		
			execute(argv + 3);
			_exit(0);
		}
		else
		{
			waitpid(-1, NULL, 0);
			close(fd0);
		}
	}
	
	else if(!strcmp(argv[1], "-o"))
	{
		int fd1 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(fd1, 1);
	
		int pid;

		if((pid = fork()) < 0) perror("FORK ERROR!!\n");
		else if(!pid)
		{		
			execute(argv + 3);
			_exit(0);
		}
		else
		{
			waitpid(-1, NULL, 0);
			close(fd1);	
		}
	}
	else
	{
		execute(argv + 1);
	}

	return 1; 
}

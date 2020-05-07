#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pid;
	for(int i = 1; i < argc; i++)
	{
		
		if((pid = fork()) < 0)
		{
			perror("Fork Error!!\n");
		}
		if(!pid)
		{
			execlp(argv[i], argv[i], NULL);
			_exit(0);
		}
	}

	for(int i = 1; i < argc; i++)
			waitpid(-1, NULL, 0);

	return 0;
}

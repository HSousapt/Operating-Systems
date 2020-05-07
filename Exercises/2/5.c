#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int pid;
	for(int i = 0; i < 10; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("Erro no fork()");
			return 1;
		}
		if(pid > 0)
		{
			waitpid(-1,NULL,0);
			
			if(getpid() > 0)
				printf("Terminou o processo com nº: %d\n",i);
			_exit(0);
		}
	printf("Sou o processo nº: %d, com pid: %d e o meu pai tem o pid: %d\n", i, getpid(), getppid());
	}
	return 0;
}

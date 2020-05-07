#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int pid;
	if((pid=fork()) < 0)
	{
		perror("Fork Error!");
	}
	if(!pid)
	{
		execlp("ls","-l",NULL);
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("Eu sou o pai com o pid: %d e o meu filho tem o pid: %d\n",getpid(),pid);
	}
	return 0;
}

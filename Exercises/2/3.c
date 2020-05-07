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
			perror("erro no fork\n");
		if(!pid)
		{
			_exit(0);
		}
		else
		{
			waitpid(pid,NULL,0);
			printf("Sou o processo pai: %d e terminou o meu filho: %d com nº %d\n",getpid(),pid,i);
		}
	}
}

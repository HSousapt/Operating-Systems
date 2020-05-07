#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int pid,status;
	if((pid = fork())<0)
	{
		perror("O fork falhou!\n");
	}
	if(!pid)
	{	
		printf("eu sou o filho: %d\nE eu sou o pai: %d\n",getpid(),getppid());
	}
	else
	{
		pid_t child = wait(&status);
		printf("eu sou o pai: %d\nE eu sou o filho: %d\n",getpid(),child);

	}
	return 0;
}

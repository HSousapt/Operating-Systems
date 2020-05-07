#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int agrc, char** argv)
{
	int n;
	int buffer[1024];
	int pid;
	
	int fh0 = open("/etc/passwd", O_RDONLY, 0644);
	int fh1 = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	int fh2 = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);

	if(dup2(fh0,0) < 0 || dup2(fh1,1) < 0 || dup2(fh2,2) < 0)
	{
		perror("DUP ERROR!!!\n");
	}
	
	if((pid = fork()) < 0)
	{
		perror("FORK ERROR!!!\n");
	}
	else if(!pid)
	{
		printf("sou o filho com pid: %d e o meu pai tem pid: %d\n",getpid(),getppid());
		while((n = read(0,buffer,sizeof(buffer))))
			write(1,buffer,n);
		_exit(0);
	}
	else
	{
		printf("sou o filho com pid: %d e o meu pai tem pid: %d\n", pid,getppid());
		waitpid(-1,NULL,0);	
	}
	
	return 1;
}

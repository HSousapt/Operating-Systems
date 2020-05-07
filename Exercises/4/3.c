#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char*argv[])
{
	int n;
	char buffer[1024];
	int pid;

	int fh0 = open("/etc/passwd", O_RDONLY, 0644);
	int fh1 = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700 );
	int fh2 = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700 );

	//close(0);
	//dup(fh0);
	dup2(fh0,0);

	//close(1);
	//dup(fh1);
	dup2(fh1,1);	

	//close(2);
	//dup(fh2);
	dup2(fh2,2);
	
	if((pid = fork()) < 0) perror("FORK ERROR!!\n");
	else if(!pid)
	{
		execlp("wc","wc",NULL);
		_exit(0);
	}
	else
	{
		waitpid(-1,NULL, 0);
		close(fh0);
		close(fh1);
		close(fh2);
	}
	return 1;
}

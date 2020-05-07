#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pid, n, pd[2];
	char buffer[1024];

	pipe(pd);
	
	if((pid = fork()) < 0) perror("FORK ERROR!\n");

	if(!pid)
	{
		close(pd[1]);
		//o descritor stdin do filho é substituido pelo descritors de leitura do pipe
		dup2(pd[0], 0);
		execlp("wc", "wc", NULL);
	}
	
	close(pd[0]);
	while((n = read(0, buffer, sizeof(buffer))))
		write(pd[1], buffer, n);
	close(pd[1]);
	waitpid(pid, NULL, 0);

	return 1;
}

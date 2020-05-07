#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void handle_input(char* path)
{
	int pid, pd[2];

	if((pipe(pd)) < 0) perror("ERROR IN PIPE\n");

	if((pid = fork()) < 0)	perror("ERROR IN FORK\n");

	if(!pid)
	{
		close(pd[0]);
		//o descritor stdout do processo filho é substituido pelo descritor de escrita do pipe
		dup2(pd[1], 1);
		
		execlp("ls", "ls", path, NULL);
	}

	close(pd[1]);

	//o descritor stdin do processo pai é substituido pelo descritor de leitura do pipe
	dup2(pd[0], 0);
	
	execlp("wc", "wc", "-l", NULL);
}


int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("Specify the PATH\n");
	}
	else
	{
		int pid;

		if((pid = fork()) < 0) perror("ERRO NO FORK\n");
		
		if(!pid)
		{
			handle_input(argv[1]);
			_exit(0);
		}

		waitpid(pid, NULL, 0);
	}
	return 1;
}

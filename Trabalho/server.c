#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
#include <sys/wait.h>
#include <signal.h>



ssize_t readln(int f,char* buff)
{
	int r,n=0;

	while((r=read(f,(char*)(buff+n),1))==1 && *((char*)(buff+n))!='\n') n++;

	if(*(char*)(buff+n)=='\n' || *(char*)(buff+n)==EOF) 
		*((char*)(buff+n))= '\0';

	return (r==-1)?-1:n;
}


int main(int argc, char **argv)
{
	int request;
	char *buffer = malloc(sizeof(char)*30);
	mkfifo("request", 0700);

	while(1)
	{
		request = open("request", O_RDONLY);
		if(request < 0)
		{
			perror("ERRO NO SERVERPIPE\n");
			return 0;
		}

		readln(request, buffer);
		close(request);
		int pid = fork();
		if(pid < 0)
		{
			perror("ERRO NO FORKPIPE\n");
			return 0;
		}
		else if(!pid)
		{
			printf("%s\n", buffer);
			printf("%d -> o meu pid\n%d -> o pid do meu pai\n", getpid(), getppid());
			_exit(0);
		}
		
		waitpid(pid, NULL, 0);
		memset(buffer, 0, 30);
	}
}

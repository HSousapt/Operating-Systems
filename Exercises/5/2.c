#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char** argv)
{
	int pid, pd[2];
	char buffer[1024];
	int n;
	char *s ="tentativa\n";
	
	if(pipe(pd) < 0) perror("PIPE ERROR!\n");

	if((pid = fork()) < 0) perror("FORK ERROR!\n");

	if(!pid)
	{
		close(pd[1]);
		while((n = read(pd[0], buffer, sizeof(buffer))) > 0)
			write(1, buffer, n);

		close(pd[0]);
		_exit(0);
	}
	
	close(pd[0]);
	for(n = 0; n != 4; n++)
	{
		sleep(2);
		write(1, s, strlen(s));
	}
	close(pd[1]);
	
	return 1;
}

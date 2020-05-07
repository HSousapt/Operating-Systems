#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


void Pai_Filho(void)
{
	int pd[2];
	int pid;
	char buffer[1024];
	
	write(1, "Father talks!\n", 14);

	//Sys Call that creates a pipe where pd[0] is the reader descriptor and pd[1] is the writer descriptor
	pipe(pd);

	if((pid = fork()) < 0) perror("ERRO NO FORK!");
	
	if(pid == 0)
	{
		close(pd[1]);
		size_t n = read(pd[0],buffer,sizeof(buffer));
		write(1, "Son received a msg:\n", 20);
		write(1,buffer,n);
		close(pd[0]);
		_exit(0);
	}
	else
	{
		close(pd[0]);
		char *msg = "Hello Son!\n";
		write(1, "Father sent a msg\n", 18);
		sleep(5);
		write(pd[1], msg, strlen(msg));
		close(pd[1]);
		waitpid(pid, NULL, 0);
	}
}


void Filho_Pai(void)
{
	int pd[2];
	int pid;
	char buffer[1024];
	
	write(1, "Son responds!\n", 14);	

	//Sys Call that creates a pipe where p[0] is the reader descriptor and p[1] is the writer descriptor
	if(pipe(pd) < 0) perror("ERRO A CRIAR O PIPE!\n");

	if((pid = fork()) < 0) perror("ERRO NO FORK!\n");
	
	if(pid == 0)
	{
		close(pd[0]);
		char *msg = "Hello Father!\n";
		write(1, "Son sent a msg\n", 15);
		sleep(5);
		write(pd[1],msg,strlen(msg));
		close(pd[1]);
		_exit(0);
	}
	else
	{
		close(pd[1]);
		size_t n = read(pd[0], buffer, sizeof(buffer));
		write(1, "Father received a msg\n", 22);
		write(1, buffer, n);
		close(pd[0]);
		waitpid(pid, NULL, 0);
	}
}


int main(int argc, char** argv)
{
	Pai_Filho();
	char *msg ="\n----------------------------\n\n";
	write(1, msg, strlen(msg));
	Filho_Pai();
	
	return 1;
}

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int pid=getpid(),ppid=getppid();
	printf("Eu sou o processo pai: %d\nEu sou o processo filho: %d\n",ppid,pid);
}

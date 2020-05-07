#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

/*
pid_t waitpid(pid_t pid, int *statusPtr, int options);

The value of pid can be:

    < -1: Wait for any child process whose process group ID is equal to the absolute value of pid.
    -1: Wait for any child process.
    0: Wait for any child process whose process group ID is equal to that of the calling process.
    > 0: Wait for the child whose process ID is equal to the value of pid.

The value of options is an OR of zero or more of the following constants:

    WNOHANG: Return immediately if no child has exited.
    WUNTRACED: Also return if a child has stopped. Status for traced children which have stopped is provided even if this option is not specified.
    WCONTINUED: Also return if a stopped child has been resumed by delivery of SIGCONT.

1.where pid is the process of the child it should wait.

2.statusPtr is a pointer to the location where status information for the terminating process is to be stored.

3.specifies optional actions for the waitpid function. Either of the following option flags may be specified, or they can be combined with a bitwise inclusive OR operator:

WNOHANG WUNTRACED WCONTINUED

If successful, waitpid returns the process ID of the terminated process whose status was reported. If unsuccessful, a -1 is returned.

benifits over wait

1.Waitpid can used when you have more than one child for the process and you want to wait for particular child to get its execution done before parent resumes

2.waitpid supports job control

3.it supports non blocking of the parent process
*/

int main(int argc, char** argv)
{
	int pid;
	for(int i = 0; i < 10; i++)
	{
		if((pid = fork()) < 0)
		{
			perror("erro a fazer o fork()");
			return 1;
		}
		if(pid == 0)
		{
			printf("Sou o processo filho com pid: %d e com nº: %d e o meu pai é: %d\n",getpid(),i,getppid());
			_exit(0);
		}
	}
	
	for(int i = 0; i < 10; i++)
	{
		waitpid(-1,NULL,0);
	}
return 0;
}

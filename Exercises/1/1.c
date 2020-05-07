#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

void mycp(int fd_source,int fd_dest)
{
	int n = 0;
	char c=' ';
	while((n=read(fd_source,&c,1)))
	{
		write(fd_dest,&c,1);
	}
}

int main(int argc, char** argv){
	int fd_s,fd_d;
	
	if(argc == 3)
	{
		fd_s = open(argv[1],O_RDONLY,0700);
		fd_d = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
	else
	{ 
		perror("missing source or destination file operand after\n");
		return 0;
	}
	
	if(fd_s < 0 || fd_d < 0)
	{
		perror("Error opening the files");
		return 0;
	}
	else
	{
		mycp(fd_s,fd_d);
		close(fd_s);
		close(fd_d);
	}
	return 0;
}

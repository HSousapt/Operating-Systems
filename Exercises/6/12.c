#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int fd, n;
	char buffer[1024];
	fd = open("fifo", O_WRONLY, 0666);
	while((n=read(0, buffer, sizeof(buffer)))> 0)
	{
		write(fd, buffer, n);
	}

	close(fd);
	
	return 0;
}

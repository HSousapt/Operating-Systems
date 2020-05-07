#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	int fd,n;
	char buffer[1024];
	fd = open("fifo", O_RDONLY);
	
	while((n = read(fd,buffer,sizeof(buffer))))
	{
		write(1, buffer, n);
	}

	close(fd);

	return 0;
}


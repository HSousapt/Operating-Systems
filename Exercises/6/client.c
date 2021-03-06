#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char** argv)
{

	int fd;
	fd = open("fifo", O_WRONLY);
	char buffer[1024];
	size_t n;

	while((n = read(0, buffer, sizeof(buffer))) > 0)
	{
		if(!strcmp(buffer, "quit\n"))
			break;
		else
		{
			write(fd, buffer, n);
			memset(buffer, 0, sizeof(buffer));
		}
	}
	
	puts("Cliente terminou!!!");
	close(fd);

	return 0;
}

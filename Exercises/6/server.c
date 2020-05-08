#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int file, fd;
	char buffer[1024];
	size_t n;

	if(mkfifo("fifo", 0666))
                 perror("fifo");
	
	file = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	fd = open("fifo", O_RDONLY);

	dup2(file, 1);
	dup2(fd, 0);

	close(file);
	close(fd);

	while(1)
	{
		while((n = read(0, buffer, sizeof(buffer))) > 0)
		{
			write(1, buffer, n);
		}
	}

	return 0;
}

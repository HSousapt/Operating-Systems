#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	if(mkfifo("fifo", 0666))
		perror("fifo");

	return 0;
}

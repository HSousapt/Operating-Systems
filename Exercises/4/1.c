#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char*argv[])
{
	int n;
	char buffer[1024];

	int fh0 = open("/etc/passwd", O_RDONLY, 0644);
	int fh1 = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700 );
	int fh2 = open("erros.txt", O_CREAT | O_WRONLY | O_TRUNC, 0700 );

	close(0);
	dup(fh0);

	close(1);
	dup(fh1);

	close(2);
	dup(fh2);

	while((n = read(0,buffer,sizeof(buffer))))
	{
		write(1,buffer,n);
	}

	close(fh0);
	close(fh1);
	close(fh2);

	return 1;
}

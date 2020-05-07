#include <stdio.h>
#include "readln_v1.h"
//#include <unistd.h>
//#include <fcntl.h>

/*ssize_t readln_v1(int fildes, char *buf, size_t n_byte)
{
	int i = 0;
	char c = ' ';
	int n = 1;
	while((i<n_byte) && (c != '\n') && n)
	{
		n = read(fildes,&c,1);
		if((c != '\n') && n)
			buf[i++] = c;
	}
	
	//Adição do EOF == 0 com verificação no caso de char ao limite de leitura
	if(i < n_byte)
		buf[i] = 0;
	else
		buf[i--] = 0;
	if(n<0)
		return n;
	if((n == 0) && (i == 0))
		return -1;
	return i;
}*/

int main(int argc, char** argv){
	int fd;
	int N = 1024;
	char buffer[N];
	ssize_t size;

	if(argc > 1)
	{
		fd = open(argv[1], O_RDONLY, 0700);
	}
	else
	{
		fd = 0;
	}

	if(fd < 0) perror(argv[1]);
	else
	{	
		do
		{
			size = readln_v1(fd,buffer,N);
			if(size > 0)
			{
				write(1,buffer,size);
				write(1,"\n",1);
			}
//			else
//				perror("Erro de escrita!\n");
		}
		while(size>=0);
		close (fd);
	}
	return 0;
}

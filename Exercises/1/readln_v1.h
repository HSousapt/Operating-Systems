#include <unistd.h>
#include <fcntl.h>

ssize_t readln_v1(int fildes, char *buf, size_t n_byte)
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
	
	return i;
}


int readchar(int fd, char* buf)
{
	if(pos==read_bytes)
		read_bytes = read(fd,buf,MAXSIZE)
		pos = 0
	else
	{
		*buf=bufferinterno[pos];
		pos++;
	}
}

ssize_t readln(int fd, char *line, size_t size)
{
	int pos = 0;
	int read_bytes = 0;
	while(pos < size && readchar(fd,line+pos)>0)
	{
		read_bytes ++;
		if(line[pos]=='\n')
			break;
		pos++;
	}
	return read_bytes
}

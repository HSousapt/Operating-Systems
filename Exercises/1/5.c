#include <stdio.h>
#include "readln_v1.h"

int main(int argc, char** argv){
	int fd;
	int N = 1024;
	char buffer[N];
	ssize_t size;
	int line = 1;
	char line_num[9];
	
	if(argc > 1)
	{
		fd = open(argv[1], O_RDONLY, 0700);	
	}
	else
	{
		fd = 0;
	}
	if(fd < 0)
		perror(argv[1]);
	do
	{
		size = readln_v1(fd,buffer,N);
		if(size)
		{
			sprintf(line_num,"%d",line++);
			write(1,"    ",4);
			write(1,line_num,sizeof(line_num));
			write(1,"  ",2);
			write(1,buffer,size);
			write(1,"\n",1);
		}
	}
	while(size >= 0);

	close(fd);

	return 0;
}

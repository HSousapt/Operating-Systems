#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int main(int argc,char** argv)
{
	Person* ps = init_struct_Person();
	
	if(argc < 3)
	{
		perror("Not enough arguments were given!");
		exit(0);
	}
	else
	{
		handle_option(ps,argv[1],argv[2],argv[3]);	
	}

	free(ps);
	return 0;
}

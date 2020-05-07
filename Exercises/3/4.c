#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	char *argvs[argc + 1];
	int j = 0;
	argvs[j++]=strdup("3");

	for(int i = 1; i <argc; i++)
	{
		argvs[j++] = strdup(argv[i]);
	}
	
	argvs[j] = NULL;

	execvp("./3",argvs);
	return 0;
}

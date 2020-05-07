#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void my_system(char *string, int n)
{
	char* token;
	token = strtok(string," ");
	char* args[n];
	
	int i = 0;
	
	while(token != NULL)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, " ");
	}
	
	for(int j = 0; j < i; i++)
		printf("%s\n",args[i]);
}

int main(int argc, char** argv)
{
	char s[] = "ls -l";
	my_system(s, 2);
	return 0;
}

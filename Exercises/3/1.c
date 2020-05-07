#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	execlp("ls","-l",NULL);
	return 1;
}


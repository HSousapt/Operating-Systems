#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "api.h"

#define not_free 1
#define is_free 0

#define SIZE 100

void write_to_file(Person p)
{
	int fd = open("persons.txt", O_CREAT | O_WRONLY | O_APPEND, 0700);
	if(fd < 0)
	{
		perror("erro!");
	}
	else
	{
		char idade [3];
		sprintf(idade,"%d",p.age);
		write(fd,p.name,strlen(p.name));
		write(fd," ",1);
		write(fd,idade,strlen(idade));
		write(fd,"\n",1);
		close(fd);
	}
	
}

Person* init_struct_Person()
{
	Person *ps = malloc(sizeof(struct person)*SIZE);
		

	for(int i = 0; i < SIZE; i++)
		ps[i].state = is_free;

	return ps;
}



void insert_new(Person *p, char* name, int age)
{
	if(p[SIZE].state == not_free)
	{
		Person* ps = realloc(p, sizeof(struct person)*SIZE*2);
		p = ps;		
	}
	
	int i = 0;

	while(p[i].state != is_free) i++;

	p[i].name = strdup(name);
	p[i].age = age;
	p[i].state = not_free;
	write_to_file(*p);
}


void update(Person* p, char* name, int new_age)
{
	int fd = open("persons.txt", O_RDWR, 0644);
	if(fd < 0)
	{
		perror("Could not open file 'persons.txt'\n");
	}
	else
	{
		
	}
}


void handle_option(Person* ps, char* command, char* name, char* n)
{
	int age = atoi(n);
	if(!strcmp(command,"-i"))
	{
			insert_new(ps, name, age);
	}
	if(!strcmp(command,"-u"))
	{
		printf("falta definir o update\n");	//	update(ps, name, age);
	}
}

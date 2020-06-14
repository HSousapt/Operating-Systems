#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define ACTIVE 4
#define FREE 2
#define ALIVE 1
#define DEAD 0

struct task{
	char *name;
	int id;
	int state;
	int pid;
};

typedef struct ts{
	struct task *tasks;
	int taskTime;
	int pipeTime;
	int size;
}Tasks;


//struct task init_task(char*, int);

int init_task(Tasks*, char*);

Tasks init_tasks(int);

void set_task_timer(Tasks *, int);

void set_pipe_timer(Tasks *, int);

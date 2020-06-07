#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define alive 1
#define dead 0

typedef struct task{
	char *name;
	int id;
	int state;
}Task;

typedef struct ts{
	struct task *tasks;
	int taskTime;
	int pipeTime;
}Tasks;


Task init_task(char*, int);

Tasks* init_tasks(int);

void set_task_timer(Tasks *, int);

void set_pipe_timer(Tasks *, int);

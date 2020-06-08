#include "task.h"

Task init_task(char* desc, int task_id)
{
	Task t;
	char *aux=malloc(sizeof(char*)*strlen(desc));
	aux = strdup(desc);
	t.name = aux;
	t.id = task_id;
	t.state = alive;
	return t;
}

Tasks* init_tasks(int size)
{
	Task *ts = malloc(sizeof(struct task)*size);
	Tasks *tasks = malloc(sizeof(struct ts));
	tasks->tasks = ts;
	tasks->taskTime = -1;
	tasks->pipeTime = -1;
	tasks->size = size;

	return tasks;
	
}

void set_task_timer(Tasks *ts, int time)
{
	ts->taskTime = time;
}

void set_pipe_timer(Tasks *ts, int time)
{
	ts->pipeTime = time;
}

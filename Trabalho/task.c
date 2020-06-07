#include "task.h"

Task init_task(char* desc, int task_id)
{
	return(Task){
		.name = strdup(desc),
		.id = task_id,
		.state = alive,
	};
}

Tasks* init_tasks(int size)
{
	Task *ts = malloc(sizeof(struct task)*size);
	return(Tasks*){
		->tasks = ts,
		->taskTime = -1,
		->pipeTime = -1,
	};
}

void set_task_timer(Tasks *ts, int time)
{
	ts->taskTime = time;
}

void set_pipe_timer(Tasks *ts, int time)
{
	ts->pipeTime = time;
}

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
	Tasks *tasks = malloc(sizeof(struct ts));
	tasks->tasks = ts;
	tasks->taskTime = -1;
	tasks->pipeTime = -1;

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

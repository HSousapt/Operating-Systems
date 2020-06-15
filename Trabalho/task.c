#include "task.h"

/*struct task init_task(char* desc, int task_id)
{
	struct task t;
	t.name = strdup(desc);
	t.id = task_id;
	t.state = alive;
	return t;
}*/

int init_task(Tasks *ts, char* cmd)
{
	int i;
	for(i = 0; i < ts->size; i++)
	{
		if(ts->tasks[i].state == FREE)
		{

			ts->tasks[i].name = strdup(cmd);
			ts->tasks[i].id =(i+1);
			ts->tasks[i].state = ALIVE;
			ts->tasks[i].pid = 0;
			ts->tasks[i].c = COM;
			break;
		}
	}
	return i;
}

Tasks init_tasks(int size)
{
	Tasks ts;
	ts.tasks = malloc(sizeof(struct task)*size);
	for(int i = 0; i < size; i++)
	{
		ts.tasks[i].state = FREE;
	}
	ts.taskTime = 0;
	ts.pipeTime = 0;
	ts.size = size;

	return ts;
}

void set_task_timer(Tasks *ts, int time)
{
	ts->taskTime = time;
}

void set_pipe_timer(Tasks *ts, int time)
{
	ts->pipeTime = time;
}

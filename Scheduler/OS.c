

#include "OS.h"


static OS_struct TasksArr[MAX_NUM_OF_TASKS];

static u8 tasksCounter;
u8 GetStatusOfCommTask(void);

OS_feedback OS_TaskCreate(fncPtr task, u16 periodicity, OS_state default_state)
{
	OS_feedback status = OS_OK;

	if(task == NULLPTR)
	{
		status = OS_NOK_NULL_PTR;
	}
	else if(tasksCounter >= MAX_NUM_OF_TASKS)
	{
		status = OS_NOK_TASK_COUNT_VIOLATION;
	}
	else if(periodicity > HYPER_PERIOD)
	{
		status = OS_NOK_HYPER_PERIOD_VIOLATION;
	}
	else
	{
		TasksArr[tasksCounter].function = task;
		TasksArr[tasksCounter].task_Periodicity = periodicity;
		TasksArr[tasksCounter].task_state = default_state;
		tasksCounter++;
		status = OS_OK;
	}

	return status;
}

/* LInked to ISR --- Time --- Task Ststes*/
void OS_Task_Handler(void)
{
	u8 id=0;

	/*cheack each task timeout -> Ready , counter++ */
	for(id=0; id<tasksCounter; id++)
	{
		if(TasksArr[id].task_state == BLOCKED)
		{

			if(TasksArr[id].Task_tick_counter >= TasksArr[id].task_Periodicity)
			{
				TasksArr[id].task_state = READY;
				TasksArr[id].Task_tick_counter = 1;
			}
			else
			{
				TasksArr[id].Task_tick_counter++;
			}
		}
		else if(TasksArr[id].task_state == SUSPENDED)
		{
			if(GetStatusOfCommTask() == 1)
			{
				TasksArr[id].task_state = READY;
			}
			else
			{
				TasksArr[id].task_state = SUSPENDED;
			}
		}
	}

}


void OS_TaskExecution(void)
{
	u8 id=0;

	/*cheack the task ready -> Run */
	for(id=0; id<tasksCounter; id++)
	{
		if(TasksArr[id].task_state == READY)
		{
			TasksArr[id].function();
			TasksArr[id].task_state = BLOCKED;
		}
	}
}

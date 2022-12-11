/*
 * scheduler.c
 *
 *  Created on: Dec 9, 2022
 *      Author: Cao Tien Dat
 */



#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void)
{
	unsigned char i;
	for(i = 0;i<SCH_MAX_TASKS;i++)
	{
		SCH_Delete_Task(i);
	}
	current_index_task = 0;
}
void SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	if(current_index_task < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void)
{
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].pTask){
			if (SCH_tasks_G[Index].Delay == 0) {
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Period) {
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			} else {
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

void SCH_Dispatch_Tasks(void)
{
	for(int i=0;i<current_index_task;i++)
	{
		if(SCH_tasks_G[i].RunMe > 0)
		{
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].RunMe--;
		}

		if(SCH_tasks_G[i].Period == 0)
		{
			SCH_Delete_Task(i);
		}
	}
}

void SCH_Delete_Task(uint32_t TaskID)
{
	if(current_index_task == 0) return;

	if(TaskID < current_index_task)
	{
		for(int i = TaskID; i < current_index_task - 1; i++){
			SCH_tasks_G[i] = SCH_tasks_G[i + 1];
		}
	}
	current_index_task--;
	SCH_tasks_G[current_index_task].pTask = 0x0000;
	SCH_tasks_G[current_index_task].Delay = 0;
	SCH_tasks_G[current_index_task].Period = 0;
	SCH_tasks_G[current_index_task].RunMe = 0;
}

/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2023
 *      Author: TuanAnh
 */

#include "scheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TICK				10
#define PRESCALER			64
#define COUNTER_START 		65536 - TICK * 1000 * 16 / 64	// 16M is Core Clock

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint8_t TaskID;
} sTask;

static sTask SCH_tasks_G[SCH_MAX_TASKS];
// static uint8_t array_Of_Task_ID[SCH_MAX_TASKS];
// static uint8_t newTaskID = 0;
// static uint32_t rearQueue = 0;
// static uint32_t count_SCH_Update = 0;

void SCH_Go_To_Sleep() {
	// todo
}

void SCH_Init(void) {
	for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
	// Error_code_G = 0;
	// Timer_init();
	//Watchdog_init();
}

void SCH_Update(void) {
	for (uint8_t index = 0; index < SCH_MAX_TASKS; index++) {
		if (SCH_tasks_G[index].pTask) {
			if (SCH_tasks_G[index].Delay == 0) {
				SCH_tasks_G[index].RunMe++;
				if (SCH_tasks_G[index].Period) {
					SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
				}
			} else {
				SCH_tasks_G[index].Delay--;
			}
		}
	}
}

uint8_t SCH_Add_Task(void (*pFuntion)(void), uint32_t DELAY, uint32_t PERIOD) {
	uint8_t index = 0;
	// find a gap
	while ((SCH_tasks_G[index].pTask) && index < SCH_MAX_TASKS) {
		index++;
	}
	if (index == SCH_MAX_TASKS) {
		return SCH_MAX_TASKS;
	}

	SCH_tasks_G[index].pTask = pFuntion;
	SCH_tasks_G[index].Delay = DELAY/TICK;
	SCH_tasks_G[index].Period = PERIOD/TICK;
	SCH_tasks_G[index].RunMe = 0;

	return index;
}

void SCH_Dispatch_Tasks(void) {
	for (uint8_t index = 0; index < SCH_MAX_TASKS; index++) {
		if (SCH_tasks_G[index].RunMe > 0) {
			(*SCH_tasks_G[index].pTask)(); // run task
			SCH_tasks_G[index].RunMe--;
			if (SCH_tasks_G[index].Period == 0) {
				SCH_Delete_Task(index);
			}
		}
	}

	//SCH_Report_Status();
	SCH_Go_To_Sleep();
}

uint8_t SCH_Delete_Task(uint8_t taskID) {
	uint8_t Return_code = 0;
	if (SCH_tasks_G[taskID].pTask == 0) {
		Return_code = 0;
		return Return_code;
	} else {
		Return_code = 1;
	}
	SCH_tasks_G[taskID].pTask = 0x0000;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].RunMe = 0;

	return Return_code;
}




#ifdef __cplusplus
}
#endif

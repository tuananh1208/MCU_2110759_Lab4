/*
 * scheduler.h
 *
 *  Created on: Nov 28, 2023
 *      Author: TuanAnh
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

#define SCH_MAX_TASKS	10
#define NO_TASK_ID		0

#ifdef __cplusplus
extern "C" {
#endif

	void SCH_Init(void);
	void SCH_Update(void);
	uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
	void SCH_Dispatch_Tasks(void);
	uint8_t SCH_Delete_Task(uint8_t Task_ID);

#ifdef __cplusplus
}
#endif
#endif /* INC_SCHEDULER_H_ */

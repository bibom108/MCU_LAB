/*
 * mysch.h
 *
 *  Created on: Oct 18, 2021
 *      Author: Rnmorty
 */

#ifndef INC_MYSCH_H_
#define INC_MYSCH_H_
#define MAX_TASK 5
#define INF 100000
struct SCH_Task {
	void (*pFunc)(void);
	uint32_t delay;
	uint32_t period;
	uint32_t run;
};

void SCH_Init();
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t get_time();

#endif /* INC_MYSCH_H_ */

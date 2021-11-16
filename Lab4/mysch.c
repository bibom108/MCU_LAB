/*
 * mysch.c
 *
 *  Created on: Oct 18, 2021
 *      Author: Rnmorty
 */
#include "main.h"
#include "mysch.h"

struct SCH_Task SCH_task[MAX_TASK];
uint32_t time;
uint32_t newest;
int updated;

void SCH_Init(void) {
	for(int i = 0; i < MAX_TASK; i++) {
		SCH_task[i].delay = 0;
		SCH_task[i].pFunc = NULL;
		SCH_task[i].period = 0;
		SCH_task[i].run = 0;
	}
	time = 0;
	newest = 0;
	updated = -1;
}

void SCH_Sort_Delay(void){
	for (int i = 0; i < MAX_TASK; i++){
		int min_element_index = i;
		for (int j = i+1; j < MAX_TASK; j++){
			if (SCH_task[min_element_index].delay > SCH_task[j].delay)
				min_element_index = j;
		}
		struct SCH_Task temp = SCH_task[min_element_index];
		SCH_task[min_element_index] = SCH_task[i];
		SCH_task[i] = temp;
	}
}

uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	for (int i = 0; i < MAX_TASK; i++)
	{
		if (SCH_task[i].pFunc == NULL) {
			SCH_task[i].pFunc = pFunction;
			SCH_task[i].delay = DELAY;
			SCH_task[i].period = PERIOD;
			return 1;
		}
	}
	return 0;
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (taskID < 0 || taskID >= MAX_TASK) {
		return 0;
	}
	SCH_task[taskID].pFunc = NULL;
	SCH_task[taskID].delay = INF;
	SCH_task[taskID].period = 0;
	return 1;
}

void SCH_Update(void) {
	if ((newest + SCH_task[0].delay) <= get_time()){
		newest = get_time();
		updated = 1;
	}
//	time += 10;
}

void SCH_Dispatch_Tasks(void) {
	if (updated == 1){
		uint32_t time_passed = SCH_task[0].delay;
		for (int i = 0; i < MAX_TASK; i++){
			SCH_task[i].delay = SCH_task[i].delay - time_passed;
			if (SCH_task[i].delay == 0 && SCH_task[i].pFunc){
				(*SCH_task[i].pFunc)();
				if (SCH_task[i].period)
					SCH_task[i].delay = SCH_task[i].period;
				else SCH_Delete_Task(i);
			}
		}
		SCH_Sort_Delay();
		updated = 0;
	}
	else if (updated == -1){
		SCH_Sort_Delay();
		updated = 0;
	}
}

uint32_t get_time(){
	return HAL_GetTick();
}

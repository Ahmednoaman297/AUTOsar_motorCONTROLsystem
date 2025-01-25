/*
 * OS_CONFIG.h
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#ifndef OS_OS_CONFIG_H_
#define OS_OS_CONFIG_H_
/********************************************Includes*********************************/
#include "OS.h"
#include "../APP/TASKS/TASKS.h"




/********************************************definition and macros*********************************/
#define MAX_TASKS 10



/********************************************shared global variables*********************************/
extern TaskDescriptor taskList[MAX_TASKS];
extern const uint8_t NUMBER_OF_tasks;


#endif /* OS_OS_CONFIG_H_ */

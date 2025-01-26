/*
 * OS.h
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#ifndef OS_OS_H_
#define OS_OS_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include "../MCAL/SYSTICK/SYSTICK.h"

/******************************************** Type Declarations *********************************/
typedef struct {
    void (*task)(void);         /* Function pointer to task execution */
    uint32_t priodicity;        /* Task interval in ticks */
    uint32_t tickCount;         /* Count of ticks since last execution */
    bool isPreiodic;            /* True if the task is recurring */
    bool isHighPriority;        /* True if the task has high priority (e.g., initialization) */
    bool isSuspended;           /* True if the task is suspended */
} TaskDescriptor;

/******************************************** Function Prototypes *********************************/
void OS_Init(void);
void OS_Run(void);
void OS_Stop(void);                        /* Stop all tasks */
void OS_Resume(void);                      /* Resume all tasks */
void OS_SuspendTask(uint8_t a_taskIndex);    /* Suspend a specific task */
void OS_ResumeTask(uint8_t a_taskIndex);     /* Resume a specific task */



#endif /* OS_OS_H_ */

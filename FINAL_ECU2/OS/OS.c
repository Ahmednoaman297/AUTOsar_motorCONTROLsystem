/*
 * OS.c
 *
 * Module Name: OS
 * Author: elder
 * Purpose: Scheduling tasks
 */

/************************************************************** Includes *********************************************************************/
#include "OS.h"
#include "OS_CONFIG.h"

/******************************************************* Global and Static Variables *********************************************************/
uint8_t g_OS_intTasksFlag = 1;
static bool osRunning = true;  /* OS running state */

/******************************************************* Functions Definitions ***************************************************************/

/***************************************************************
Function Name   : OS_Init
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Initializes the operating system by setting the initial values for the
                  system tick flag, and for each task in the task list, it initializes
                  the tick count to zero and sets the task's suspended state to false
                  (not suspended).
****************************************************************/

void OS_Init(void)
{
    SYSTICK_Flag = ZERO;
    uint8_t i;
    for (i = ZERO; i < NUMBER_OF_tasks; i++) {
        taskList[i].tickCount = ZERO;
        taskList[i].isSuspended = false;  /* Initialize all tasks as not suspended */
    }
}

/***************************************************************
Function Name   : OS_Run
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Executes tasks based on the system tick, considering each task's
                  periodicity and suspended state. It ensures that high-priority tasks
                  are executed before low-priority tasks. The function handles the tick
                  counter for periodic tasks and executes them accordingly.
****************************************************************/

void OS_Run(void)
{
    if (!osRunning) {
        return;  /* Exit if OS is stopped */
    }

    static volatile uint32_t LAST_SYSTICK_VALUE = 0;
    uint32_t NUMBER_OF_TICK_PASSED = SYSTICK_Flag - LAST_SYSTICK_VALUE;
    LAST_SYSTICK_VALUE = SYSTICK_Flag;

    uint8_t k;
    for (k = ZERO; k < NUMBER_OF_tasks; k++) {
        if ((taskList[k].isSuspended) || (taskList[k].tickCount == ZERO)) {
            continue;  /* Skip suspended tasks or tasks not ready to run */
        }

        if (taskList[k].tickCount > ZERO && !taskList[k].isHighPriority) {
            taskList[k].tickCount -= NUMBER_OF_TICK_PASSED;
        }

        if (taskList[k].tickCount > taskList[k].priodicity && !taskList[k].isHighPriority) {
            taskList[k].tickCount = (uint32_t)0;
        }

        //        if (taskList[k].tickCount == ZERO && !taskList[k].isSuspended) {
        //            taskList[k].task();  /* Execute the task */
        //            taskList[k].tickCount = taskList[k].priodicity;  /* Reset the tick count */
        //        }
    }

    if (g_OS_intTasksFlag == (uint8_t)1) {
        uint8_t i;
        for (i = ZERO; i < NUMBER_OF_tasks; i++) {
            if (taskList[i].isHighPriority && taskList[i].tickCount == ZERO && !taskList[i].isSuspended) {
                taskList[i].task();
                taskList[i].tickCount = (uint32_t)123;
            }
        }
        g_OS_intTasksFlag = ZERO;
    }
    uint8_t l;
    for ( l = (uint8_t)0; l < (uint8_t)NUMBER_OF_tasks; l++)
    {
        if (taskList[l].tickCount == (uint32_t)0&& !taskList[l].isSuspended)
        {
            taskList[l].task();
            if (taskList[l].isPreiodic)
            {
                taskList[l].tickCount = taskList[l].priodicity;
            }
        }
    }
}

/***************************************************************
Function Name   : OS_Stop
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Stops the operating system by setting the `osRunning` flag to false.
****************************************************************/

void OS_Stop(void)
{
    osRunning = false;  /* Stop the OS */
}

/***************************************************************
Function Name   : OS_Resume
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Resumes the operating system by setting the `osRunning` flag to true.
****************************************************************/

void OS_Resume(void)
{
    osRunning = true;  /* Resume the OS */
}

/***************************************************************
Function Name   : OS_SuspendTask
Inputs          : uint8_t a_taskIndex - The index of the task to be suspended.
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Suspends the task at the specified index by setting its `isSuspended` flag to true.
****************************************************************/

void OS_SuspendTask(uint8_t a_taskIndex)
{
    if (a_taskIndex < NUMBER_OF_tasks) {
        taskList[taskIndex].isSuspended = true;  /* Mark the task as suspended */
    }
}

/***************************************************************
Function Name   : OS_ResumeTask
Inputs          : uint8_t a_taskIndex - The index of the task to be resumed.
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Resumes the task at the specified index by setting its `isSuspended` flag to false.
****************************************************************/

void OS_ResumeTask(uint8_t a_taskIndex)
{
    if (a_taskIndex < NUMBER_OF_tasks) {
        taskList[taskIndex].isSuspended = false;  /* Mark the task as not suspended */
    }
}

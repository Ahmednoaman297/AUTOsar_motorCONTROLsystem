/*
 * Monitoring_Mechanisms.c
 *
 *  Created on: Jan 3, 2025
 *      Author: Ahmedmohamed
 */

#include "Monitoring_Mechanisms.h"
#include "APP/TASKS/TASKS.h"
uint8_t MONITORING_DTC_FLAG = 0;

/***************************************************************
Function Name   : Monitor_Communication
Inputs          : uint32_t code_error - The error code indicating the type of communication issue.
Outputs         : None
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles different error scenarios (FAULT, Connection Lost, Overheat) by performing
                  necessary actions such as suspending tasks, sending error messages via UART and CAN,
                  and triggering LED blinks. It also updates Non-Volatile Memory (NVM) to store error
                  states and flags.
                  The function handles the following error codes:
                  - FAULT_code: Trigger fault handling procedures.
                  - lostCOM_code: Handle communication loss and monitor retries.
                  - OverHeat_code: Handle overheat condition and monitor retries.
****************************************************************/

void Monitor_Communication(uint32_t code_error) {

    switch (code_error)
    {
    case FAULT_code:
    {
        MONITORING_DTC_FLAG = (uint8_t)1;
        OS_SuspendTask((uint8_t)0);
        OS_SuspendTask((uint8_t)2);
        OS_SuspendTask((uint8_t)4);
        OS_SuspendTask((uint8_t)6);
        OS_SuspendTask((uint8_t)7);
        OS_SuspendTask((uint8_t)8);
        UART_FLAG_SEND = FAULT_STATE;
        /*send fault */
        uint8_t task_recCAN_tempSTATE=(uint8_t)FAULT_STATE;
        CANTransmit((uint8_t)CAN0_Index,(uint8_t) 5,(uint8_t*)&task_recCAN_tempSTATE, (uint32_t)MSG_LENGTH, false);
        /*blink red */
        TASK_FLAGblink_REDled=(uint8_t)1;
        TASK_FLAGblink_Whiteled=(uint8_t)0;
        TASK_MONITOR_comLOST=(uint8_t)0;
        TASK_MONITOR_fault_STATE=(uint8_t)0;
        MONITOR_overHEAT=(uint8_t)3;

        NVM_Write((uint32_t)0x100, (uint32_t)FAULT_code);
        /*blink_redled */
    }
    break;
    case lostCOM_code:
    {
        UART_FLAG_SEND = Connection_lost;
        TASK_FLAGblink_BLUEled=(uint8_t)1;

        NVM_Read((uint32_t)0x200, (uint32_t*)&consecutive_counterConnection);
        TASK_MONITOR_comLOST=(uint8_t)0;
        TASK_MONITOR_fault_STATE=(uint8_t)0;
        MONITOR_overHEAT=(uint8_t)3;
        if(consecutive_counterConnection<(uint8_t)2)
        {
            consecutive_counterConnection++;
            NVM_Write((uint32_t)0x200, (uint32_t)consecutive_counterConnection);

        }
        else
        {
            consecutive_counterConnection++;
            NVM_Write((uint32_t)0x200, (uint32_t)consecutive_counterConnection);
            MONITORING_DTC_FLAG =(uint8_t)1;
            OS_SuspendTask((uint8_t)0);
            OS_SuspendTask((uint8_t)2);
            OS_SuspendTask((uint8_t)5);
            OS_SuspendTask((uint8_t)6);
            OS_SuspendTask((uint8_t)7);
            OS_SuspendTask((uint8_t)8);
            /*blink blue led */
            /*TASK_FLAGblink_BLUEled=1; */
        }
    }
    break;
    case OverHeat_code:
    {
        UART_FLAG_SEND = OverHeat_code;
        /*counter to calc 3 consecutive */

        /*send overheat */
        uint8_t task_recCAN_tempSTATE=(uint8_t)OverHeat_code;
        CANTransmit((uint8_t)CAN0_Index, (uint8_t)5,(uint8_t*)&task_recCAN_tempSTATE, (uint32_t)MSG_LENGTH, false);
        /* stop motor */
        DIO_writePin((uint32_t)GPIO_PORTE_BASE, (uint8_t)GPIO_PIN_5, (uint8_t)1);
        /*blink white */
        TASK_FLAGblink_Whiteled=(uint8_t)1;
        TASK_FLAGblink_REDled=(uint8_t)0;
        /*unexpected_temp=0; */


        TASK_MONITOR_comLOST=(uint8_t)0;
        TASK_MONITOR_fault_STATE=(uint8_t)0;
        MONITOR_overHEAT=(uint8_t)3;

        NVM_Read((uint32_t)0x300, (uint32_t*)&consecutive_counteroverHEAT);
        if(consecutive_counteroverHEAT<(uint8_t)2)
        {
            consecutive_counteroverHEAT++;
            NVM_Write((uint32_t)0x300, (uint32_t)consecutive_counteroverHEAT);

        }
        else
        {
            consecutive_counteroverHEAT++;
            NVM_Write((uint32_t)0x300, (uint32_t)consecutive_counteroverHEAT);
            MONITORING_DTC_FLAG =(uint8_t)1;
            OS_SuspendTask((uint8_t)0);
            OS_SuspendTask((uint8_t)2);
            OS_SuspendTask((uint8_t)4);
            OS_SuspendTask((uint8_t)5);
            OS_SuspendTask((uint8_t)7);
            OS_SuspendTask((uint8_t)8);
            /*blink blue led */
            /*TASK_FLAGblink_BLUEled=1; */
        }
    }
    break;
    default:
        break;
    }

}





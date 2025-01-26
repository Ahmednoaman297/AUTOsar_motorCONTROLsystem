/*
 * TASKS.h
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#ifndef APP_TASKS_TASKS_H_
#define APP_TASKS_TASKS_H_

/********************************************Includes*********************************/

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "../../HAL/LED/LED.h"
#include "../../HAL/BTN/BTN.h"
#include "../../MCAL/CAN/CAN.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../MCAL/UARTs/UARTS.h"
#include "../../OS/OS.h"
#include "../../MCAL/ADC/ADC.h"


/********************************************Definitions and Macros*********************************/


#define INIT_ZERO               0u
#define CONDITION_ZERO          0u

#define SetFlag                 1u
#define ConditionFlag           1u

#define SetSEAMPHORE            1u
#define ConditionSEAMPHORE      1u

#define CAN0_Index                      0u
#define MSG_LENGTH                      1u
#define DataErrorSendingObject          1u
#define TempSensorObject                1u
#define ISConnectedSendingObject        4u
#define ISConnectedReceivingObject      3u
#define REMOTEFRAME_OBJECT              2u
#define STATEOBJECT                     5u
#define QUEUE_LEN                       30


#define PRESSED                 0u
#define NOTPRESSED              1u
#define FIRST_SWITCH          GPIO_PIN_0      /* Indicates the first button which sends the first state*/
#define SECOND_SWITCH         GPIO_PIN_4

#define REDLED               GPIO_PIN_1
#define BLUELED              GPIO_PIN_2
#define GREENLED             GPIO_PIN_3
#define GPIO_PORTF_Index        0u


#define BLUE                    3u
#define WHITE                   6u
#define GREEN                   3u
#define RED                     22u
#define TESTREDLED              50u
#define TESTGREENLED            52u
#define TESTBLUELED             51u
#define TESTWHITELED            53u
#define ENTERTESTING            57u
#define EXITTESTING             58u

#define CW                      1u
#define CCW                     2u
#define Initial                 3u
#define HoldSTATE               4u
#define Unidentefied_state      9u
#define IDLE_STATE              6u

#define CheckVoltage            88u


/********************************************functions prototypes*********************************/

void TASK_INITS (void);
void TASK_ReceiveCAN(void);
void TASK_RECEIVED_DATA_CHECK (void);
void TASK_REDLED (void);
void TASK_GREENLED (void);
void TASK_WHITELED (void);
void TASK_errorCheck(void);
void TASK_TempCheck (void);
void TASK_blinkBlueLED (void);
void TASK_RemoteFrame (void);
void mohamed(int num, char *str, int base);
void SUSPEND_ALL(void);
void RESUME_ALL(void);



#endif /* APP_TASKS_TASKS_H_ */

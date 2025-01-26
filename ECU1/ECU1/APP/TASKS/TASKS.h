/*
 * TASKS.h
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#ifndef APP_TASKS_TASKS_H_
#define APP_TASKS_TASKS_H_
/*************************************************************Includes**************************************************************/
#include "Service/OS/OS.h"
#include <stdint.h>
#include <stdbool.h>
#include "HAL/LED/LED.h"
#include "HAL/BTN/BTN.h"
#include "MCAL/CAN/CAN.h"
#include "MCAL/gpio/gpio.h"
#include "MCAL/SYSTICK/SYSTICK.h"
#include "MCAL/UARTs/UARTS.h"
#include "Service/MONITORING/Monitoring_Mechanisms.h"
#include "MCAL/E2PROM/E2PROM.h"
/********************************************Definitions and Macros*********************************/
#define INIT_ZERO               0u
#define CONDITION_ZERO          0u

#define SetFlag                 1u
#define ConditionFlag           1u

#define PRESSED                 0u
#define NOTPRESSED              1u
#define FIRST_SWITCH          GPIO_PIN_0      /* Indicates the first button which sends the first state*/
#define SECOND_SWITCH         GPIO_PIN_4

#define ENTER_TESTER            57u
#define EXIT_TESTER             58u
#define NORMAL_TEMP             3u
#define NOT_NORMAL_TEMP         9u
#define Connection_lost         8u
#define OverHeat_code           6u
#define FAULT_code              4u
#define NO_DATATOSEND           0u
#define SENDERRORCHECK          7u
#define lostCOM_code            5u
#define CAN0_Index                          0u
#define MSG_LENGTH                          1u
#define DataSendingObject                   1u
#define keep_ALIVEmsg                       4u
#define ISConnectedReceivingObject          3u
#define DATAERRORRECEIVING_OBJECT           2u
#define FAULT_STATE  22u

#define DIAGNOSTICsession                   44u
#define FAILEDoverHEAT                      45u
#define CONFIRMEDoverHEAT                   46u
#define FAILEDfault                         47u
#define CONFIRMEDfault                      48u
#define FAILEDlostcon                       49u
#define CONFIRMEDlostcon                    40u
#define Warning                             41u

#define TESTredLED                          50u
#define TESTblueLED                          51u
#define TESTgreenLED                          52u
#define TESTwhiteLED                          53u

#define TESTtemp                  54u
#define TESTvoltage               55u

#define White                   0u
#define Green                   1u
#define Red                     2u
#define Blue                    3u

#define ADDRESS_fault               0x100u
#define ADDRESS_communication       0x200u
#define ADDRESS_overheat            0x300u

#define TASTKS_INITS_valueINDEX                    0u
#define TASK_BTN_READ_valueINDEX                   1u
#define TASK_ReceiveCAN_valueINDEX                 2u
#define TASK_UARTSEND_valueINDEX                   3u
#define TASK_blinkBlueLED_valueINDEX               4u
#define TASK_blinkRedLED_valueINDEX                5u
#define TASK_blinkWhiteLED_valueINDEX              6u
#define keep_ALIVE_valueINDEX                      7u
#define ADC_health_check_valueINDEX                8u
#define monitoring_task_checker_valueINDEX         9u
#define ON_BoardDIAGnostic_valueINDEX              10u
#define TESTER_mode_valueINDEX                     11u
#define TASK_UARTreceive_valueINDEX                12u

/**********************************Function Defintions********************************************/

void TASK_INITS (void);
void TASK_BTN_READ(void);
void TASK_LEDGREEN(void);
void TASK_LEDRED(void);
void TASK_LEDWHITE(void);
void TASK_LEDBLUE(void);
void TASK_CLOCKWISE(void);
void TASK_COUNTERCLOCKWISE(void);
void TASK_UARTSEND (void);
void TASK_SendCAN (void);
void TASK_ReceiveCAN (void);
void keep_ALIVE (void);
void TASK_blinkRedLED (void);
void TASK_blinkBlueLED (void);
void TASK_blinkWhiteLED (void);
void Task_UARTTRIAL(void);
void ADC_health_check(void);
void can_send(void);
void monitoring_task_checker(void);
void ON_BoardDIAGnostic(void);
void TESTER_mode(void);

/*******************************************************Shared Global Variable(extern)**********************************************************/
extern uint8_t TASK_STATE;
extern uint8_t TASK_LED;
uint8_t task_buttonCOUNT;
extern  uint8_t TASK_FLAGblink_REDled;
extern uint8_t TASK_FLAGblink_BLUEled;
extern uint8_t TASK_FLAGblink_Whiteled;
extern uint32_t consecutive_counteroverHEAT;
extern uint8_t INIT_FLAG;
extern uint8_t MONITOR_overHEAT;
extern uint8_t TASK_MONITOR_fault_STATE;
extern uint8_t UART_FLAG_SEND;
extern uint8_t TASK_MONITOR_comLOST;

extern uint32_t consecutive_counterConnection;

#endif /* APP_TASKS_TASKS_H_ */

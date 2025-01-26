/*
 * Monitoring_Mechanisms.h
 *
 *  Created on: Jan 3, 2025
 *      Author: Ahmedmohamed
 */

#ifndef SERVICE_MONITORING_MECHANISMS_H_
#define SERVICE_MONITORING_MECHANISMS_H_

#include <stdint.h>
#include "HAL/LED/LED.h"
#include "Service/NVM/NVM.h"
#include "APP/TASKS/TASKS.h"
#include "MCAL/UARTs/UARTS.h"
#include "MCAL/CAN/CAN.h"
#include "../OS/OS.h"
/* Function prototypes for monitoring */
void Monitor_Communication(uint32_t code_error) ;


extern uint8_t MONITORING_DTC_FLAG;


#endif /* SERVICE_MONITORING_MECHANISMS_H_ */

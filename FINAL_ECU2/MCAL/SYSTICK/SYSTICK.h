/*
 * SYSTICK.h
 *
 *      ModuleName: SYSTICK
 *      Author: Ahmedmohamed
 *      Purpose: Header file for SYSTICK Driver
 */
#ifndef SYSTICK_H_
#define SYSTICK_H_

/*************************************************************Includes**************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"
#include "../../HAL/LED/LED.h"

/********************************************Definitions and Macros******************************************************************/
#define MS_TO_S 1000U


/*********************************************Shared Global Variable(extern)**********************************************************/
extern volatile uint32_t  SYSTICK_Flag;


/*******************************************************Function Prototypes**********************************************************/
void SYSTICK_delayMSec(uint32_t a_msec);
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */

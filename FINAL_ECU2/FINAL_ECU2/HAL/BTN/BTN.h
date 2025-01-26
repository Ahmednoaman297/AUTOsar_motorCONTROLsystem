/*
 * BTN.h
 *
 *      ModuleName: BTN
 *      Author: Ahmedmohamed
 *      Purpose: Header file for BTN Driver
 */

#ifndef BTN_H_
#define BTN_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "../../MCAL/DIO/dio.h"

/********************************************Definitions and Macros*********************************/
#define BTN_0     GPIO_PIN_0
#define BTN_4     GPIO_PIN_4


/********************************************functions prototypes*********************************/
uint8_t BTN_read (uint8_t a_btn , uint32_t a_base);

#endif /* BTN_H_ */

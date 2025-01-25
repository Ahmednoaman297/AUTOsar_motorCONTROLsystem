/*
 * dio.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Mostafa elder
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

/*************************************************************Includes**************************************************/

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"


/*******************************************************Definitions and Macros***************************************/
#define ZERO ((uint8_t)0)
#define VALUE_ONE ((uint8_t)1)


/**************************************************functions prototypes***********************************************/
uint8_t DIO_readPin(uint8_t a_pin , uint32_t a_base);
uint8_t DIO_writePin(uint32_t a_base , uint8_t a_pin  , uint8_t a_value);


#endif /* MCAL_DIO_DIO_H_ */

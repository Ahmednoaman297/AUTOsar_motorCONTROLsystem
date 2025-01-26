/*
 * gpio.c
 *
 *      Created on: Dec 10, 2024
 *      Author: Mostafa elder
 *
 */

#ifndef GPIO_H_
#define GPIO_H_
/********************************************Includes*********************************/
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
/*******************************************************Definitions and Macros**********************************************************/
#define ZERO_GPIO 0u
#define GPIO_ERROR 12u
/*******************************************************Type Declaration(struct)**********************************************************/
typedef struct {
   uint8_t Input_pin;
   uint8_t Type;
   uint8_t Strength;
} InputPin_Cfg;

typedef struct {
    uint32_t Peripheral;
    uint32_t Base;
    InputPin_Cfg *InputPins;
    uint8_t InputPinsCount;    /* Length of InputPins array*/
    uint8_t *OutputPins;
    uint8_t OutputPinsCount;   /* Length of OutputPins array*/
} GPIO_Param;

/********************************************functions prototypes*********************************/
uint8_t GPIO_init (uint8_t a_Index);

#endif /* GPIO_H_ */

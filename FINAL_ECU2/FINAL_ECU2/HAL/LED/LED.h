/*
 * LED.h
 *
 *      ModuleName: LED
 *      Author: Ahmedmohamed
 *      Purpose: Header file for LED Driver
 */

#ifndef LED_H_
#define LED_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "../../MCAL/DIO/dio.h"



/********************************************Definitions and Macros*********************************/
#define RED_LED     ((uint8_t)GPIO_PIN_1)
#define BLUE_LED    ((uint8_t)GPIO_PIN_2)
#define GREEN_LED   ((uint8_t)GPIO_PIN_3)
#define OFF             ((uint8_t)0)
#define ON              ((uint8_t)1)


/********************************************functions prototypes*********************************/
void LED_blueLight(void);
void LED_greenLight(void);
void LED_redLight(void);
void LED_whiteLight(void);
void LEDS_off(void);
uint8_t LED_read (uint8_t a_led , uint32_t a_base);


#endif /* LED_H_ */

/*
 * gpioConfig.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Mostafa elder
 */

#include "gpioConfig.h"

InputPin_Cfg INPUTS_PORTF[]={
                       {.Input_pin  = GPIO_PIN_0,
                        .Type       = GPIO_PIN_TYPE_STD_WPU,
                        .Strength   = GPIO_STRENGTH_2MA},

                        {.Input_pin = GPIO_PIN_4,
                         .Type      = GPIO_PIN_TYPE_STD_WPU,
                         .Strength  = GPIO_STRENGTH_2MA}
};
uint8_t OUTPUTS_PORTF[]={GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3};

GPIO_Param Parameters[NumberOfGPIO] ={
                          {
                           .Peripheral      = SYSCTL_PERIPH_GPIOF,
                           .Base            = GPIO_PORTF_BASE,
                           .InputPins       = INPUTS_PORTF,
                           .InputPinsCount  = sizeof(INPUTS_PORTF) / sizeof(INPUTS_PORTF[0]),
                           .OutputPins      = OUTPUTS_PORTF,
                           .OutputPinsCount = sizeof(OUTPUTS_PORTF) / sizeof(OUTPUTS_PORTF[0])
                          }
};



/*
 * ADC.h
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */
#ifndef ADC_H_
#define ADC_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

/********************************************Definitions and Macros*********************************/

#define NUM_SAMPLES 5

/********************************************Shared Global Variables(extern)*********************************/

extern const ADC_ConfigType ADC_CONFIGURATIONS[];
extern const uint32_t ADC_CONFIGURATIONS_COUNT;


/********************************************Type Declerations(structs)*********************************/

typedef struct {
    uint32_t ADC_base;
    uint32_t sequence;
    uint32_t pin;
} ADC_ConfigType;


/********************************************functions prototypes*********************************/

void ADC_Init(void);
uint32_t ADC_ReadValue(uint32_t a_Base, uint32_t a_sequence);
uint32_t ADC_ComputeAverage(uint32_t *samples_ptr);

#endif /* ADC_H_ */

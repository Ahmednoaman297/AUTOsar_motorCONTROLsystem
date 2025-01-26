/*
 * ADC.h
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

// Define the ADC_ConfigType structure
typedef struct {
    uint32_t ADC_base;     // ADC base address (ADC0_BASE or ADC1_BASE)
    uint32_t sequence;     // ADC sequence number (e.g., 0, 1, 2, or 3)
    uint32_t pin;          // GPIO pin number (e.g., GPIO_PIN_3 for PE3)
} ADC_ConfigType;

// Extern declaration of configurations
extern const ADC_ConfigType ADC_Configurations[];
extern const uint32_t ADC_Configurations_Count;

void ADC_Init(void);

#endif /* ADC_H_ */

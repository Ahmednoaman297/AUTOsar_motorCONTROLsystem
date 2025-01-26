/*
 * ADC_cfg.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */

#include "ADC_Cfg.h"

// Define ADC configurations
const ADC_ConfigType ADC_Configurations[] = {
    {ADC0_BASE, 3, GPIO_PIN_3}, // ADC0, sequence 3, pin PE3
    {ADC1_BASE, 3, GPIO_PIN_2}  // ADC1, sequence 3, pin PE2
};

// Define the number of configurations
const uint32_t ADC_Configurations_Count = sizeof(ADC_Configurations) / sizeof(ADC_ConfigType);

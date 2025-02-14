/*
 * ADC_cfg.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */

#include "ADC_Cfg.h"

/*******************************************************Functions Definitions**********************************************************/

const ADC_ConfigType ADC_Configurations[] = {
    {ADC0_BASE, 3, GPIO_PIN_3},
    {ADC0_BASE, 0, GPIO_PIN_2}
};

const uint32_t ADC_Configurations_Count = sizeof(ADC_Configurations) / sizeof(ADC_ConfigType);

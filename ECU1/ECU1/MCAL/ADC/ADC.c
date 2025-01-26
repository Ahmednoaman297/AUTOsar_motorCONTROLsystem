/*
 * ADC.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */
#include "ADC.h"
#include "ADC_Cfg.h"

void ADC_Init(void) {
    uint32_t i;

    // Loop through all ADC configurations
    for (i = 0; i < ADC_Configurations_Count; i++) {
        const ADC_ConfigType *config = &ADC_Configurations[i];

        // Enable GPIO port for ADC pins
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {
            // Wait for GPIOE to be ready
        }

        // Configure the pin as an ADC input
        GPIOPinTypeADC(GPIO_PORTE_BASE, config->pin);

        // Enable the ADC peripheral
        if (config->ADC_base == ADC0_BASE) {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
            while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) {
                // Wait for ADC0 to be ready
            }
        } else if (config->ADC_base == ADC1_BASE) {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
            while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1)) {
                // Wait for ADC1 to be ready
            }
        }

        // Configure the ADC sequencer
        ADCSequenceConfigure(config->ADC_base, config->sequence, ADC_TRIGGER_PROCESSOR, 0);
        ADCSequenceStepConfigure(config->ADC_base, config->sequence, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
        ADCSequenceEnable(config->ADC_base, config->sequence);

        // Clear any pending interrupt for the sequence
        ADCIntClear(config->ADC_base, config->sequence);
    }
}

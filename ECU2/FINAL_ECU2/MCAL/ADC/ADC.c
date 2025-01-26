/*
 * ADC.c
 *
 * Created on: Jan 2, 2025
 * Author: Ahmedmohamed
 */
#include "ADC.h"
#include "ADC_Cfg.h"

/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : ADC_Init
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Initializes the ADC module by enabling peripherals for GPIO and ADC channels,
                  configuring ADC sequences, and setting up the necessary ADC steps based on the
                  configuration provided in `ADC_CONFIGURATIONS`.
 ****************************************************************/

void ADC_Init(void) {

    uint32_t i;

    for (i = (uint32_t)0; i < ADC_Configurations_Count; i++) {
        const ADC_ConfigType *config = &ADC_Configurations[i];
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) {

        }


        GPIOPinTypeADC(GPIO_PORTE_BASE, config->pin);


        if (config->ADC_base == ADC0_BASE) {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
            while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) {

            }
        } else if (config->ADC_base == ADC1_BASE) {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
            while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1)) {

            }
        }


        ADCSequenceConfigure(config->ADC_base, config->sequence, ADC_TRIGGER_PROCESSOR, 0);
        if (config->pin == GPIO_PIN_3) { // PE3 -> AIN0
            ADCSequenceStepConfigure(config->ADC_base, config->sequence, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
        } else if (config->pin == GPIO_PIN_2) { // PE2 -> AIN1
            ADCSequenceStepConfigure(config->ADC_base, config->sequence, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
        }
        ADCSequenceEnable(config->ADC_base, config->sequence);

        ADCIntClear(config->ADC_base, config->sequence);
    }
}

/***************************************************************
Function Name   : ADC_ReadValue
Inputs          : uint32_t a_Base, uint32_t a_sequence
Outputs         : uint32_t a_Value
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Triggers the ADC conversion on the specified ADC base and sequence,
                  waits for the conversion to complete, retrieves the ADC value,
                  clears the interrupt flag, and returns the value.
 ****************************************************************/


uint32_t ADC_ReadValue(uint32_t a_Base, uint32_t a_sequence)
{
    uint32_t a_Value;

    ADCProcessorTrigger(a_Base, a_sequence);
    while (!ADCIntStatus(a_Base, a_sequence, false));
    ADCSequenceDataGet(a_Base, a_sequence, &a_Value);
    ADCIntClear(a_Base, a_sequence);

    return a_Value;
}

/***************************************************************
Function Name   : ADC_ComputeAverage
Inputs          : uint32_t *samples_ptr
Outputs         : uint32_t a_x
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Computes the average of the samples in the provided array,
                  applies a transformation to the average, and returns the result.
 ****************************************************************/

uint32_t ComputeAverage(uint32_t *samples_ptr){
    uint32_t sum = 0;
    int i =0;
    for (i=0; i < NUM_SAMPLES; i++) {
        sum += samples_ptr[i];
    }
    uint32_t a_x = 50 + ((sum / NUM_SAMPLES - 50) * (200 - 50)) / (2000 - 50);

    return a_x;
}


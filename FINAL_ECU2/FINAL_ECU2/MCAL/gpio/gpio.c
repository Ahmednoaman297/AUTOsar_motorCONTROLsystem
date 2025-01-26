/*
 * gpio.c
 *
 *      Created on: Dec 10, 2024
 *      Author: Mostafa elder
 */
/**************************************************************************************************************************
 *                                                      Includes
 * ***********************************************************************************************************************/
#include "gpio.h"
#include "gpioConfig.h"
/***************************************************************
Function Name   : GPIO_init
Inputs          : uint8_t a_Index
Outputs         : uint8_t GPIO_state
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Configures GPIO pins for input and output functionality on Port F and Port A.
 ****************************************************************/
uint8_t GPIO_init (uint8_t a_Index)
{
    uint8_t GPIO_state = ZERO_GPIO;
    uint8_t GPIO_counter=ZERO_GPIO;
    /*Enable the GPIOF peripheral for the buttons*/
    SysCtlPeripheralEnable(Parameters[a_Index].Peripheral);
    while(!SysCtlPeripheralReady(Parameters[a_Index].Peripheral)){
        GPIO_counter++;
        if(GPIO_counter>=(uint8_t)30){
            GPIO_state= GPIO_ERROR ;
        }
    }
    GPIO_counter=ZERO_GPIO;
    if(Parameters[a_Index].Base==(uint32_t)GPIO_PORTF_BASE){
        HWREG((uint32_t)(GPIO_PORTF_BASE + GPIO_O_LOCK)) = (uint32_t)GPIO_LOCK_KEY;
        HWREG((uint32_t)(GPIO_PORTF_BASE + GPIO_O_CR)) |= (uint32_t)0x01;
        HWREG((uint32_t)(GPIO_PORTF_BASE + GPIO_O_LOCK)) = ZERO_GPIO;

    }
    else{
    }
    /* Configure the  pins as input and output*/
    uint8_t i;
    for (i = ZERO_GPIO; i<Parameters[a_Index].InputPinsCount;i++)
    {
        GPIOPinTypeGPIOInput((uint32_t)Parameters[a_Index].Base, (uint32_t)Parameters[a_Index].InputPins[i].Input_pin);
        GPIOPadConfigSet((uint32_t)Parameters[a_Index].Base, (uint32_t)Parameters[a_Index].InputPins[i].Input_pin ,(uint32_t) Parameters[a_Index].InputPins[i].Strength, Parameters[a_Index].InputPins[i].Type);

    }
    for (i = ZERO_GPIO; i<Parameters[a_Index].OutputPinsCount;i++)
    {
        GPIOPinTypeGPIOOutput((uint32_t)Parameters[a_Index].Base, (uint32_t) Parameters[a_Index].OutputPins[i]);

    }
    return GPIO_state;
}

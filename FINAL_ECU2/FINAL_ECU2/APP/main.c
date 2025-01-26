

/**
 * main.c
 */
/********************************************Includes********************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../HAL/LED/LED.h"
#include "../HAL/BTN/BTN.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/UARTs/UARTS.h"
#include "../MCAL/CAN/CAN.h"
#include "../MCAL/gpio/gpio.h"
#include "../MCAL/SYSTICK/SYSTICK.h"
#include "../OS/OS.h"



/******************************************Definitions and Macros*********************************/

#define MS 1u

/******************************************PROTYPES*********************************/

/***************************************Functions Definitions***************************************/
int main(void)
{
    SysCtlClockSet((uint32_t)SYSCTL_SYSDIV_4 | (uint32_t)SYSCTL_USE_PLL | (uint32_t)SYSCTL_OSC_MAIN | (uint32_t)SYSCTL_XTAL_16MHZ);

    SYSTICK_delayMSec(MS);
    OS_Init();
    while (1)
    {

        OS_Run();
    }

}

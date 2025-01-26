
/*
 * LED.c
 *
 ModuleName: LED
 Author: Ahmedmohamed
 Purpose: Source file for LED Driver
 */

/**************************************************************Includes*********************************************************************/

#include "LED.h"


/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : LED_blueLight
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Turn on blue led
 ****************************************************************/

void LED_blueLight(void)
{
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)RED_LED, (uint8_t)OFF);
    DIO_writePin((uint32_t)GPIO_PORTF_BASE,(uint8_t) BLUE_LED, (uint8_t)ON); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE,(uint8_t) GREEN_LED,(uint8_t) OFF); /* Turn on LED*/

}

/***************************************************************
Function Name   : LED_greenLight
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Turn on green led
 ****************************************************************/

void LED_greenLight(void)
{
    DIO_writePin((uint32_t)GPIO_PORTF_BASE,(uint8_t) RED_LED, (uint8_t) OFF); /*Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)BLUE_LED, (uint8_t)OFF); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)GREEN_LED, (uint8_t)ON); /* Turn on LED*/

}

/***************************************************************
Function Name   : LED_redLight
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Turn on red led
 ****************************************************************/

void LED_redLight(void)
{
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)RED_LED,(uint8_t) ON); /*Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)BLUE_LED, (uint8_t)OFF); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)GREEN_LED, (uint8_t)OFF); /* Turn on LED*/

}

/***************************************************************
Function Name   : LED_whiteLight
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Turn on white led
 ****************************************************************/

void LED_whiteLight(void)
{
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)RED_LED, (uint8_t)ON); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)BLUE_LED, (uint8_t)ON); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE,(uint8_t) GREEN_LED, (uint8_t)ON); /* Turn on LED*/

}
/***************************************************************
Function Name   : LEDS_off
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Turn off All leds
 ****************************************************************/
void LEDS_off(void)
{
    DIO_writePin((uint32_t)GPIO_PORTF_BASE,(uint8_t) RED_LED, (uint8_t)OFF); /*Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)BLUE_LED, (uint8_t)OFF); /* Turn on LED*/
    DIO_writePin((uint32_t)GPIO_PORTF_BASE, (uint8_t)GREEN_LED, (uint8_t)OFF); /* Turn on LED*/
}

/***************************************************************
Function Name   : LED_read
Inputs          : uint8_t a_LED, uint32_t a_base
Outputs         : uint8_t LED
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Return the value of the LED
****************************************************************/
uint8_t LED_read (uint8_t a_led , uint32_t a_base)
{
    uint8_t LED = DIO_readPin(a_led, a_base);
    return  (LED & a_led) ? 1 : 0;
}


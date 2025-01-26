
/*
 * BTN.c
 *
 ModuleName: BTN
 Author: Ahmedmohamed
 Purpose: Source file for BTN Driver
 */
/**************************************************************Includes*********************************************************************/

#include "BTN.h"

/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : BTN_read
Inputs          : uint8_t a_btn,uint32_t a_base
Outputs         : uint8_t switchStatus_a_btn
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Return the value of the btn
****************************************************************/

uint8_t BTN_read (uint8_t a_btn , uint32_t a_base)
{
    uint8_t BTN = DIO_readPin(a_btn , a_base);
    return  (BTN & a_btn) ? 1 : 0;
}


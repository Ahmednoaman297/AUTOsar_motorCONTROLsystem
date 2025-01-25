/*
 * SYSTICK.c
 *
 *      ModuleName: SYSTICK
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for SYSTICK Driver
 */

/***************************************************Includes*********************************************************************************/

#include "SYSTICK.h"

/*******************************************************Global and Static Variables**********************************************************/
volatile uint32_t SYSTICK_Flag = 0;


/**********************************Function Defintions***************************************************************************************/

/***************************************************************
Function Name   : SysTick_Handler
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles the Systick interrupt and sets the global flag SYSTICK_Flag
                  to indicate the timer delay has completed.
 ****************************************************************/
void SysTick_Handler(void)
{
    SYSTICK_Flag++;
}




/********************************************************************
    Function Name   : SYSTICK_delayMsec
    Inputs          : a_msec
    Outputs         : void
    Reentrancy      : Non-Reentrant
    Synchronous     : ASynchronous
    Description     : Configures SysTick to generate a millisecond delay

 *******************************************************************/
void SYSTICK_delayMSec(uint32_t a_msec)
{
    /* Calculate the reload value // (  Desired Frequency/System Clock Frequency )-1*/
    uint32_t reloadValue = ((uint32_t)(SysCtlClockGet()) / MS_TO_S) * (uint32_t)(a_msec);
    /*set reloadValue in NVIC_ST_RELOAD REG */
    SysTickPeriodSet(reloadValue - (uint32_t)1);
    /*updates the vector table to point to  SysTick_Handler function. */
    SysTickIntRegister(&SysTick_Handler);
    /* Enable SysTick with interrupt */
    SysTickIntEnable();
    /* Enable Systick*/
    SysTickEnable();
    /* Enable global interrupt */
    IntMasterEnable();
}






/*
 * dio.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Mostafa elder
 */


/***************************************************Includes*********************************************************************************/

#include "dio.h"

/**********************************Function Defintions***************************************************************************************/

/***************************************************************
Function Name   :  DIO_readPin
Inputs          :  a_pin  (uint8_t)-b_base (uint32_t)
Outputs         :  uint8_t - The state of the specified pin (0 or 1).
Reentrancy      :  Reentrant
Synchronous     :  Synchronous
Description     :  Reads the value of the specified pin at the given
                   GPIO port and returns its state (0 or 1).
****************************************************************/


uint8_t DIO_readPin(uint8_t a_pin , uint32_t a_base)
{
    uint8_t value = GPIOPinRead(a_base,a_pin);
    return (value & a_pin);
}



/***************************************************************
Function Name   :  DIO_writePin
Inputs          :   a_base-a_pin-a_value
Outputs         :  uint8_t - Error status
Reentrancy      :  Reentrant
Synchronous     :  Synchronous
Description     :  Writes a specified value (0 or 1) to a given pin
                   at the specified GPIO port. Returns an error
                   status if the value is invalid.
****************************************************************/


uint8_t DIO_writePin(uint32_t a_base , uint8_t a_pin  , uint8_t a_value)
{

    uint8_t error=0;
    if (a_value==ZERO)
    {
        GPIOPinWrite(a_base, a_pin,ZERO);
    }
    else if(a_value==VALUE_ONE )
    {
        GPIOPinWrite(a_base, a_pin, a_pin);
    }
    else
    {
        /*update value with def error value */
    }
    return error;
}

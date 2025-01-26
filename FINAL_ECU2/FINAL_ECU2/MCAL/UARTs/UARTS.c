/*
 * UARTS.c
 *
 *  Created on: Dec 15, 2024
 *      Author: elder
 */
/**************************************************************Includes*********************************************************************/

#include "UARTS.h"
#include "UARTS_CONFIG.h"
/***************************************************************
Function Name   : UART_sendString
Inputs          : char *a_stringPtr
Outputs         : void - This function does not return any value.
Reentrancy      : Non-Reentrant
Synchronous     : Yes
Description     : This function transmits a null-terminated string over the UART interface. It sends each character in the
                  string one at a time, waiting for the UART to be ready before transmitting the next character. The function
                  continues sending characters until the null terminator (`'\0'`) of the string is encountered.
                  It is a blocking call and does not return until the entire string has been transmitted.
 ****************************************************************/

void UART_sendString(char *a_stringPtr,uint8_t a_Index) {
    uint8_t flag =0U;
    uint16_t i = 0U; /* Index for traversing the string */
    /* Validate the input pointer */
    if (a_stringPtr == NULL) {
        /* Null pointer detected, exit the function */
        flag ++;
    }

    /* Validate the UART index */
    if (a_Index >= UARTS_CONFIG_numUarts && flag==1u) {
        /* Invalid UART index, exit the function */
        flag ++;
    }

    /* Loop through the string until the null terminator is encountered */
    while (a_stringPtr[i] != '\0' && flag ==0u) {
        /* Send the current character in the string over the specified UART module */
        UARTCharPut((uint32_t)UARTS_CONFIG_array[a_Index].module, (uint8_t)a_stringPtr[i]);

        /* Increment the index to process the next character */
        i++;
    }
}


/***************************************************************
Function Name   : UART_receiveByte
Inputs          : uint8_t a_Index
Outputs         : int32_t g_data
Reentrancy      : Non-Reentrant.
Synchronous     : Yes .
Description     : This function waits for a byte of data to be received via the UART interface. It checks if data is available
                  in the UART receive (Rx) buffer, and once data is available, it retrieves the byte from the buffer. The function
                  blocks until at least one byte is received, then returns the byte to the caller. The function is blocking and
                  does not return until data is received.
 ****************************************************************/


int32_t UART_receiveByte(uint8_t a_Index)
{
    int32_t g_data;  /* Variable to store the received byte*/

    /* Wait until there is at least one character in the UART Rx buffer*/
    while(!UARTCharsAvail(UARTS_CONFIG_array[a_Index].module)){};

    /* Read the received data from the UART Rx buffer*/
    g_data = UARTCharGet(UARTS_CONFIG_array[a_Index].module);

    /* Return the received byte of data*/
    return g_data;
}


/***************************************************************
Function Name   : UART_config
Inputs          :-a_PTR: Pointer to a structure of type UartCFG containing:
Outputs         : uint8_t Uart_State
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Configures a UART module for communication with specified parameters.
                  Initializes the GPIO pins required for the UART functionality.
 ****************************************************************/
uint8_t UART_config(UartCFG a_PTR) {
    uint8_t Uart_State = UART_SUCCESS; /* Initialize UART state to success */

    /* Select the UART module base address */
    switch (a_PTR.module) {
    case (uint32_t)UART0_BASE:
            /* Enable UART0 and GPIOA peripherals */
            SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOA);

    /* Configure UART0 RX and TX pins */
    GPIOPinConfigure((uint32_t)GPIO_PA0_U0RX);
    GPIOPinConfigure((uint32_t)GPIO_PA1_U0TX);

    /* Set PA0 and PA1 as UART pins */
    GPIOPinTypeUART((uint32_t)GPIO_PORTA_BASE,
                    (uint8_t)((uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1));
    break;

    case (uint32_t)UART1_BASE:
            /* Enable UART1 and GPIOC peripherals */
            SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOC);

    /* Configure UART1 RX and TX pins */
    GPIOPinConfigure((uint32_t)GPIO_PC4_U1RX);
    GPIOPinConfigure((uint32_t)GPIO_PC5_U1TX);

    /* Set PC4 and PC5 as UART pins */
    GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE,
                    (uint8_t)((uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5));
    break;

    /* Add cases for UART2 through UART7 as needed */

    default:
        /* Invalid UART module base */
        Uart_State = UART_ERROR_INVALID_MODULE;
        break;
    }

    /* If UART module is valid, configure its parameters */
    if (Uart_State == UART_SUCCESS) {
        UARTConfigSetExpClk(
                a_PTR.module,                 /* UART module base address */
                SysCtlClockGet(),             /* System clock frequency */
                a_PTR.baud_rate,              /* Baud rate */
                (uint32_t)(a_PTR.data_bits |  /* Data bits configuration */
                        a_PTR.stop_bits |  /* Stop bits configuration */
                        (uint32_t)a_PTR.parity)); /* Parity configuration */
    }

    /* Return the state of the UART configuration */
    return Uart_State;
}

/***************************************************************
Function Name   : configure_all_uarts
Inputs          : None:
Outputs         : uint32_t status
Reentrancy      : Non-Reentrant
Synchronous     : ASynchronous
Description     : Configures a UART module for communication with specified parameters.
 ****************************************************************/


uint8_t configure_all_uarts(void) {
    uint8_t status = 0U;              /* Variable to hold the status of UART configuration */
    size_t i = 0U;                    /* Loop counter, initialized to 0 */
    /* Loop through all UART configurations */
    for (i = 0U; i < (size_t)UARTS_CONFIG_numUarts; i++) {
        /* Configure each UART using the UART_config function */
        status = UART_config(UARTS_CONFIG_array[i]);
    }

    return status; /* Return the status of the last UART configuration */
}





void UART_Sprintf(uint32_t num, char *str, uint8_t base) {
    uint8_t i = 0U;            /* Index for the string */
    uint8_t isNegative = 0U;   /* Flag for negative numbers (only used for base 10) */

    /* Validate the base parameter (MISRA-compliant handling) */
    if ((base < 2U) || (base > 36U)) {
        str[0] = '\0'; /* Invalid base, return an empty string */
        return;
    }

    /* Handle the case when the number is 0 */
    if (num == 0U) {
        str[i++] = '0';  /* Add '0' to the string */
        str[i] = '\0';   /* Null-terminate the string */
        return;
    }

    /* Handle base 10 numbers with a "negative" flag (though num is unsigned) */
    if ((base == 10U) && ((int32_t)num < 0)) {
        isNegative = 1U;                 /* Set the negative flag */
        num = (uint32_t)(-(int32_t)num); /* Convert to positive */
    }

    /* Convert the number to the given base */
    while (num != 0U) {
        uint32_t rem = num % (uint32_t)base; /* Get the remainder */
        /* Convert remainder to the appropriate character */
        if (rem > 9U) {
            str[i++] = (char)((rem - 10U) + (uint32_t)'a'); /* For 'a' to 'z' */
        } else {
            str[i++] = (char)(rem + (uint32_t)'0'); /* For '0' to '9' */
        }
        num = num / (uint32_t)base; /* Divide by base */
    }

    /* Add the negative sign for base 10 numbers, if applicable */
    if (isNegative == 1U) {
        str[i++] = '-';
    }

    str[i] = '\0'; /* Null-terminate the string */

    /* Reverse the string to get the correct order */
    uint8_t start = 0U;
    uint8_t end = i - 1U;
    while (start < end) {
        char temp = str[start];  /* Temporary variable for swapping */
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}



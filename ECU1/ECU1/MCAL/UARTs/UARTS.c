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

void UART_sendString(char *a_stringPtr,uint8_t a_Index)
{
    // Loop through the string until the null terminator is encountered
    while(*a_stringPtr != '\0')
    {
        // Send the current character in the string over UART0
        UARTCharPut(UARTS_CONFIG_array[a_Index].module, *a_stringPtr);

        // Move to the next character in the string
        a_stringPtr++;
    }
}




/***************************************************************
Function Name   : UART_receiveByte
Inputs          : uint8_t a_Index
Outputs         : int32_t (Received byte or -1 if no data available)
Reentrancy      : Non-Reentrant
Synchronous     : Yes
Description     : This function checks if a byte of data is available in the UART buffer.
                  If data is available, it retrieves and returns the byte.
                  If no data is available, it immediately returns -1 without blocking.
 ****************************************************************/


// Add data to the circular buffer
void UART_bufferAdd(uint8_t data) {
    uartBuffer[bufferHead] = data;
    bufferHead = (bufferHead + 1) % UART_BUFFER_SIZE;
}

// Get data from the circular buffer
int32_t UART_bufferGet(void) {
    if (bufferHead == bufferTail) {
        return -1; // Buffer empty
    }

    uint8_t data = uartBuffer[bufferTail];
    bufferTail = (bufferTail + 1) % UART_BUFFER_SIZE;
    return data;
}

// Non-blocking UART receive function
void UART_pollReceive(uint8_t a_Index) {
    if (UARTCharsAvail(UARTS_CONFIG_array[a_Index].module)) {
        uint8_t data = UARTCharGet(UARTS_CONFIG_array[a_Index].module);
        UART_bufferAdd(data); // Add received data to the buffer
    }
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
    /* Enable the UART module and configure the GPIO pins for the given UART base*/
    uint8_t Uart_State=0;
    switch (a_PTR.module) {
    case (uint32_t)UART0_BASE:
        /* Enable UART0 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART0);
        /* Enable GPIOA for UART0 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOA);
        /* Configure PA0 for UART0 RX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PA0_U0RX);
        /* Configure PA1 for UART0 TX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PA1_U0TX);
        /* Set PA0 and PA1 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTA_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);
        break;

    case (uint32_t)UART1_BASE:
        /* Enable UART1 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART1);
        /* Enable GPIOC for UART1 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOC);
        /* Configure PC4 for UART1 RX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PC4_U1RX);
        /* Configure PC5 for UART1 TX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PC5_U1TX);
        /* Set PC4 and PC5 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
        break;

    case(uint32_t) UART2_BASE:
        /* Enable UART2 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART2);
        /* Enable GPIOB for UART2 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOB);
        /* Configure PB0 for UART2 RX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PD6_U2RX);
        /* Configure PB1 for UART2 TX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PD7_U2TX);
        /* Set PB0 and PB1 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTB_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);
        break;

    case (uint32_t) UART3_BASE:
        /* Enable UART3 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART3);
        /* Enable GPIOC for UART3 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOC);
        /* Configure PC6 for UART3 RX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PC6_U3RX);
        /* Configure PC7 for UART3 TX functionality*/
        GPIOPinConfigure((uint32_t)GPIO_PC7_U3TX);
        /* Set PC6 and PC7 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE, (uint8_t)GPIO_PIN_6 | (uint8_t)GPIO_PIN_7);
        break;
    case (uint32_t) UART4_BASE: /* UART4 Configuration*/
        /* Enable UART4 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART4);

        /* Enable GPIOC for UART4 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOC);

        /* Configure PC4 as UART4 Receive (RX)*/
        GPIOPinConfigure((uint32_t)GPIO_PC4_U4RX);

        /* Configure PC5 as UART4 Transmit (TX)*/
        GPIOPinConfigure((uint32_t)GPIO_PC5_U4TX);

        /* Set GPIOC pins 4 and 5 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTC_BASE,(uint8_t) GPIO_PIN_4 |(uint8_t) GPIO_PIN_5);
        break;

    case (uint32_t)UART5_BASE: /* UART5 Configuration*/
        /* Enable UART5 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART5);

        /* Enable GPIOE for UART5 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOE);

        /* Configure PE4 as UART5 Receive (RX)*/
        GPIOPinConfigure((uint32_t)GPIO_PE4_U5RX);

        /* Configure PE5 as UART5 Transmit (TX)*/
        GPIOPinConfigure((uint32_t)GPIO_PE5_U5TX);

        /* Set GPIOE pins 4 and 5 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTE_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
        break;

    case (uint32_t)UART6_BASE: /* UART6 Configuration*/
        /* Enable UART6 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART6);

        /* Enable GPIOD for UART6 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOD);

        /* Configure PD4 as UART6 Receive (RX)*/
        GPIOPinConfigure((uint32_t)GPIO_PD4_U6RX);

        /* Configure PD5 as UART6 Transmit (TX)*/
        GPIOPinConfigure((uint32_t)GPIO_PD5_U6TX);

        /* Set GPIOD pins 4 and 5 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTD_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);
        break;

    case (uint32_t)UART7_BASE: /* UART7 Configuration*/
        /* Enable UART7 peripheral*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_UART7);

        /* Enable GPIOE for UART7 pins*/
        SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOE);

        /* Configure PE0 as UART7 Receive (RX)*/
        GPIOPinConfigure((uint32_t)GPIO_PE0_U7RX);

        /* Configure PE1 as UART7 Transmit (TX)*/
        GPIOPinConfigure((uint32_t)GPIO_PE1_U7TX);

        /* Set GPIOE pins 0 and 1 as UART pins*/
        GPIOPinTypeUART((uint32_t)GPIO_PORTE_BASE,(uint8_t) GPIO_PIN_0 |(uint8_t) GPIO_PIN_1);
        break;

    default:
        /* Invalid UART module base*/
        Uart_State= UART_ERROR_INVALID_MODULE;
    }


    /* Configure the UART module with specified parameters*/
    UARTConfigSetExpClk(
            a_PTR.module,            /* UART module base address*/
            SysCtlClockGet(),        /* Use system clock*/
            a_PTR.baud_rate,         /* Baud rate*/
            (a_PTR.data_bits |       /* Data bits*/
                    a_PTR.stop_bits |       /* Stop bits*/
                    (uint8_t) a_PTR.parity));         /* Parity configuration*/
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

    uint32_t status;
    size_t i;
    for (i = 0; i < (size_t)UARTS_CONFIG_numUarts; i++) {
        status = UART_config(UARTS_CONFIG_array[i]);
    }

    return status;
}
void SPRINTF(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers only if base is 10
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Append '-' for negative numbers
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null terminate string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

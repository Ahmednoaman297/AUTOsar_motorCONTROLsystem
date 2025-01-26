/*
 * UARTS.h
 *
 *  Created on: Dec 15, 2024
 *      Author: elder
 */

#ifndef MCAL_UARTS_UARTS_H_
#define MCAL_UARTS_UARTS_H_
/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
/*******************************************************Definitions and Macros**********************************************************/
#define UART_ERROR_INVALID_MODULE  15u
/*******************************************************Type Declaration(struct)**********************************************************/
typedef struct{
    uint32_t module ;
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t parity;
    uint8_t stop_bits;

}UartCFG;
/********************************************functions prototypes*********************************/
void UART_sendString(char *a_stringPtr,uint8_t a_Index);
int32_t UART_receiveByte(uint8_t a_Index);
uint8_t UART_config(UartCFG a_PTR) ;
uint8_t configure_all_uarts(void);

void UART_pollReceive(uint8_t a_Index);
int32_t UART_bufferGet(void);
void SPRINTF(int num, char *str, int base) ;

#define UART_BUFFER_SIZE 128

static uint8_t uartBuffer[UART_BUFFER_SIZE];
static uint8_t bufferHead = 0;
static uint8_t bufferTail = 0;




#endif /* MCAL_UARTS_UARTS_H_ */

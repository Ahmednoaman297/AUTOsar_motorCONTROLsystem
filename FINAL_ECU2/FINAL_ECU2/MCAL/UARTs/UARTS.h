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
#define UART_SUCCESS 0U
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
void UART_Sprintf(uint32_t num, char *str, uint8_t base);






#endif /* MCAL_UARTS_UARTS_H_ */

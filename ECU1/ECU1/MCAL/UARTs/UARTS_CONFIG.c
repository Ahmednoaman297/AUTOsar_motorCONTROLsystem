/*
 * UARTS_CONFIG.c
 *
 *  Created on: Dec 15, 2024
 *      Author: elder
 */


#include "UARTS_CONFIG.h"

UartCFG UARTS_CONFIG_array[Maximum_modules] = {
    {
        .module = UART0_BASE,
        .baud_rate = 9600,
        .data_bits = UART_CONFIG_WLEN_8,
        .stop_bits = UART_CONFIG_STOP_ONE,
        .parity = UART_CONFIG_PAR_NONE
    },
    /* Add more UART configurations here if needed*/
};

uint32_t UARTS_CONFIG_numUarts = sizeof(UARTS_CONFIG_array) / sizeof(UARTS_CONFIG_array[0]);





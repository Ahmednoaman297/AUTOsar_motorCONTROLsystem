/*
 * UARTS_CONFIG.h
 *
 *  Created on: Dec 15, 2024
 *      Author: elder
 */

#ifndef MCAL_UARTS_UARTS_CONFIG_H_
#define MCAL_UARTS_UARTS_CONFIG_H_
#define Maximum_modules 1u

#include "UARTS.h"

/********************************************Shared Global variables*********************************/
extern UartCFG UARTS_CONFIG_array[Maximum_modules];
extern uint32_t UARTS_CONFIG_numUarts;
#endif /* MCAL_UARTS_UARTS_CONFIG_H_ */

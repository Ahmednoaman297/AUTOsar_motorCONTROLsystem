/*
 * E2PROM.h
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */

#ifndef E2PROM_H_
#define E2PROM_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"
#include "utils/uartstdio.h"
#include "driverlib/eeprom.h"

#include "E2PROM_config.h"  // Include the configuration header

#define NULL ((void*)0)

/* Standard AUTOSAR error handling */
//#include "Det.h"  // For diagnostics (Det_ReportError)

#define EEPROM_PAGE_SIZE 16   // Typically, Tiva C EEPROM has 16-byte blocks
#define EEPROM_MODULE_ID  0x01 // Module identifier
/* EEPROM status types */
typedef enum {
    EEPROM_OK = 0x00,
    EEPROM_NOT_INITIALIZED = 0x01,
    EEPROM_WRITE_ERROR = 0x02,
    EEPROM_READ_ERROR = 0x03,
    EEPROM_UNKNOWN_ERROR = 0x04
} Eeprom_StatusType;

/* Function prototypes */


Eeprom_StatusType Eeprom_Init(void);


Eeprom_StatusType Eeprom_Write(uint32_t address, uint32_t data);


Eeprom_StatusType Eeprom_Read(uint32_t address, uint32_t* data);

Eeprom_StatusType Eeprom_Clear(uint32_t startAddress, uint32_t endAddress);




#endif /* E2PROM_H_ */

/*
 * E2PROM_config.h
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */

#ifndef E2PROM_CONFIG_H_
#define E2PROM_CONFIG_H_





#include <stdint.h>

/* Configuration structure for EEPROM */
typedef struct {
    uint32_t baseAddress;  /* Base address of EEPROM memory */
    uint32_t maxSize;      /* Maximum size of EEPROM memory */
} Eeprom_ConfigType;

/* Configuration for EEPROM (this would typically come from an AUTOSAR configuration tool) */
extern const Eeprom_ConfigType Eeprom_Config;



#endif /* E2PROM_CONFIG_H_ */

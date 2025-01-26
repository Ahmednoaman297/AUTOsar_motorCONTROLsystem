/*
 * E2PROM.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Ahmedmohamed
 */

#include "E2PROM.h"
#include "E2PROM_config.h"
// Include the EEPROM header for public APIs

/* Global configuration pointer */
static const Eeprom_ConfigType* Eeprom_ConfigPtr = NULL;

Eeprom_StatusType Eeprom_Init(void)
{
    /* Enable the EEPROM peripheral */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    /* Wait until the EEPROM is ready */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)) {
        /* Optionally, implement a timeout mechanism */
    }

    /* Initialize the EEPROM */
    EEPROMInit();

    return EEPROM_OK;
}

Eeprom_StatusType Eeprom_Write(uint32_t address, uint32_t data)
{
    /* Program the data into the specified address */
    EEPROMProgram(&data, address, sizeof(data));

    /* Check for any errors during write */
    if (EEPROMStatusGet() != 0) {
      //  Det_ReportError(EEPROM_MODULE_ID, 0, 0, EEPROM_WRITE_ERROR);
        return EEPROM_WRITE_ERROR;
    }

    return EEPROM_OK;
}

Eeprom_StatusType Eeprom_Read(uint32_t address, uint32_t* data)
{


    if (data == NULL) {
        return EEPROM_READ_ERROR;
    }

    /* Read data from the specified address */
    EEPROMRead(data, address, sizeof(*data));

    return EEPROM_OK;
}

Eeprom_StatusType Eeprom_Clear(uint32_t startAddress, uint32_t endAddress)
{

    uint32_t address;
    for (address = startAddress; address <= endAddress; address += EEPROM_PAGE_SIZE) {
        uint32_t emptyData[EEPROM_PAGE_SIZE / 4] = {0xFFFFFFFF}; // Erase data

        /* Program the erase data into the specified address */
        EEPROMProgram(emptyData, address, EEPROM_PAGE_SIZE);

        /* Wait for the operation to complete */
        while (EEPROMStatusGet() != 0) {
//            SysCtlDelay(1000); replace with systick
        }
    }

    return EEPROM_OK;
}





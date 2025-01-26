/*
 * NVM.c
 *
 *  Created on: Jan 3, 2025
 *      Author: Ahmedmohamed
 */

#include "NVM.h"
#include "../../MCAL/E2PROM/E2PROM.h"
/***************************************************************
Function Name   : NVM_Read
Inputs          : uint32_t blockID  - ID of the block to read from.
                  uint32_t *data   - Pointer to store the read data.
Outputs         : uint8_t          - Status of the read operation (success/failure).
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Reads data from the Non-Volatile Memory (NVM) at the specified block ID.
                  This function delegates the read operation to the Eeprom_Read function.
****************************************************************/

uint8_t NVM_Read(uint32_t blockID, uint32_t *data) {
    return Eeprom_Read(blockID, data);
}
/***************************************************************
Function Name   : NVM_Write
Inputs          : uint32_t blockID  - ID of the block to write to.
                  uint32_t data    - Data to be written to the specified block.
Outputs         : uint8_t          - Status of the write operation (success/failure).
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Writes data to the Non-Volatile Memory (NVM) at the specified block ID.
                  This function delegates the write operation to the Eeprom_Write function.
****************************************************************/

uint8_t NVM_Write(uint32_t blockID,  uint32_t data) {
    return Eeprom_Write(blockID, data);
}
/***************************************************************
Function Name   : NVM_Clear
Inputs          : uint32_t startAddress - The starting address of the block to be cleared.
                  uint32_t endAddress   - The ending address of the block to be cleared.
Outputs         : uint8_t               - Status of the clear operation (success/failure).
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Clears a range of memory in the Non-Volatile Memory (NVM) between the specified
                  start and end addresses.
                  This function delegates the clear operation to the Eeprom_Clear function.
****************************************************************/

uint8_t NVM_Clear(uint32_t startAddress, uint32_t endAddress)
{

    Eeprom_Clear(startAddress,endAddress);

}


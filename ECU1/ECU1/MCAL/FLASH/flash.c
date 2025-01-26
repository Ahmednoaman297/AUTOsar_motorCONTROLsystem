/* flash.c */

#include "flash.h"
#include "flash_cfg.h"
#include "driverlib/flash.h"
#include "driverlib/sysctl.h"
#include "MCAL/UARTs/UARTS.h"

// UART for debug messages
#define UART_DEBUG_INDEX 0

void UART_DebugMessage(const char *message) {
    UART_sendString((char *)message, UART_DEBUG_INDEX);
}

void UART_DebugMessageNumber(const char *message, uint32_t number) {
    char buffer[64];
    sprintf(buffer, "%s: 0x%08X\r\n", message, number);
    UART_sendString(buffer, UART_DEBUG_INDEX);
}

// Initialize the Flash driver
int Flash_Init(void) {
    UART_DebugMessage("Flash driver initialized.\r\n");
    return FLASH_SUCCESS;
}

// Erase a Flash sector
int Flash_EraseSector(uint32_t address) {
    if (address % FLASH_CONFIG.sectorSize != 0) {
        UART_DebugMessage("Error: Invalid Flash sector address alignment.\r\n");
        return FLASH_INVALID_ADDRESS;
    }

    if (FlashErase(address) != 0) {
        UART_DebugMessage("Error: Failed to erase Flash sector.\r\n");
        return FLASH_ERROR_ERASE;
    }

    UART_DebugMessage("Flash sector erased successfully.\r\n");
    return FLASH_SUCCESS;
}

// Write a 32-bit word to Flash
int Flash_WriteWord(uint32_t address, uint32_t data) {
    if (address % 4 != 0) {
        UART_DebugMessage("Error: Invalid Flash write address alignment.\r\n");
        return FLASH_INVALID_ADDRESS;
    }

    if (FlashProgram(&data, address, sizeof(uint32_t)) != 0) {
        UART_DebugMessage("Error: Failed to write data to Flash.\r\n");
        return FLASH_ERROR_WRITE;
    }

    UART_DebugMessage("Data written to Flash successfully.\r\n");
    return FLASH_SUCCESS;
}

// Write an array to Flash
int Flash_WriteArray(uint32_t address, uint32_t *data, uint32_t length) {
    if (length % 4 != 0) {
        UART_DebugMessage("Error: Invalid Flash write length alignment.\r\n");
        return FLASH_INVALID_ADDRESS;
    }

    if (FlashProgram(data, address, length) != 0) {
        UART_DebugMessage("Error: Failed to write array to Flash.\r\n");
        return FLASH_ERROR_WRITE;
    }

    UART_DebugMessage("Array written to Flash successfully.\r\n");
    return FLASH_SUCCESS;
}

// Read a 32-bit word from Flash
int Flash_ReadWord(uint32_t address, uint32_t *data) {
    if (address % 4 != 0) {
        UART_DebugMessage("Error: Invalid Flash read address alignment.\r\n");
        return FLASH_INVALID_ADDRESS;
    }

    *data = *(volatile uint32_t *)address;
    UART_DebugMessage("Data read from Flash successfully.\r\n");
    return FLASH_SUCCESS;
}

void testFlashDriver(void) {
    uint32_t writeData = 0xABCDEF12;
    uint32_t readData = 0;

    if (Flash_EraseSector(FLASH_CONFIG.startAddress) == FLASH_SUCCESS) {
        UART_DebugMessage("Flash sector erased successfully.\r\n");
    }

    if (Flash_WriteWord(FLASH_CONFIG.startAddress, writeData) == FLASH_SUCCESS) {
        UART_DebugMessage("Data written successfully.\r\n");
    }

    if (Flash_ReadWord(FLASH_CONFIG.startAddress, &readData) == FLASH_SUCCESS) {
        UART_DebugMessage("Data read successfully.\r\n");
    }

    if (readData == writeData) {
        UART_DebugMessage("Flash test passed!\r\n");
    } else {
        UART_DebugMessage("Flash test failed!\r\n");
    }
}

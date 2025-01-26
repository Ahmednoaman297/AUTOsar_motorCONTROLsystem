/* flash.h */

#ifndef BSW_FLASH_H_
#define BSW_FLASH_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "flash_cfg.h"

// Error Codes
#define FLASH_SUCCESS           0
#define FLASH_ERROR_ERASE      -1
#define FLASH_ERROR_WRITE      -2
#define FLASH_ERROR_READ       -3
#define FLASH_INVALID_ADDRESS  -4

// API Prototypes
int Flash_Init(void);
int Flash_EraseSector(uint32_t address);
int Flash_WriteWord(uint32_t address, uint32_t data);
int Flash_WriteArray(uint32_t address, uint32_t *data, uint32_t length);
int Flash_ReadWord(uint32_t address, uint32_t *data);
void testFlashDriver(void);

#endif /* BSW_FLASH_H_ */

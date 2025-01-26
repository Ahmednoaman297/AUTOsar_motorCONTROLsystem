/* flash_cfg.c */

#include "flash_cfg.h"

// Define the user-configurable Flash settings
const FlashConfig FLASH_CONFIG = {
    .startAddress = 0x00020000, // Example start address (modifiable by user)
    .sectorSize = 1024         // Example sector size (modifiable by user)
};



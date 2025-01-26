/* flash_cfg.h */

#ifndef FLASH_CFG_H_
#define FLASH_CFG_H_

#include <stdint.h>

// User-configurable Flash memory settings
typedef struct {
    uint32_t startAddress; // Start address of Flash memory
    uint32_t sectorSize;   // Size of each sector in bytes
} FlashConfig;

extern const FlashConfig FLASH_CONFIG;

#endif /* FLASH_CFG_H_ */

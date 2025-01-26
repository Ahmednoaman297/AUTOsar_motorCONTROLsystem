/*
 * NVM.h
 *
 *  Created on: Jan 3, 2025
 *      Author: Ahmedmohamed
 */

#ifndef SERVICE_NVM_H_
#define SERVICE_NVM_H_


#include <stdint.h>

/* Function prototypes for NVM operations */
uint8_t NVM_Read(uint32_t blockID, uint32_t *data) ;
uint8_t NVM_Write(uint32_t blockID,  uint32_t data);
uint8_t NVM_Clear(uint32_t startAddress, uint32_t endAddress);


#endif /* SERVICE_NVM_H_ */

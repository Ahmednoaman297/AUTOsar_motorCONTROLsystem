/*
 * CAN_CONFIG.h
 *
 ModuleName: CAN
 Author: Ahmedmohamed
 Purpose: Header file for CAN_CONFIG Driver
 */

#ifndef MCAL_CAN_CAN_CONFIG_H_
#define MCAL_CAN_CAN_CONFIG_H_
/*************************************************************Includes**************************************************************/
#include "CAN.h"



#define CAN_MODULES     1
#define OBJECTS_NUM     5

/*************************************************************Extern**************************************************************/

extern  CAN_ErrorStatus CAN_Errors;
extern  CAN_MessageObjectConfig MessagObjects[OBJECTS_NUM];
extern  CAN_ModuleConfig CAN_Modules[CAN_MODULES];






#endif /* MCAL_CAN_CAN_CONFIG_H_ */

/*
 * CAN_CONFIG.c
 *
 ModuleName: CAN
 Author: Ahmedmohamed
 Purpose: Source file for CAN_CONFIG Driver
 */


/*************************************************************Includes**************************************************************/
#include "CAN_CONFIG.h"

/*************************************************************Declarations**************************************************************/

CAN_ErrorStatus CAN_Errors = {Zero_CAN};

CAN_MessageObjectConfig MessagObjects[OBJECTS_NUM]=
{
 /*TEMP. & KNOWN VOLTAGE SENDING OBJECT*/
 {
  1, /*the number of the object*/
  0x27, /*the msgID*/
  0x27, /*the msgIDMask*/
  MSG_OBJ_TX_INT_ENABLE, /*the msgFlag*/
  8, /*the msgLEN*/
  MSG_OBJ_TYPE_TX,
  CAN_ROLE_SEND /*the role of object whether master of slave*/
 },
 /*REMOTE FRAME RECEIVING OBJECT*/
 {
  .objectID     = 2, /*the number of the object*/
  .msgID        = 0x37, /*the msgID*/
  .msgIDMask    = 0x37, /*the msgIDMask*/
  .flags        =  (uint32_t)MSG_OBJ_USE_ID_FILTER, /*the msgFlag  (uint32_t)MSG_OBJ_RX_INT_ENABLE |*/
  .msgLen       = 8, /*the msgLEN*/
  .OBJ_Type     = MSG_OBJ_TYPE_RX_REMOTE,
  .role         = CAN_ROLE_RECIEVE/*the role of object whether master of slave*/
 },
 /*ERROR CHECK RECEIVING OBJECT*/
 {
  .objectID     = 3, /*the number of the object*/
  .msgID        = 0x07, /*the msgID*/
  .msgIDMask    = 0X07, /*the msgIDMask*/
  .flags        = (uint32_t)MSG_OBJ_USE_ID_FILTER, /*the msgFlag  (uint32_t)MSG_OBJ_RX_INT_ENABLE |*/
  .msgLen       = 8, /*the msgLEN*/
  .OBJ_Type     = MSG_OBJ_TYPE_RX,
  .role         = CAN_ROLE_RECIEVE/*the role of object whether master of slave*/
 },
 /*ERROR CHECK SENDING OBJECT*/
 {
  .objectID     = 4, /*the number of the object*/
  .msgID        = 0x07, /*the msgID*/
  .msgIDMask    = 0x07, /*the msgIDMask*/
  .flags        = MSG_OBJ_TX_INT_ENABLE, /*the msgFlag*/
  .msgLen       = 8, /*the msgLEN*/
  .OBJ_Type     = MSG_OBJ_TYPE_TX,
  .role         = CAN_ROLE_SEND/*the role of object whether master of slave*/
 },
 /*ERROR CHECK SENDING OBJECT*/
 {
  .objectID     = 5, /*the number of the object*/
  .msgID        = 0x45, /*the msgID*/
  .msgIDMask    = 0x45, /*the msgIDMask*/
  .flags        = (uint32_t)MSG_OBJ_USE_ID_FILTER |(uint32_t)MSG_OBJ_RX_INT_ENABLE,  /*the msgFlag*/
  .msgLen       = 8, /*the msgLEN*/
  .OBJ_Type     = MSG_OBJ_TYPE_RX,
  .role         = CAN_ROLE_RECIEVE/*the role of object whether master of slave*/
 }
};


CAN_ModuleConfig CAN_Modules[CAN_MODULES] =
{
 {
  .Module                = CAN0_BASE,
  .InterruptEnable       = NO_Interrupt, /*interrupt*/
  .bitRate               = 500000,
  .numObjects            = sizeof(MessagObjects) / sizeof(MessagObjects[Zero_CAN]),
  .objects                = MessagObjects,
  .errors                = &CAN_Errors /* Pointer to error status*/
 }
};




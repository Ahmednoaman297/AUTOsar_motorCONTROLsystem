/*
 * CAN.h
 *
 *      ModuleName: CAN
 *      Author: Ahmed Mohamed
 *      Purpose: Header file for CAN Driver
 */

#ifndef MCAL_CAN_H_
#define MCAL_CAN_H_

/*************************************************************Includes**************************************************************/


#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"


/*************************************************************Defines**************************************************************/

/* Error Codes not implemented yet*/
#define CAN_NO_ERROR                0u /* No error*/
#define CAN_ERROR_GPIO_INIT         13u /* Error in GPIO initialization*/
#define CAN_ERROR_CAN_Module        14u /* Error in CAN module initialization*/
#define CAN_ERROR_TRANSMIT          17u /* Error in transmitting data*/
#define CAN_ERROR_RECEIVE           18u /* Error in receiving data*/
#define CAN_Remote_Frame            10u
#define ENABLE_Interrupt             1u
#define NO_Interrupt                 0u
#define Zero_CAN                     0u
#define ONE_CAN                      1u
#define CAN_ROLE_SEND                1u
#define CAN_ROLE_RECIEVE             2u

/*************************************************************Structs**************************************************************/

/* Structure to hold error status*/
typedef struct {
    uint8_t gpioInitError;       /* GPIO initialization error*/
    uint8_t canInitError;        /* CAN module initialization error*/
    uint8_t transmitError;       /* Transmission error*/
    uint8_t receiveError;        /* Reception error*/
    uint8_t bitRateError;        /* Bit rate setting error*/
    uint8_t invalidObjectError;  /* Invalid object error*/
} CAN_ErrorStatus;

/* Structure for CAN message object configuration
(to declare many objects and choose the role whether
to be sender or receiver and some other information
about the object)*/
typedef struct {
    uint8_t objectID;   /*the object id*/
    uint32_t msgID;     /*the message ID that is wanted to send or received*/
    uint32_t msgIDMask; /*MSGID mask*/
    uint32_t flags;     /*whether sending or receiving*/
    uint32_t msgLen;     /*msg length in bytes*/
    tMsgObjType OBJ_Type;
    uint8_t role;       /*is this object sending or receiving*/
} CAN_MessageObjectConfig;

/* Structure for CAN module configuration*/
typedef struct {
    uint32_t Module;
    uint8_t InterruptEnable;            /* if interrupt needed*/
    uint32_t bitRate;                   /*baud rate*/
    uint8_t numObjects;                 /*Number of objects in this can base*/
    CAN_ErrorStatus* errors;
    CAN_MessageObjectConfig * objects;/* Pointer to error status*/
} CAN_ModuleConfig;


/*******************************************************Function Prototypes**********************************************************/

uint8_t CANInitialize(uint8_t a_index);
uint8_t CANTransmit(uint8_t a_moduleIndex, uint8_t a_objectID, uint8_t *a_pui8Data, uint32_t a_ui32MsgLen, bool isRemote);
uint32_t CanReceiveMessage(uint8_t a_moduleIndex, uint8_t a_objectID, uint8_t *a_pui8Buffer) ;



#endif /* MCAL_CAN_H_ */

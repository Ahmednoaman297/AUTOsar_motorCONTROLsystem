/*
 * CAN.c
 *
 * ModuleName: CAN
 * Author: Ahmedmohamed
 * Purpose: Source file for CAN Driver
 */

/**************************************************************Includes*********************************************************************/

#include "CAN.h"
#include "CAN_CONFIG.h"



/***************************************************************
Function Name   : CANInitialize
Inputs          : uint8_t a_index
Outputs         : uint8_t
Reentrancy      : Non-Reentrancy
Synchronous     : Synchronous
Description     : Initialize the certain CAN module identified by the user in
                  configurations files
 ****************************************************************/
uint8_t CANInitialize(uint8_t a_index){
    uint8_t Error_flag =Zero_CAN;
    uint8_t Error =CAN_NO_ERROR;
    switch(CAN_Modules[a_index].Module)
    {
    case (uint32_t)CAN0_BASE:
            /* Enable GPIO and CAN peripherals*/
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); /* GPIO for CAN0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0); /* CAN0 Module*/

    /* Wait until the peripherals are ready*/
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {
        Error_flag++;
        if(Error_flag >=(uint8_t)50)
        {
            Error = (uint8_t)CAN_ERROR_GPIO_INIT;
        }
    }
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0)) {
        Error_flag++;
        if(Error_flag >=(uint8_t)50)
        {
            Error = CAN_ERROR_CAN_Module;
        }
    }

    /* Configure GPIO pins for CAN0 (PB4 = RX, PB5 = TX)*/
    GPIOPinConfigure((uint32_t)GPIO_PB4_CAN0RX);
    GPIOPinConfigure((uint32_t)GPIO_PB5_CAN0TX);
    GPIOPinTypeCAN((uint32_t)GPIO_PORTB_BASE, (uint8_t)GPIO_PIN_4 | (uint8_t)GPIO_PIN_5);

    /* Initialize the CAN controller*/
    CANInit((uint32_t)CAN0_BASE);


    break;
    case (uint32_t)CAN1_BASE:
            /* Enable GPIO and CAN peripherals for CAN1*/
            SysCtlPeripheralEnable((uint32_t)SYSCTL_PERIPH_GPIOA); /* GPIO for CAN1*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1); /* CAN1 Module*/

    /* Wait until the peripherals are ready*/
    while (!SysCtlPeripheralReady((uint32_t)SYSCTL_PERIPH_GPIOA)) {
        Error_flag++;
        if(Error_flag >= (uint8_t)50)
        {
            Error = CAN_ERROR_GPIO_INIT;
        }
    }
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN1)) {
        Error_flag++;
        if(Error_flag >= (uint8_t)50)
        {
            Error = CAN_ERROR_CAN_Module;
        }
    }

    /* Configure GPIO pins for CAN1 (PA0 = RX, PA1 = TX)*/
    GPIOPinConfigure((uint32_t)GPIO_PA0_CAN1RX);
    GPIOPinConfigure((uint32_t)GPIO_PA1_CAN1TX);
    GPIOPinTypeCAN((uint32_t)GPIO_PORTA_BASE, (uint8_t)GPIO_PIN_0 | (uint8_t)GPIO_PIN_1);

    /* Initialize the CAN1 controller*/
    CANInit((uint32_t)CAN1_BASE);


    break;
    default:
        Error = CAN_ERROR_CAN_Module;
        break;
    }
    /* Set the bit rate for CAN communication*/
    CANBitRateSet((uint32_t)CAN_Modules[a_index].Module, (uint32_t)SysCtlClockGet(), (uint32_t)CAN_Modules[a_index].bitRate);

    /* Enable CAN for operation*/
    CANEnable((uint32_t)CAN_Modules[a_index].Module);

    if (CAN_Modules[a_index].InterruptEnable == (uint8_t)ONE_CAN )
    {
        CANIntEnable((uint32_t)CAN_Modules[a_index].Module, (uint32_t)CAN_INT_ERROR |(uint32_t)CAN_INT_STATUS|(uint32_t)CAN_INT_MASTER);
        IntMasterEnable();
    }
    uint8_t i ;
    for (i=(uint8_t)Zero_CAN ; i<CAN_Modules[a_index].numObjects ; i++)
    {
        tCANMsgObject msgObject;
        msgObject.ui32MsgID = MessagObjects[i].msgID;
        msgObject.ui32MsgIDMask = MessagObjects[i].msgIDMask;
        msgObject.ui32Flags = MessagObjects[i].flags;
        msgObject.ui32MsgLen = MessagObjects[i].msgLen;

        if (MessagObjects[i].role== (uint8_t)CAN_ROLE_SEND)
        {
            CANMessageSet(CAN_Modules[a_index].Module,
                          MessagObjects[i].objectID,
                          &msgObject,
                          MessagObjects[i].OBJ_Type );
        }
        else
        {
            CANMessageSet(CAN_Modules[a_index].Module,
                          MessagObjects[i].objectID,
                          &msgObject,
                          MessagObjects[i].OBJ_Type   );
        }
    }
    return Error ;

}


/***************************************************************
Function Name   : CANTransmit
Inputs          : uint8_t ModuleIndex,
                  uint8_t a_objectID,
                  uint8_t *a_pui8Data,
                  uint32_t a_ui32MsgLen
Outputs         : void
Reentrancy      : Non-Reentrancy
Synchronous     : ASynchronous
Description     : Transmit message to the CAN bus with certain ID
 ****************************************************************/

uint8_t CANTransmit(uint8_t a_moduleIndex, uint8_t a_objectID, uint8_t *a_pui8Data, uint32_t a_ui32MsgLen, bool isRemote)
{
    uint8_t Error_transmit = CAN_NO_ERROR;

    if (a_ui32MsgLen > (uint32_t)8 && !isRemote) {
        Error_transmit = CAN_ERROR_TRANSMIT;
    } else {
        uint8_t error = ONE_CAN;
        uint8_t i = Zero_CAN;
        for (i = (uint8_t)Zero_CAN; i < CAN_Modules[a_moduleIndex].numObjects; i++) {
            if (CAN_Modules[a_moduleIndex].objects[i].objectID == a_objectID) {
                error = (uint8_t)Zero_CAN;
            }
        }
        if ((uint8_t)Zero_CAN == error) {
            tCANMsgObject msgObject;
            msgObject.ui32MsgID = CAN_Modules[a_moduleIndex].objects[a_objectID - ONE_CAN].msgID;
            msgObject.ui32MsgIDMask = CAN_Modules[a_moduleIndex].objects[a_objectID - ONE_CAN].msgIDMask;
            msgObject.ui32Flags = CAN_Modules[a_moduleIndex].objects[a_objectID - ONE_CAN].flags;
            msgObject.ui32MsgLen = isRemote ? 0 : a_ui32MsgLen;
            msgObject.pui8MsgData = isRemote ? 0 : a_pui8Data;


            uint32_t msgType = isRemote ? MSG_OBJ_TYPE_TX_REMOTE : MSG_OBJ_TYPE_TX;
            CANMessageSet((uint32_t)CAN_Modules[a_moduleIndex].Module, (uint32_t)a_objectID, &msgObject, msgType);
        } else {
            Error_transmit = CAN_ERROR_TRANSMIT;
        }
    }
    return Error_transmit;
}


/***************************************************************
Function Name   : ReceiveMessage
Inputs          : uint8_t a_moduleIndex,
                  uint8_t a_objectID,
                  uint8_t *pui8Buffer
Outputs         : uint32_t msgObject.a_ui32MsgLen
Reentrancy      : Non-Reentrancy
Synchronous     : ASynchronous
Description     : Receive a message from the CAN bus with certain id and mask(selected by the a_objectID ) for the message
                  and if there is no new data the a_ui32MsgLen returned variable is ZERO
 ****************************************************************/


uint32_t CanReceiveMessage(uint8_t a_moduleIndex, uint8_t a_objectID, uint8_t *a_pui8Buffer) {
    uint32_t return_variable;
    uint32_t Msg_length;

    uint8_t error=Zero_CAN;
    uint8_t i=Zero_CAN;
    for (i=(uint8_t)Zero_CAN ;i<CAN_Modules[a_moduleIndex].numObjects;i++)
    {
        if (CAN_Modules[a_moduleIndex].objects[i].objectID == a_objectID)
        {
            error = (uint8_t)Zero_CAN;
        }else{

        }
    }
    if ((uint8_t)Zero_CAN == error)
    {
        tCANMsgObject msgObject;
        msgObject.pui8MsgData = a_pui8Buffer; /* Point to the provided buffer*/

        /* Get the message from Message Object*/
        CANMessageGet((uint32_t)CAN_Modules[a_moduleIndex].Module, (uint32_t)a_objectID, &msgObject, true);
        Msg_length = msgObject.ui32MsgLen;
        if((msgObject.ui32Flags & MSG_OBJ_NEW_DATA  ) && (msgObject.ui32Flags & MSG_OBJ_REMOTE_FRAME))
        {
            return_variable = CAN_Remote_Frame;
        }
        else{
            return_variable = Msg_length;
        }
    }
    else
    {
        return_variable = CAN_ERROR_RECEIVE;/* return error hena m7tag 2ghyar al zero adelha*/

    }

    return return_variable;
}



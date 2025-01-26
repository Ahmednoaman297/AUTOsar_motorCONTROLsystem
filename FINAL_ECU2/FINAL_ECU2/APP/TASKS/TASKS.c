/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */
/********************************************Includes*********************************/

#include "TASKS.h"

/********************************************Global and static variables*********************************/

uint8_t BlinkBlueLED_Flag =INIT_ZERO;
uint8_t received_data[8];
uint8_t SEND_DATA=0;
uint8_t Queue[QUEUE_LEN] ;
uint8_t RED_SEMAPHORE =INIT_ZERO;
uint8_t GREEN_SEMAPHORE =INIT_ZERO;
uint8_t WHITE_SEMAPHORE =INIT_ZERO;
uint8_t ENTER_TESTING =INIT_ZERO;
uint8_t EXIT_TESTING =INIT_ZERO;
uint8_t TESTING_SEMAPHORE =INIT_ZERO;


/**********************************Function Defintions********************************************/
/***************************************************************
Function Name   : SUSPEND_ALL
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Suspends specific tasks by calling the `OS_SuspendTask` function on tasks with predefined indices.
****************************************************************/
void SUSPEND_ALL(void)
{
    OS_SuspendTask((uint8_t)0);
    OS_SuspendTask((uint8_t)3);
    OS_SuspendTask((uint8_t)4);
    OS_SuspendTask((uint8_t)7);
    OS_SuspendTask((uint8_t)9);

}

/***************************************************************
Function Name   : RESUME_ALL
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Resumes specific tasks by calling the `OS_ResumeTask` function on tasks with predefined indices.
****************************************************************/
void RESUME_ALL(void)
{
    OS_ResumeTask((uint8_t)0);
    OS_ResumeTask((uint8_t)3);
    OS_ResumeTask((uint8_t)4);
    OS_ResumeTask((uint8_t)6);
    OS_ResumeTask((uint8_t)7);
    OS_ResumeTask((uint8_t)9);
}

/***************************************************************
Function Name   : TASK_INITS
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Initializes various hardware modules such as GPIO, CAN, ADC, and UART.
****************************************************************/


void TASK_INITS (void)
{
    GPIO_init(GPIO_PORTF_Index);
    CANInitialize(CAN0_Index);
    ADC_Init();
    configure_all_uarts();
}

/***************************************************************
Function Name   : TASK_ReceiveCAN
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Receives CAN messages and stores them in a queue if valid.
****************************************************************/
void TASK_ReceiveCAN(void)
{
    static uint8_t Queue_Counter =INIT_ZERO;
    uint32_t ReceivedMSG_LEN =  CanReceiveMessage((uint8_t)CAN0_Index,STATEOBJECT,received_data);
    if (MSG_LENGTH == ReceivedMSG_LEN)
    {
        if (received_data[0] != HoldSTATE)
        {
            Queue[Queue_Counter] = received_data[0];
            if (Queue_Counter >= (uint8_t)29)
            {
                Queue_Counter = (uint8_t)INIT_ZERO;
            }
            else
            {
                Queue_Counter ++;
            }

        }
    }
    else
    {
        /* Error*/
    }
}


void TASK_RECEIVED_DATA_CHECK (void)
{
    static uint8_t READING_QUEUE_COUNTER =INIT_ZERO;

    switch(Queue[READING_QUEUE_COUNTER])
    {
    case RED:
    {

        RED_SEMAPHORE =SetSEAMPHORE;
        WHITE_SEMAPHORE =INIT_ZERO;
        GREEN_SEMAPHORE =INIT_ZERO;
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case GREEN:
    {
        RED_SEMAPHORE= INIT_ZERO;
        WHITE_SEMAPHORE =INIT_ZERO;
        GREEN_SEMAPHORE =SetSEAMPHORE;
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case WHITE:
    {
        GREEN_SEMAPHORE=INIT_ZERO;
        RED_SEMAPHORE= INIT_ZERO;
        WHITE_SEMAPHORE =SetSEAMPHORE;
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case TESTREDLED:
    {
        if(TESTING_SEMAPHORE == ConditionSEAMPHORE)
        {
            LED_redLight();
        }
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case TESTWHITELED:
    {
        if(TESTING_SEMAPHORE == ConditionSEAMPHORE)
        {
            LED_whiteLight();
        }
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case TESTBLUELED:
    {
        if(TESTING_SEMAPHORE == ConditionSEAMPHORE)
        {
            LED_blueLight();
        }
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case TESTGREENLED:
    {
        if(TESTING_SEMAPHORE == ConditionSEAMPHORE)
        {
            LED_greenLight();
        }
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case ENTERTESTING:
    {
        TESTING_SEMAPHORE = SetSEAMPHORE;
        ENTER_TESTING =SetSEAMPHORE;
        GREEN_SEMAPHORE=INIT_ZERO;
        RED_SEMAPHORE= INIT_ZERO;
        WHITE_SEMAPHORE =SetSEAMPHORE;
        SUSPEND_ALL();
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        break;
    }
    case EXITTESTING:
    {
        TESTING_SEMAPHORE = INIT_ZERO ;
        EXIT_TESTING = SetSEAMPHORE;
        GREEN_SEMAPHORE=INIT_ZERO;
        RED_SEMAPHORE= INIT_ZERO;
        WHITE_SEMAPHORE =SetSEAMPHORE;
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;
        LEDS_off();
        break;
    }

    default:
    {
        Queue[READING_QUEUE_COUNTER] = HoldSTATE;
        READING_QUEUE_COUNTER ++;

        break;
    }
    }
    if (READING_QUEUE_COUNTER >= (uint8_t)29)
    {
        READING_QUEUE_COUNTER =INIT_ZERO;
    }

}

/***************************************************************
Function Name   : TASK_REDLED
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Controls the blinking behavior of the red LED based on the state of a semaphore.
****************************************************************/

void TASK_REDLED (void)
{

    static uint32_t BlinkRed_timeDelay = INIT_ZERO;
    static uint8_t BlinkRed_Flag = INIT_ZERO;

    if (RED_SEMAPHORE ==ConditionSEAMPHORE)
    {

        uint8_t condition1 = (BlinkRed_Flag == CONDITION_ZERO);
        uint8_t condition3 = (BlinkRed_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkRed_timeDelay) >= (uint32_t)1000);
        if (condition1 && condition2  )
        {
            BlinkRed_Flag = SetFlag;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LED_redLight();

        }
        else if (condition3 && condition2 )
        {
            BlinkRed_Flag = INIT_ZERO;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LEDS_off();

        }
        else
        {

        }

    }
    else {

    }

}
/***************************************************************
Function Name   : TASK_GREENLED
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : This task controls the behavior of the green LED. It checks if the green semaphore is set, and if so, it turns on the green LED and resets the green semaphore to its initial state.
****************************************************************/
void TASK_GREENLED (void)
{

    if (GREEN_SEMAPHORE== ConditionSEAMPHORE)
    {
        LED_greenLight();
        GREEN_SEMAPHORE = INIT_ZERO;
    }
    else {

    }

}

/***************************************************************
Function Name   : TASK_WHITELED
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : This task controls the behavior of the white LED. It checks if the white semaphore is set, and depending on whether the system is entering or exiting testing mode, it blinks the white LED with a specified delay. After a certain number of blinks, the task either resumes all processes or stops the blinking and resets the semaphore.
****************************************************************/
void TASK_WHITELED (void)
{

    static uint32_t BlinkWhite_timeDelay = INIT_ZERO;
    static uint8_t BlinkWhite_Flag = INIT_ZERO;
    static uint8_t Counter = INIT_ZERO;
    if (WHITE_SEMAPHORE ==ConditionSEAMPHORE)
    {
        if ((ENTER_TESTING == ConditionSEAMPHORE) || (EXIT_TESTING == ConditionSEAMPHORE))
        {
            uint8_t condition1 = (BlinkWhite_Flag == CONDITION_ZERO);
            uint8_t condition3 = (BlinkWhite_Flag != CONDITION_ZERO);
            uint8_t condition2 = ((SYSTICK_Flag - BlinkWhite_timeDelay) >= (uint32_t)1000);
            if (condition1 && condition2  )
            {
                BlinkWhite_Flag = SetFlag;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LED_whiteLight();
                Counter++;
            }
            else if (condition3 && condition2 )
            {

                BlinkWhite_Flag = INIT_ZERO;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LEDS_off();
                Counter++;
            }
            else
            {

            }
            if(Counter >=(uint8_t)4)
            {
                ENTER_TESTING = (uint8_t)0;
                if (EXIT_TESTING == (uint8_t)0)
                {
                    RESUME_ALL();
                }
                BlinkBlueLED_Flag =INIT_ZERO;
                WHITE_SEMAPHORE=INIT_ZERO;
                Counter=INIT_ZERO;
            }
        }
        else
        {
            RED_SEMAPHORE= INIT_ZERO;
            uint8_t condition1 = (BlinkWhite_Flag == CONDITION_ZERO);
            uint8_t condition3 = (BlinkWhite_Flag != CONDITION_ZERO);
            uint8_t condition2 = ((SYSTICK_Flag - BlinkWhite_timeDelay) >= (uint32_t)1000);
            if (condition1 && condition2  )
            {
                BlinkWhite_Flag = SetFlag;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LED_whiteLight();
                Counter++;
            }
            else if (condition3 && condition2 )
            {
                BlinkWhite_Flag = INIT_ZERO;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LEDS_off();
                Counter++;
            }
            else
            {

            }
            if(Counter >=(uint8_t)10)
            {
                BlinkBlueLED_Flag =INIT_ZERO;
                WHITE_SEMAPHORE=INIT_ZERO;
                Counter=INIT_ZERO;
            }
            else
            {

            }
        }
    }
    else {

    }

}


/***************************************************************
Function Name   : TASK_errorCheck
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Handles error checking for the CAN communication. It receives a message, checks if it's received correctly, and sends a response if no error is detected. If the message isn't received, it triggers a blue LED blink after a timeout.
****************************************************************/
void TASK_errorCheck (void)
{
    static uint32_t ErrorCheck_delay = INIT_ZERO;
    uint8_t received_data_error[8]= {INIT_ZERO} ;
    bool remoteFlag = false;
    uint32_t ReceivedMSG_LEN =  CanReceiveMessage(CAN0_Index,ISConnectedReceivingObject,received_data_error);
    if (MSG_LENGTH == ReceivedMSG_LEN)
    {
        BlinkBlueLED_Flag =INIT_ZERO;
        ErrorCheck_delay =INIT_ZERO;
        uint8_t  error_check_data = 0x07 ;
        CANTransmit((uint8_t)CAN0_Index, (uint8_t)ISConnectedSendingObject, &error_check_data, (uint32_t)MSG_LENGTH,remoteFlag);
    }
    else
    {
        if (ErrorCheck_delay == CONDITION_ZERO)
        {
            ErrorCheck_delay =SYSTICK_Flag;
        }
        else if (SYSTICK_Flag - ErrorCheck_delay>= (uint32_t)5000)
        {
            if (RED_SEMAPHORE== CONDITION_ZERO)
            {
                BlinkBlueLED_Flag =SetFlag;
                TESTING_SEMAPHORE =INIT_ZERO ;

            }
            ErrorCheck_delay =INIT_ZERO;
        }
        else
        {

        }
    }

}

/***************************************************************
Function Name   : TASK_blinkBlueLED
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : This task controls the behavior of the blue LED. When the blue LED flag (`BlinkBlueLED_Flag`) is set, it blinks the blue LED with a 1000ms delay. After 10 blinks, the task resets the flag and the counter.
****************************************************************/

void TASK_blinkBlueLED (void)
{
    static uint32_t BlinkBlue_timeDelay = INIT_ZERO;
    static uint8_t Blinkblue_Flag = INIT_ZERO;
    static uint8_t Counter = INIT_ZERO;
    if (BlinkBlueLED_Flag ==ConditionSEAMPHORE)
    {

        uint8_t condition1 = (Blinkblue_Flag == CONDITION_ZERO);
        uint8_t condition3 = (Blinkblue_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkBlue_timeDelay) >= (uint32_t)1000);
        if (condition1 && condition2  )
        {
            Blinkblue_Flag = SetFlag;
            BlinkBlue_timeDelay = SYSTICK_Flag;
            LED_blueLight();
            Counter++;
        }
        else if (condition3 && condition2 )
        {
            Blinkblue_Flag = INIT_ZERO;
            BlinkBlue_timeDelay = SYSTICK_Flag;
            LEDS_off();
            Counter++;
        }
        else{

        }
        if(Counter >= (uint8_t)10)
        {
            BlinkBlueLED_Flag =INIT_ZERO;
            Counter=INIT_ZERO;

        }
        else{

        }
    }
    else {

    }

}


/***************************************************************
Function Name   : TASK_TempCheck
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : This task reads temperature sensor data from ADC, calculates the average temperature from multiple samples, and sends the calculated temperature through UART and CAN communication.
****************************************************************/

void TASK_TempCheck (void)
{
    static uint8_t TempCheck_Counter = INIT_ZERO;
    static uint32_t tempSamples[NUM_SAMPLES] = {INIT_ZERO};

    if (TempCheck_Counter <(uint8_t)5)
    {



        tempSamples[TempCheck_Counter] = ADC_ReadValue((uint32_t)ADC0_BASE, (uint32_t)3);
        TempCheck_Counter++;

    }
    else {
        uint32_t sum = INIT_ZERO;
        uint32_t Average_Temp;
        bool remoteFlag = false;
        TempCheck_Counter =INIT_ZERO;
        uint8_t i =INIT_ZERO;
        for (i = (uint8_t)INIT_ZERO; i < (uint8_t)NUM_SAMPLES; i++)
        {
            sum += tempSamples[i];
        }

        Average_Temp = (uint8_t)(sum / (uint8_t)NUM_SAMPLES);
        Average_Temp = (uint32_t)50 + (((uint32_t)Average_Temp) * ((uint32_t)200 - (uint32_t)50)) / (uint32_t)4060;

        uint8_t bytes[4]={INIT_ZERO};

        bytes[0] = (uint8_t)(((uint32_t)Average_Temp >> 24) & (uint8_t)0xFF);
        bytes[1] = (uint8_t)(((uint32_t)Average_Temp >> 16) & (uint8_t)0xFF);
        bytes[2] = (uint8_t)(((uint32_t)Average_Temp >> 8) & (uint8_t)0xFF);
        bytes[3] = (uint8_t)(((uint32_t)Average_Temp ) & (uint8_t)0xFF);

        uint8_t msgData[8];

        msgData[0] = bytes[0];
        msgData[1] = bytes[1];
        msgData[2] = bytes[2];
        msgData[3] = bytes[3];
        char buffer[16]={INIT_ZERO};
        UART_Sprintf(Average_Temp, buffer, (uint8_t)10);
        UART_sendString("\r\nADC Value: ", (uint8_t)0);
        UART_sendString(buffer,(uint8_t) 0);

        UART_sendString("\n", (uint8_t)0);

        CANTransmit((uint8_t)CAN0_Index, (uint8_t)TempSensorObject, msgData, (uint32_t)8,remoteFlag);
    }



}

/***************************************************************
Function Name   : TASK_RemoteFrame
Inputs          : None
Outputs         : None
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : This task receives a CAN message, checks its length, reads a voltage value from the ADC, and sends the voltage value via UART and CAN.
****************************************************************/
void TASK_RemoteFrame (void)
{

    uint8_t received_data_error[8]= {INIT_ZERO} ;
    uint32_t ReceivedMSG_LEN =  CanReceiveMessage((uint8_t)CAN0_Index,REMOTEFRAME_OBJECT,received_data_error);
    if (ReceivedMSG_LEN ==(uint32_t)10)
    {

        uint32_t tempSamples[NUM_SAMPLES] = {0};
        bool remoteFlag = false;
        uint32_t Average_Temp;

        tempSamples[0] = ADC_ReadValue((uint32_t)ADC0_BASE, (uint32_t)0);
        Average_Temp = tempSamples[0];
        uint8_t bytes[4]={INIT_ZERO};

        bytes[0] = (uint8_t)(((uint32_t)Average_Temp >> 24) & (uint8_t)0xFF);
        bytes[1] = (uint8_t)(((uint32_t)Average_Temp >> 16) & (uint8_t)0xFF);
        bytes[2] = (uint8_t)(((uint32_t)Average_Temp >> 8) & (uint8_t)0xFF);
        bytes[3] = (uint8_t)(((uint32_t)Average_Temp ) & (uint8_t)0xFF);


        uint8_t msgData[8];


        msgData[0] = bytes[0];
        msgData[1] = bytes[1];
        msgData[2] = bytes[2];
        msgData[3] = bytes[3];

        char buffer[16]= {INIT_ZERO};


        UART_Sprintf(Average_Temp, buffer,(uint8_t) 10);


        UART_sendString("\r\nVoltage Value: ", (uint8_t)0);
        UART_sendString(buffer,(uint8_t) 0);


        UART_sendString("\n",(uint8_t) 0);

        CANTransmit((uint8_t)CAN0_Index, (uint8_t)TempSensorObject, msgData, (uint32_t)8,remoteFlag);
    }

}



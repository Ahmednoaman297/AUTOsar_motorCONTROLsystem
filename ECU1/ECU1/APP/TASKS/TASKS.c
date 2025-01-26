/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2024
 *      Author: elder
 */

#include "TASKS.h"

uint8_t STATE =INIT_ZERO;
uint8_t LED =INIT_ZERO;
uint8_t UART_FLAG_SEND=INIT_ZERO;
uint8_t g_taskTimerIdleDelay=INIT_ZERO;
uint8_t g_receiveState=INIT_ZERO;
uint8_t received_data[8];
uint8_t buttonCOUNT=0;
uint8_t task_communicationFlag_overHeat=0;
uint32_t consecutive_counteroverHEAT=0;
uint32_t consecutive_counterConnection=0;
uint8_t task_ConsecutiveFlag_COMCounter=0;
uint8_t INIT_FLAG=1;
uint8_t MONITOR_overHEAT=0;
uint8_t TASK_MONITOR_fault_STATE=0;
uint8_t TASK_MONITOR_comLOST=0;
uint8_t TASKS_testMODEflag=0;
char buffer[16];  /* Buffer to hold the string */
char buffer2[16];
uint8_t Task_UARTFLAG_recPC=0;
uint8_t TASK_FLAGblink_REDled=0;
uint8_t TASK_FLAGblink_BLUEled=0;
uint8_t TASK_FLAGblink_Whiteled=0;
uint8_t task_flag_blink_enter_tester=0;
uint8_t task_flag_blink_exit_tester=0;
uint8_t g_unexpectedTemp=0;
uint8_t data[8];
uint8_t flag_green=0;
uint32_t commCheck_timedelay=0;

/***************************************************************
Function Name   : TASK_INITS
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Initializes various modules including GPIO, UART, CAN, and EEPROM.
                  Reads values from EEPROM memory locations to determine fault conditions.
                  If specific fault conditions are met, suspends tasks in the operating system.
 ****************************************************************/

void TASK_INITS (void)
{

    static  uint8_t CanIndex_Array=INIT_ZERO;
    static uint8_t GpioIndex_array=INIT_ZERO;
    UART_FLAG_SEND= GPIO_init(GpioIndex_array);
    UART_FLAG_SEND=configure_all_uarts();
    UART_FLAG_SEND= CANInitialize(CanIndex_Array);
    Eeprom_Init();
    uint32_t g_eeprom1Value=0;
    uint32_t g_eeprom2Value=0;
    uint32_t g_eeprom3Value=0;

    NVM_Read(ADDRESS_fault, (uint32_t*)&g_eeprom1Value);
    NVM_Read(ADDRESS_communication, (uint32_t*)&g_eeprom2Value);
    NVM_Read(ADDRESS_overheat, (uint32_t*)&g_eeprom3Value);

    if(g_eeprom1Value==FAULT_code)
    {
        MONITORING_DTC_FLAG=(uint8_t)1;
        OS_SuspendTask(TASTKS_INITS_valueINDEX);
        OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
        OS_SuspendTask(TASK_blinkBlueLED_valueINDEX);
        OS_SuspendTask(TASK_blinkWhiteLED_valueINDEX);
        OS_SuspendTask(keep_ALIVE_valueINDEX);
        OS_SuspendTask(ADC_health_check_valueINDEX);
    }
    else if(g_eeprom2Value>(uint32_t)2)
    {
        MONITORING_DTC_FLAG =(uint8_t)1;
        OS_SuspendTask(TASTKS_INITS_valueINDEX);
        OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
        OS_SuspendTask(TASK_blinkRedLED_valueINDEX);
        OS_SuspendTask(TASK_blinkWhiteLED_valueINDEX);
        OS_SuspendTask(keep_ALIVE_valueINDEX);
        OS_SuspendTask(ADC_health_check_valueINDEX);
    }
    else if(g_eeprom3Value>(uint32_t)2)
    {
        MONITORING_DTC_FLAG =(uint8_t)1;
        OS_SuspendTask(TASTKS_INITS_valueINDEX);
        OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
        OS_SuspendTask(TASK_blinkBlueLED_valueINDEX);
        OS_SuspendTask(TASK_blinkRedLED_valueINDEX);
        OS_SuspendTask(keep_ALIVE_valueINDEX);
        OS_SuspendTask(ADC_health_check_valueINDEX);
    }else{}


}

void TASK_BTN_READ(void)
{
    static uint8_t TASKBTN_Flag =INIT_ZERO;
    static uint32_t TimeDelay_BTN =INIT_ZERO;
    uint8_t switch1 = BTN_read((uint8_t)FIRST_SWITCH,(uint32_t) GPIO_PORTF_BASE);
    uint8_t switch2 = BTN_read((uint8_t)SECOND_SWITCH, (uint32_t)GPIO_PORTF_BASE);

    if ((switch1 == PRESSED) || (switch2 == PRESSED))
    {
        if ((TASKBTN_Flag == CONDITION_ZERO) && (TimeDelay_BTN == CONDITION_ZERO))
        {

            TimeDelay_BTN = SYSTICK_Flag ;
            TASKBTN_Flag =SetFlag;
        }
        else if (((SYSTICK_Flag - TimeDelay_BTN)>= (uint32_t)150) && (TASKBTN_Flag ==ConditionFlag ))
        {
            uint8_t switch_1 = BTN_read((uint8_t)FIRST_SWITCH,(uint32_t) GPIO_PORTF_BASE);
            uint8_t switch_2 = BTN_read((uint8_t)SECOND_SWITCH, (uint32_t)GPIO_PORTF_BASE);

            if ((switch_1 == PRESSED) && (switch_2 == PRESSED))
            {
                TASKS_testMODEflag=(uint8_t)1;
            }
            else{}

        }else{}
    }
    else
    {
        TimeDelay_BTN=INIT_ZERO;
        TASKBTN_Flag =INIT_ZERO;
    }
}

/***************************************************************
Function Name   : TASK_BTN_READ
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Reads the state of two buttons and manages button press events.
                  Sets a test mode flag if both buttons are pressed under specific conditions.
 ****************************************************************/

void TASK_UARTSEND (void)
{
    static uint8_t UartIndex_Array=0;

    switch (UART_FLAG_SEND)
    {
    case NO_DATATOSEND:
    {

        break;
    }
    case CAN_ERROR_CAN_Module:
    {
        UART_sendString("Error in can module\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case UART_ERROR_INVALID_MODULE:
    {
        UART_sendString("UART_ERROR_INVALID_MODULE\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case GPIO_ERROR:
    {
        UART_sendString("Error GPIO module\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case ENTER_TESTER:
    {
        UART_sendString("System enters Tester mode\r\n"
                , UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTredLED:
    {
        UART_sendString("test red led \r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTblueLED:
    {
        UART_sendString("test blue led \r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTgreenLED:
    {
        UART_sendString("test green led \r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTwhiteLED:
    {
        UART_sendString("test white led \r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTtemp:
    {
        UART_sendString("ADC Readings= ", UartIndex_Array);
        UART_sendString(buffer, 0);  // Send the converted ADC value
        UART_sendString("\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case TESTvoltage:
    {
        UART_sendString("test voltage  \r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
    case EXIT_TESTER:
    {
        UART_sendString("System exit Tester mode\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }

    case Connection_lost:
    {
        UART_sendString("ECU2: Connection lost\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }


    case FAULT_STATE:
        UART_sendString("ECU2: system is in FAULT_STATE:", UartIndex_Array);
        UART_sendString(buffer2, 0);  // Send the converted ADC value
        UART_sendString(" VOLT", UartIndex_Array);
        UART_sendString("\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case NORMAL_TEMP:
        UART_sendString("Motor temperature is normal :", UartIndex_Array);
        UART_sendString(buffer, 0);  // Send the converted ADC value
        UART_sendString("\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case NOT_NORMAL_TEMP:
        UART_sendString("Motor temperature is not normal:", UartIndex_Array);
        UART_sendString(buffer, 0);  // Send the converted ADC value
        UART_sendString("\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case OverHeat_code:
        UART_sendString("Motor temperature is overheat:", UartIndex_Array);
        UART_sendString(buffer, 0);  // Send the converted ADC value
        UART_sendString("\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    case FAILEDoverHEAT:
        UART_sendString("DTC OVER HEAT FAILED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case CONFIRMEDoverHEAT:
        UART_sendString("DTC OVER HEAT CONFIRMED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case CONFIRMEDfault:
        UART_sendString("DTC FAULT STATE CONFIRMED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case FAILEDfault:
        UART_sendString("DTC FAULT STATE FAILED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case CONFIRMEDlostcon:
        UART_sendString("DTC LOST COM CONFIRMED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case FAILEDlostcon:
        UART_sendString("DTC LOST COM FAILED\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    case Warning:
        UART_sendString("warning in tester mode\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;

    default:
        UART_sendString("ECU2: Error unidentified state received\r\n", UartIndex_Array);
        UART_FLAG_SEND=INIT_ZERO;
        break;
    }
}

/***************************************************************
Function Name   : TASK_ReceiveCAN
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Receives data from the CAN bus, processes the received temperature data,
                  and performs appropriate actions based on the temperature range.
                  Controls LEDs and monitors overheat conditions. Sends feedback via CAN
                  when operating in the normal temperature range. Implements a counter
                  to detect unexpected temperature conditions.
 ****************************************************************/

void TASK_ReceiveCAN (void)
{
    uint32_t flag =INIT_ZERO;
    /*  uint8_t g_unexpectedTemp=0;    */
    static uint8_t counter_temp=0;

    flag =CanReceiveMessage(CAN0_Index, DATAERRORRECEIVING_OBJECT, received_data);

    uint32_t getData = ((uint32_t)received_data[0] << 24) |
            ((uint32_t)received_data[1] << 16) |
            ((uint32_t)received_data[2] << 8) |
            ((uint32_t)received_data[3]);

    if (flag == (uint32_t)8 )
    {
        if( ((uint32_t)50< getData )&&( (uint32_t)130>getData))
        {


            LED_greenLight();
            TASK_FLAGblink_BLUEled=(uint8_t)0;
            TASK_FLAGblink_REDled=(uint8_t)0;
            TASK_FLAGblink_Whiteled=(uint8_t)0;
            g_unexpectedTemp=(uint8_t)0;
            MONITOR_overHEAT=(uint8_t)0;

            /*in normal temp  */
            UART_FLAG_SEND = NORMAL_TEMP;
            uint8_t task_recCAN_tempSTATE=(uint8_t)NORMAL_TEMP;
            CANTransmit((uint8_t)CAN0_Index, (uint8_t)5, (uint8_t*)&task_recCAN_tempSTATE, (uint32_t)MSG_LENGTH, (bool)false);
            if(counter_temp>(uint8_t)0)
            {

                counter_temp=(uint8_t)0;

            }

        }
        else if(((uint32_t)130<getData) &&((uint32_t)200>getData))
        {
            counter_temp++;
            if(counter_temp==(uint8_t)6)
            {
                g_unexpectedTemp=(uint8_t)1;
                counter_temp=(uint8_t)0;
                UART_FLAG_SEND = NOT_NORMAL_TEMP;

            }else{}

        }else{}

    }

}
/***************************************************************
Function Name   : keep_ALIVE
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Implements a keep-alive mechanism to ensure communication
                  between nodes. Sends periodic messages over CAN, checks for
                  responses, and monitors communication status. If no response
                  is received within a defined timeout, flags communication
                  loss and sets error states. Resets flags upon successful
                  response.
 ****************************************************************/

void keep_ALIVE (void)
{
    static uint8_t ErrorCheck_flag =INIT_ZERO;
    static uint32_t ErrorCheck_timedelay =INIT_ZERO;

    uint32_t flag;
    uint8_t received_data_error[8]={INIT_ZERO};


    if (ErrorCheck_flag ==INIT_ZERO)
    {
        ErrorCheck_flag=SetFlag;

        CANTransmit((uint8_t)CAN0_Index, (uint8_t)4, 0, (uint32_t)MSG_LENGTH, (bool)false);
        ErrorCheck_timedelay =SYSTICK_Flag;
    }
    else
    {
        flag = CanReceiveMessage(CAN0_Index, ISConnectedReceivingObject, received_data_error);
        if (((SYSTICK_Flag - ErrorCheck_timedelay) <= (uint32_t)5000 )|| (flag==MSG_LENGTH ))
        {

            if (flag!=(uint32_t)CONDITION_ZERO)
            {
                ErrorCheck_timedelay = SYSTICK_Flag;
                if (received_data_error[0] == SENDERRORCHECK)
                {
                    task_ConsecutiveFlag_COMCounter = (uint8_t)1;

                    ErrorCheck_flag =INIT_ZERO;
                    TASK_FLAGblink_BLUEled=INIT_ZERO;
                    TASK_MONITOR_comLOST=(uint8_t)0;
                    commCheck_timedelay=(uint8_t)0;


                }
                else
                {}
            }
            else
            {}
        }
        else
        {

            if((task_ConsecutiveFlag_COMCounter ==(uint8_t) 1 )||( INIT_FLAG ==(uint8_t) 1))
            {
                task_ConsecutiveFlag_COMCounter = (uint8_t)0;
                INIT_FLAG =(uint8_t) 0;
                TASK_MONITOR_comLOST=(uint8_t)1;

            }else{}
            ErrorCheck_timedelay = SYSTICK_Flag;

            ErrorCheck_flag =INIT_ZERO;

        }
    }


}
/***************************************************************
Function Name   : TASK_blinkWhiteLED
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Controls the blinking of the white LED based on specific conditions.
 ****************************************************************/

void TASK_blinkWhiteLED (void)
{

    static uint32_t BlinkWhite_timeDelay = INIT_ZERO;
    static uint8_t BlinkWhite_Flag = INIT_ZERO;
    static uint8_t Led_counter = INIT_ZERO;
    if(1==TASK_FLAGblink_Whiteled || MONITORING_DTC_FLAG == 1)
    {

        uint8_t condition1 = (BlinkWhite_Flag == CONDITION_ZERO);
        uint8_t condition3 = (BlinkWhite_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkWhite_timeDelay) >= (uint32_t)1000);



        if(task_flag_blink_enter_tester==1 ||task_flag_blink_exit_tester==1)
        {
            if (Led_counter ==4)
            {
                if (task_flag_blink_exit_tester==1)
                {
                    OS_ResumeTask(TASK_ReceiveCAN_valueINDEX);
                }

                TASK_FLAGblink_Whiteled =0;
                Led_counter=0;
                UART_FLAG_SEND=0;
                task_flag_blink_enter_tester=0;
                task_flag_blink_exit_tester=0;
            }
            if(condition1 && condition2)
            {
                LED_whiteLight();
                BlinkWhite_Flag=1;
                Led_counter++;
                BlinkWhite_timeDelay = SYSTICK_Flag;

            }
            else if(condition3 && condition2 )

            {
                LEDS_off();
                BlinkWhite_timeDelay = SYSTICK_Flag;
                BlinkWhite_Flag=0;
                Led_counter++;
            }
        }
        else if(task_flag_blink_enter_tester==0)
        {
            if (condition1 && condition2  )
            {
                Led_counter++;
                BlinkWhite_Flag = SetFlag;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LED_whiteLight();
            }
            else if (condition3 && condition2 )
            {
                Led_counter++;
                BlinkWhite_Flag = INIT_ZERO;
                BlinkWhite_timeDelay = SYSTICK_Flag;
                LEDS_off();
                if(10==Led_counter)
                {
                    TASK_FLAGblink_Whiteled=0;
                    Led_counter =0;

                }

            }
            else{

            }

        }
    }
}
/***************************************************************
Function Name   : TASK_blinkBlueLED
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Controls the blinking of the blue LED based on specific conditions.

 ****************************************************************/

void TASK_blinkBlueLED (void)
{


    static uint32_t BlinkBlue_timeDelay = INIT_ZERO;
    static uint8_t BlinkBlue_Flag = INIT_ZERO;
    static uint8_t Led_counter = INIT_ZERO;
    if(((uint8_t)1==TASK_FLAGblink_BLUEled) || (MONITORING_DTC_FLAG == (uint8_t)1))
    {
        uint8_t condition1 = (BlinkBlue_Flag == CONDITION_ZERO);
        uint8_t condition3 = (BlinkBlue_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkBlue_timeDelay) >= (uint32_t)1000);
        if (condition1 && condition2  )
        {
            task_ConsecutiveFlag_COMCounter = (uint8_t)0;
            Led_counter++;
            BlinkBlue_Flag = SetFlag;
            BlinkBlue_timeDelay = SYSTICK_Flag;
            LED_blueLight();
        }
        else if (condition3 && condition2 )
        {

            task_ConsecutiveFlag_COMCounter = (uint8_t)0;
            Led_counter++;
            BlinkBlue_Flag = INIT_ZERO;
            BlinkBlue_timeDelay = SYSTICK_Flag;
            LEDS_off();
            if((uint8_t)10==Led_counter)
            {
                TASK_FLAGblink_BLUEled=(uint8_t)0;

            }
        }
        else{}
    }
    else{}



}
/***************************************************************
Function Name   : TASK_blinkRedLED
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Controls the blinking of the red LED based on specific conditions.

 ****************************************************************/

void TASK_blinkRedLED (void)
{

    static uint32_t BlinkRed_timeDelay = INIT_ZERO;
    static uint8_t BlinkRed_Flag = INIT_ZERO;
    static uint8_t Led_counter = INIT_ZERO;

    if(((uint8_t)1==TASK_FLAGblink_REDled )|| (MONITORING_DTC_FLAG == (uint8_t)1))
    {

        uint8_t condition1 = (BlinkRed_Flag == CONDITION_ZERO);
        uint8_t condition3 = (BlinkRed_Flag != CONDITION_ZERO);
        uint8_t condition2 = ((SYSTICK_Flag - BlinkRed_timeDelay) >= (uint32_t)1000);
        if (condition1 && condition2  )
        {
            Led_counter++;
            BlinkRed_Flag = SetFlag;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LED_redLight();
        }
        else if (condition3 && condition2 )
        {
            Led_counter++;
            BlinkRed_Flag = INIT_ZERO;
            BlinkRed_timeDelay = SYSTICK_Flag;
            LEDS_off();
            if((uint8_t)10==Led_counter)
            {
                TASK_FLAGblink_REDled=(uint8_t)0;

            }

        }
        else{}


    }
}
/***************************************************************
Function Name   : ADC_health_check
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Monitors the ADC data to check the system's health.
                  Converts the received data into a voltage value and performs
                  checks based on voltage levels and temperature conditions.
                  Flags an overheat or fault state depending on the analysis.
                  Sends a CAN message and receives ADC data for evaluation.
 ****************************************************************/

void ADC_health_check(void)
{

    if ((uint8_t)1==g_unexpectedTemp)
    {

        CANTransmit((uint8_t)CAN0_Index,(uint8_t) 1,(uint8_t*) NULL,(uint32_t) 0, (bool)true);

        CanReceiveMessage((uint8_t)CAN0_Index,(uint8_t)2, (uint8_t*)data);

        uint32_t getData = ((uint32_t)data[0] << 24) |
                ((uint32_t)data[1] << 16) |
                ((uint32_t)data[2] << 8) |
                ((uint32_t)data[3]);
        float voltage = ((float)getData / (float)4095.0) * (float)3.3;

        if((voltage>(float)3) && (voltage<(float)3.3) && (NOT_NORMAL_TEMP) && ((uint8_t)0==MONITOR_overHEAT))
        {
            MONITOR_overHEAT=(uint8_t)1;


        }

        /*fault*/
        else if( NOT_NORMAL_TEMP  && (voltage<(float)3) && (voltage>=(float)0.5) )
        {
            TASK_MONITOR_fault_STATE=(uint8_t)1;

        }else{}
    }

}
/***************************************************************
Function Name   : monitoring_task_checker
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Checks monitoring flags for overheat, fault, or communication
                  loss conditions. Clears the unexpected temperature flag when
                  applicable and triggers the corresponding communication monitor
                  action based on the detected condition.
 ****************************************************************/

void monitoring_task_checker(void)
{
    if(((uint8_t)1==g_unexpectedTemp)&&((uint8_t)1==MONITOR_overHEAT))
    {
        g_unexpectedTemp = (uint8_t)0;
        Monitor_Communication(OverHeat_code);

    }
    else if(((uint8_t)1==g_unexpectedTemp)&&((uint8_t)1==TASK_MONITOR_fault_STATE))
    {
        g_unexpectedTemp = (uint8_t)0;
        Monitor_Communication(FAULT_code);

    }
    else if((uint8_t)1==TASK_MONITOR_comLOST)
    {
        Monitor_Communication(lostCOM_code);

    }else{}


}
/***************************************************************
Function Name   : ON_BoardDIAGnostic
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles on-board diagnostic tasks by processing UART-received
                  commands and managing system states. Depending on received
                  commands, it performs EEPROM reads, suspends/resumes tasks,
                  and updates monitoring flags and diagnostic sessions.
 ****************************************************************/

void ON_BoardDIAGnostic(void)
{

    static uint8_t UartIndex_Array = 0;

    /*Poll for new data and add it to the buffer*/
    UART_pollReceive(UartIndex_Array);
    static uint8_t flag = 0 ;
    /* Process data from the buffer*/
    int32_t uart_receivedData = UART_bufferGet();
    if (uart_receivedData != -1) {
        Task_UARTFLAG_recPC =(uint8_t) uart_receivedData;

    }
    uint32_t g_eeprom1Value=0;
    uint32_t g_eeprom2Value=0;
    uint32_t g_eeprom3Value=0;

    if (uart_receivedData == (uint32_t)'1')
    {
        OS_SuspendTask(TASTKS_INITS_valueINDEX);
        OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
        OS_SuspendTask(TASK_blinkBlueLED_valueINDEX);
        OS_SuspendTask(TASK_blinkRedLED_valueINDEX);

        OS_SuspendTask(TASK_blinkWhiteLED_valueINDEX);
        OS_SuspendTask(keep_ALIVE_valueINDEX);
        OS_SuspendTask(ADC_health_check_valueINDEX);
        UART_FLAG_SEND=DIAGNOSTICsession;
        flag =(uint8_t)1 ;
    }
    if (flag ==(uint8_t)1 )
    {
        switch (uart_receivedData)
        {
        case '4':
        {
            NVM_Read((uint32_t)0x100, (uint32_t*)&g_eeprom1Value);
            if(g_eeprom1Value==FAULT_code)
            {
                UART_FLAG_SEND=CONFIRMEDfault;
            }
            else
            {
                UART_FLAG_SEND=FAILEDfault;

            }
        }
        break;
        case '2':
        {
            NVM_Read((uint32_t)0x200, (uint32_t*)&g_eeprom2Value);
            if(g_eeprom2Value>(uint32_t)2)
            {
                UART_FLAG_SEND=CONFIRMEDlostcon;

            }
            else
            {
                UART_FLAG_SEND=FAILEDlostcon;

            }
        }
        break;
        case '3':
        {
            NVM_Read((uint32_t)0x300, (uint32_t*)&g_eeprom3Value);

            if(g_eeprom3Value>(uint32_t)2)
            {
                UART_FLAG_SEND=CONFIRMEDoverHEAT;

            }
            else
            {
                UART_FLAG_SEND=FAILEDoverHEAT;

            }
        }
        break;
        case '6':
        {
            MONITORING_DTC_FLAG = (uint8_t)0;
            OS_ResumeTask(TASTKS_INITS_valueINDEX);
            OS_ResumeTask(TASK_BTN_READ_valueINDEX);
            OS_ResumeTask(TASK_ReceiveCAN_valueINDEX);
            OS_ResumeTask(TASK_UARTSEND_valueINDEX);
            OS_ResumeTask(TASK_blinkBlueLED_valueINDEX);
            OS_ResumeTask(TASK_blinkRedLED_valueINDEX);
            OS_ResumeTask(TASK_blinkWhiteLED_valueINDEX);
            OS_ResumeTask(keep_ALIVE_valueINDEX);
            OS_ResumeTask(ADC_health_check_valueINDEX);
            OS_ResumeTask(monitoring_task_checker_valueINDEX);
            flag =(uint8_t)0 ;
        }
        break;
        case '5':
        {
            NVM_Read((uint32_t)0x100,(uint32_t*) &g_eeprom1Value);
            NVM_Read((uint32_t)0x200,(uint32_t*) &g_eeprom2Value);
            NVM_Read((uint32_t)0x300,(uint32_t*) &g_eeprom3Value);

            if(g_eeprom1Value==FAULT_code)
            {
                MONITORING_DTC_FLAG=(uint8_t)1;
                OS_SuspendTask(TASTKS_INITS_valueINDEX);
                OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
                OS_SuspendTask(TASK_blinkBlueLED_valueINDEX);
                OS_SuspendTask(TASK_blinkWhiteLED_valueINDEX);
                OS_SuspendTask(keep_ALIVE_valueINDEX);
                OS_SuspendTask(ADC_health_check_valueINDEX);
                flag = (uint8_t)0;
            }
            else if(g_eeprom2Value>(uint32_t)2)
            {
                MONITORING_DTC_FLAG =(uint8_t)1;
                OS_SuspendTask(TASTKS_INITS_valueINDEX);
                OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
                OS_SuspendTask(TASK_blinkRedLED_valueINDEX);
                OS_SuspendTask(TASK_blinkWhiteLED_valueINDEX);
                OS_SuspendTask(keep_ALIVE_valueINDEX);
                OS_SuspendTask(ADC_health_check_valueINDEX);
                flag = (uint8_t)0;
            }
            else if(g_eeprom3Value>(uint32_t)2)
            {
                MONITORING_DTC_FLAG =(uint8_t)1;
                OS_SuspendTask(TASTKS_INITS_valueINDEX);
                OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);
                OS_SuspendTask(TASK_blinkBlueLED_valueINDEX);
                OS_SuspendTask(TASK_blinkRedLED_valueINDEX);
                OS_SuspendTask(keep_ALIVE_valueINDEX);
                OS_SuspendTask(ADC_health_check_valueINDEX);
                flag = (uint8_t)0;
            }
            else if (MONITORING_DTC_FLAG ==(uint8_t)0)
            {
                OS_ResumeTask(TASTKS_INITS_valueINDEX);
                OS_ResumeTask(TASK_BTN_READ_valueINDEX);
                OS_ResumeTask(TASK_ReceiveCAN_valueINDEX);
                OS_ResumeTask(TASK_UARTSEND_valueINDEX);
                OS_ResumeTask(TASK_blinkBlueLED_valueINDEX);
                OS_ResumeTask(TASK_blinkRedLED_valueINDEX);
                OS_ResumeTask(TASK_blinkWhiteLED_valueINDEX);
                OS_ResumeTask(keep_ALIVE_valueINDEX);
                OS_ResumeTask(ADC_health_check_valueINDEX);
                OS_ResumeTask(monitoring_task_checker_valueINDEX);
                flag = (uint8_t)0;
            }else{}

        }
        break;
        default:
            break;

        }
    }

}
/***************************************************************
Function Name   : TESTER_mode
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Manages the tester mode for debugging and system validation.
                  Handles UART commands to test GPIO and ADC functionality,
                  blink LEDs, and manage task suspensions and resumptions.
                  Includes communication timeout handling for robustness.
 ****************************************************************/

void TESTER_mode(void)
{
    static uint8_t Gpio_Manipulate_Flag=0;
    static uint8_t ADC_Test_Flag=0;
    static uint8_t flag=0;
    static uint8_t commCheck_timedelay_flag =0;

    if( 1==TASKS_testMODEflag ||Task_UARTFLAG_recPC=='8')//d5lt tester
    {
        Task_UARTFLAG_recPC=0;
        UART_FLAG_SEND=ENTER_TESTER;
        TASK_FLAGblink_Whiteled=1;
        TASKS_testMODEflag=0;
        flag=1;
        OS_SuspendTask(TASTKS_INITS_valueINDEX);
        OS_SuspendTask(TASK_BTN_READ_valueINDEX);
        OS_SuspendTask(TASK_ReceiveCAN_valueINDEX);

        OS_SuspendTask(9);
        OS_SuspendTask(8);
        OS_SuspendTask(10);
        task_flag_blink_enter_tester=1;
        CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);
    }



    if (flag ==1)
    {
        if(1==TASK_MONITOR_comLOST )

        {
            UART_FLAG_SEND=Warning;
            TASK_FLAGblink_BLUEled=1;
            if (commCheck_timedelay_flag == 0)
            {
                commCheck_timedelay_flag =1;

                commCheck_timedelay =SYSTICK_Flag;
            }
            if(0!=TASK_MONITOR_comLOST && (SYSTICK_Flag - commCheck_timedelay) > (uint32_t)30000 )
            {
                TASK_MONITOR_comLOST=0;
                TASK_FLAGblink_BLUEled=0;
                UART_FLAG_SEND=EXIT_TESTER;
                flag =0;
                commCheck_timedelay_flag =0;


            }
            else
            {

            }

        }
        else
        {

            static uint8_t UartIndex_Array = 0;
            if (Gpio_Manipulate_Flag == 0 && ADC_Test_Flag ==0)
            {

                UART_pollReceive(UartIndex_Array);
//                static uint8_t flag = 0 ;

            }
            if ((Task_UARTFLAG_recPC == '1' || Gpio_Manipulate_Flag == 1) && ADC_Test_Flag ==0 )
            {

                ADC_Test_Flag =0;
                Gpio_Manipulate_Flag =1;

                switch(Task_UARTFLAG_recPC)
                {
                case '6':
                    UART_FLAG_SEND=TESTredLED;
                    LED_redLight();
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);
                    break;
                case '2':
                    UART_FLAG_SEND=TESTblueLED;
                    LED_blueLight();
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);
                    break;
                case '3':
                    UART_FLAG_SEND=TESTgreenLED;
                    LED_greenLight();
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);

                    break;
                case '4':
                    UART_FLAG_SEND=TESTwhiteLED;
                    LED_whiteLight();
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);

                    break;
                case '5':
                    Gpio_Manipulate_Flag =0;
                    flag =0;
                    OS_ResumeTask(TASTKS_INITS_valueINDEX);
                    OS_ResumeTask(TASK_BTN_READ_valueINDEX);

                    OS_ResumeTask(TASK_UARTSEND_valueINDEX);
                    OS_ResumeTask(TASK_blinkBlueLED_valueINDEX);
                    OS_ResumeTask(TASK_blinkRedLED_valueINDEX);
                    OS_ResumeTask(TASK_blinkWhiteLED_valueINDEX);
                    OS_ResumeTask(keep_ALIVE_valueINDEX);
                    OS_ResumeTask(ADC_health_check_valueINDEX);
                    OS_ResumeTask(monitoring_task_checker_valueINDEX);
                    OS_ResumeTask(ON_BoardDIAGnostic_valueINDEX);
                    OS_ResumeTask(TESTER_mode_valueINDEX);
                    UART_FLAG_SEND=EXIT_TESTER;
                    TASK_FLAGblink_Whiteled =1;
                    task_flag_blink_exit_tester=1;
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);

                    break;
                }
            }
            else if((Task_UARTFLAG_recPC == '2' ||ADC_Test_Flag==1) && Gpio_Manipulate_Flag ==0)
            {
                ADC_Test_Flag =1;
                Gpio_Manipulate_Flag =0;

                switch(Task_UARTFLAG_recPC)
                {
                case '1':
                    UART_FLAG_SEND=TESTtemp;
                    CanReceiveMessage(CAN0_Index, DATAERRORRECEIVING_OBJECT, received_data);

                    uint32_t getData = ((uint32_t)received_data[0] << 24) |
                            ((uint32_t)received_data[1] << 16) |
                            ((uint32_t)received_data[2] << 8) |
                            ((uint32_t)received_data[3]);

                    SPRINTF(getData, buffer, 10);

                    break;

                case '5':
                    ADC_Test_Flag =0;
                    flag =0;
                    OS_ResumeTask(TASTKS_INITS_valueINDEX);
                    OS_ResumeTask(TASK_BTN_READ_valueINDEX);

                    OS_ResumeTask(TASK_UARTSEND_valueINDEX);
                    OS_ResumeTask(TASK_blinkBlueLED_valueINDEX);
                    OS_ResumeTask(TASK_blinkRedLED_valueINDEX);
                    OS_ResumeTask(TASK_blinkWhiteLED_valueINDEX);
                    OS_ResumeTask(keep_ALIVE_valueINDEX);
                    OS_ResumeTask(ADC_health_check_valueINDEX);
                    OS_ResumeTask(monitoring_task_checker_valueINDEX);
                    OS_ResumeTask(ON_BoardDIAGnostic_valueINDEX);
                    OS_ResumeTask(TESTER_mode_valueINDEX);
                    UART_FLAG_SEND=EXIT_TESTER;
                    TASK_FLAGblink_Whiteled =1;
                    task_flag_blink_exit_tester=1;
                    CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);

                    commCheck_timedelay_flag =0;
                    break;

                }
            }
            else if (Task_UARTFLAG_recPC == '5')
            {
                ADC_Test_Flag =0;
                Gpio_Manipulate_Flag =0;
                flag =0;
                OS_ResumeTask(TASTKS_INITS_valueINDEX);
                OS_ResumeTask(TASK_BTN_READ_valueINDEX);

                OS_ResumeTask(TASK_UARTSEND_valueINDEX);
                OS_ResumeTask(TASK_blinkBlueLED_valueINDEX);
                OS_ResumeTask(TASK_blinkRedLED_valueINDEX);
                OS_ResumeTask(TASK_blinkWhiteLED_valueINDEX);
                OS_ResumeTask(keep_ALIVE_valueINDEX);
                OS_ResumeTask(ADC_health_check_valueINDEX);
                OS_ResumeTask(monitoring_task_checker_valueINDEX);
                OS_ResumeTask(ON_BoardDIAGnostic_valueINDEX);
                OS_ResumeTask (TESTER_mode_valueINDEX);
                TASK_FLAGblink_REDled =0 ;
                TASK_FLAGblink_BLUEled =0;
                TASK_FLAGblink_Whiteled =1;
                UART_FLAG_SEND=EXIT_TESTER;
                task_flag_blink_exit_tester=1;
                CANTransmit(CAN0_Index, 5,&UART_FLAG_SEND, MSG_LENGTH, false);

                commCheck_timedelay_flag =0;
                Task_UARTFLAG_recPC =0 ;

            }

        }



    }
}

void TASK_UARTreceive(void)
{
    Task_UARTFLAG_recPC=0;
    static uint8_t UartIndex_Array = 0;
    UART_pollReceive(UartIndex_Array);
    int32_t receivedData = UART_bufferGet();
    if (receivedData != -1) {
        Task_UARTFLAG_recPC = receivedData;
    }
}

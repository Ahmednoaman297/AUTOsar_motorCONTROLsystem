/*
 * OS_CONFIG.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */



/********************************************Includes*********************************/
#include "OS_CONFIG.h"


/********************************************global and static variables*********************************/

TaskDescriptor taskList[MAX_TASKS] =
{
 {&TASK_INITS,
  .priodicity = 0,
  .tickCount = 0,
  .isPreiodic = false,
  .isHighPriority = true,
  .isSuspended = false},     /* Initialization task*/

  {&TASK_BTN_READ,
   .priodicity = 1,
   .tickCount = 0,
   .isPreiodic = true,
   .isHighPriority = false,
   .isSuspended = false}, /* Periodic task with 1000 ticks interval*/

   {&TASK_ReceiveCAN,
    .priodicity = 500,
    .tickCount = 0,
    .isPreiodic = true,
    .isHighPriority = false,
    .isSuspended = false},

    {&TASK_UARTSEND,
     .priodicity = 1000,
     .tickCount = 0,
     .isPreiodic = true,
     .isHighPriority = false,
     .isSuspended = false}, /* Periodic task with 1000 ticks interval*/

     /* Periodic task with 1000 ticks interval*/
     {&TASK_blinkBlueLED ,
      .priodicity = 1,
      .tickCount = 0,
      .isPreiodic = true,
      .isHighPriority = false,
      .isSuspended = false},

      {&TASK_blinkRedLED ,
       .priodicity = 1,
       .tickCount = 0,
       .isPreiodic = true,
       .isHighPriority = false,
       .isSuspended = false},

       {&TASK_blinkWhiteLED ,
        .priodicity = 1,
        .tickCount = 0,
        .isPreiodic = true,
        .isHighPriority = false,
        .isSuspended = false},

        {&keep_ALIVE ,
         .priodicity = 100,
         .tickCount = 0,
         .isPreiodic = true,
         .isHighPriority = false,
         .isSuspended = false},

         {&ADC_health_check ,
          .priodicity = 300,
          .tickCount = 0,
          .isPreiodic = true,
          .isHighPriority = false,
          .isSuspended = false},

          {&monitoring_task_checker ,
           .priodicity = 10,
           .tickCount = 0,
           .isPreiodic = true,
           .isHighPriority = false,
           .isSuspended = false},
           {&ON_BoardDIAGnostic ,
            .priodicity = 100,
            .tickCount = 0,
            .isPreiodic = true,
            .isHighPriority = false,
            .isSuspended = false},
            {&TESTER_mode,
             .priodicity = 100,
             .tickCount = 0,
             .isPreiodic = true,
             .isHighPriority = false,
             .isSuspended = false}

};

const uint8_t NUMBER_OF_tasks = MAX_TASKS;

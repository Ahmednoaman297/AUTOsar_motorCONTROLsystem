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

  {&TASK_ReceiveCAN,
   .priodicity = 500,
   .tickCount = 0,
   .isPreiodic = true,
   .isHighPriority = false,
   .isSuspended = false},

   {&TASK_RECEIVED_DATA_CHECK,
    .priodicity = 1,
    .tickCount = 0,
    .isPreiodic = true,
    .isHighPriority = false,
    .isSuspended = false},

    {&TASK_REDLED,
     .priodicity = 50,
     .tickCount = 0,
     .isPreiodic = true,
     .isHighPriority = false,
     .isSuspended = false},

     {&TASK_GREENLED,
      .priodicity = 50,
      .tickCount = 0,
      .isPreiodic = true,
      .isHighPriority = false,
      .isSuspended = false},

      {&TASK_WHITELED,
       .priodicity = 50,
       .tickCount = 0,
       .isPreiodic = true,
       .isHighPriority = false,
       .isSuspended = false},

       {&TASK_errorCheck,
        .priodicity = 10,
        .tickCount = 0,
        .isPreiodic = true,
        .isHighPriority = false,
        .isSuspended = false}, /* Periodic task with 1000 ticks interval*/

        {&TASK_blinkBlueLED,
         .priodicity = 10,
         .tickCount = 0,
         .isPreiodic = true,
         .isHighPriority = false,
         .isSuspended = false},

         {&TASK_TempCheck,
          .priodicity = 100,
          .tickCount = 0,
          .isPreiodic = true,
          .isHighPriority = false,
          .isSuspended = false},

          {&TASK_RemoteFrame,
           .priodicity = 600,
           .tickCount = 0,
           .isPreiodic = true,
           .isHighPriority = false,
           .isSuspended = false}
};

const uint8_t NUMBER_OF_tasks = MAX_TASKS;

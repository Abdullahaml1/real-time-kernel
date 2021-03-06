/*
    FreeRTOS V6.1.0 - Copyright (C) 2010 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

#define SYS_CLOCK 16000000U

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h" // from tivawoare
#include "driverlib/interrupt.h" // from tivawoare
#include "driverlib/sysctl.h" // from tivawoare
#include "driverlib/gpio.h" // from tivawoare
#include "driverlib/timer.h" // from tivawoare
#include "driverlib/uart.h" // from tivawoare
#include "utils/uartstdio.h" // from tivawoare


/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/*-----------------------------------------------------------*/
/* configs and intits */
/*-----------------------------------------------------------*/
// init uart for printing
void InitConsole(void); 

// Timer0B handler



/*-----------------------------------------------------------*/
/* The tasks to be created. */
static void vHandlerTask( void *pvParameters );
static void vPeriodicTask( void *pvParameters );

/* The service routine for the interrupt.  This is the interrupt that the
   task will be synchronized with. */
void vSoftwareInterruptHandler( void );

/*-----------------------------------------------------------*/

/* Declare a variable of type xSemaphoreHandle.  This is used to reference the
   semaphore that is used to synchronize a task with an interrupt. */
xSemaphoreHandle xBinarySemaphore;

xTaskHandle xHandlerHandle;

/*-----------------------------------------------------------*/

int main( void )
{

  //-----------------------------------------------------------------------
  // init portF leds
  //-----------------------------------------------------------------------
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  GPIO_PORTF_DATA_R  = 0x00U; // write led

  //-----------------------------------------------------------------------
  // init Timer and systick
  //-----------------------------------------------------------------------

  // The Timer0 peripheral must be enabled for use.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  // Set up the serial console to use for displaying messages.  This is
  // just for this example program and is not needed for Systick operation.
  InitConsole();

  // Configure Timer0B as a 16-bit periodic timer.
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);


  // Set the Timer0B load value to 1ms.
  TimerLoadSet(TIMER0_BASE, TIMER_B, SYS_CLOCK/100);

  // Enable interrupts to the processor.
  IntMasterEnable();

  // Enable the SysTick Interrupt.
  SysTickIntEnable();

  // Enable SysTick.
  SysTickEnable();

  // Configure the Timer0B interrupt for timer timeout.
  TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

  // Enable the Timer0B interrupt on the processor (NVIC).
  IntEnable(INT_TIMER0B);






  // Display the setup on the console.
  UARTprintf("Starting Code ->");
  UARTprintf("\n   >>>>>>>>>>>\n\n");


   /* Before a semaphore is used it must be explicitly created.  In this example
      a binary semaphore is created. */
   vSemaphoreCreateBinary( xBinarySemaphore );

   /* Check the semaphore was created successfully. */
   if( xBinarySemaphore != NULL )
     {

       /* Create the 'handler' task.  This is the task that will be synchronized
          with the interrupt.  The handler task is created with a high priority to
          ensure it runs immediately after the interrupt exits.  In this case a
          priority of 3 is chosen. */
       xTaskCreate( vHandlerTask, "Handler", 240, NULL, 1, &xHandlerHandle );

       /* Create the task that will periodically generate a software interrupt.
          This is created with a priority below the handler task to ensure it will
          get preempted each time the handler task exits the Blocked state. */
       /* xTaskCreate( vPeriodicTask, "Periodic", 240, NULL, 3, NULL ); */



       /* Start the scheduler so the created tasks start executing. */
       vTaskStartScheduler();
     }

   /* If all is well we will never reach here as the scheduler will now be
      running the tasks.  If we do reach here then it is likely that there was
      insufficient heap memory available for a resource to be created. */
   for( ;; );


}


/*-----------------------------------------------------------*/

static void vHandlerTask( void *pvParameters )
{
  /* As per most tasks, this task is implemented within an infinite loop.

     Take the semaphore once to start with so the semaphore is empty before the
     infinite loop is entered.  The semaphore was created before the scheduler
     was started so before this task ran for the first time.*/
  xSemaphoreTake( xBinarySemaphore, 0 );


  // Enable Timer0B.
  TimerEnable(TIMER0_BASE, TIMER_B);

  for( ;; )
    {
      /* Use the semaphore to wait for the event.  The task blocks
         indefinitely meaning this function call will only return once the
         semaphore has been successfully obtained - so there is no need to check
         the returned value. */
      xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );

      // our timer0b event
      GPIO_PORTF_DATA_R  ^= 0x04U; // toggling blue led

      /* To get here the event must have occurred.  Process the event (in this
         case we just print out a message). */
      UARTprintf("Handler task - Processing event.\n");
    }
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void *pvParameters )
{
  /* As per most tasks, this task is implemented within an infinite loop. */

  // Enable Timer0B.
  TimerEnable(TIMER0_BASE, TIMER_B);

  vTaskPrioritySet( xHandlerHandle, 4);
  for( ;; )
    {
      /* This task is just used to 'simulate' an interrupt.  This is done by
         periodically generating a software interrupt. */
      vTaskDelay( 500 / portTICK_RATE_MS );

      UARTprintf("We are in periodic Task\n");

          }
}
/*-----------------------------------------------------------*/


void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining - and
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
	is set to either 1 or 2 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
	FreeRTOSConfig.h. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}


//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PCTL_PA0_U0RX);
    GPIOPinConfigure(GPIO_PCTL_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}


/* Timer0b ISR Handler  */

void Timer0BIntHandler(void)
{
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  /* 'Give' the semaphore to unblock the task. */
  xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );


  // Clear the timer interrupt flag.
  TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);


  /* Giving the semaphore may have unblocked a task - if it did and the
     unblocked task has a priority equal to or above the currently executing
     task then xHigherPriorityTaskWoken will have been set to pdTRUE and
     portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
     higher priority task.

     NOTE: The syntax for forcing a context switch within an ISR varies between
     FreeRTOS ports.  The portEND_SWITCHING_ISR() macro is provided as part of
     the Cortex M3 port layer for this purpose.  taskYIELD() must never be called
     from an ISR! */
  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );

}

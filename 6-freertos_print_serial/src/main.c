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


#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h" // from tivawoare
#include "driverlib/sysctl.h" // from tivawoare
#include "driverlib/gpio.h" // from tivawoare
#include "driverlib/uart.h" // from tivawoare
#include "utils/uartstdio.h" // from tivawoare


/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"


//---------------------------------------------------------------
// defining the system clock too Free RTOS
//---------------------------------------------------------------
uint32_t SystemCoreClock = 16000000; // for free rtos config

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );



// initializing UART 
void InitConsole(void);


/*-----------------------------------------------------------*/

int main( void )
{

  // Set up the serial console to use for displaying messages.  This is
  // just for this example program and is not needed for Systick operation.
  InitConsole();

  // Display the setup on the console.
  UARTprintf("SysTick Firing Interrupt ->");
  UARTprintf("\n   Rate = 1sec\n\n");

  //-----------------------------------------------------------------------
  // init portF leds
  //-----------------------------------------------------------------------
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  GPIO_PORTF_DATA_R  = 0x08U; // write led



	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					200,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 200, NULL, 1, NULL );

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task1\n";
volatile unsigned long ul;
volatile unsigned long u2;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{

    GPIO_PORTF_DATA_R  = 0x04U; // blue led
    UARTprintf("\%s", pcTaskName);

		/* Print out the name of this task. */
		/* vPrintString( pcTaskName ); */

		/* Delay for a period. */

/* 		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) */
/* //		for( ul = 0; ul < 0xFFFE0; ul++ ) */

/* 		{ */
/* 			u2=2; */
/* 			/\* This loop is just a very crude delay implementation.  There is */
/* 			nothing to do in here.  Later exercises will replace this crude */
/* 			loop with a proper delay/sleep function. *\/ */
/* 		} */
	}
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task2\n";
volatile unsigned long ul2;
volatile unsigned long u22;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{

    GPIO_PORTF_DATA_R  = 0x08U; // green led
    UARTprintf("\%s", pcTaskName);

		/* Print out the name of this task. */
		/* vPrintString( pcTaskName ); */

		/* Delay for a period. */
		/* for( ul2 = 0; ul2 < mainDELAY_LOOP_COUNT; ul2++ ) */
		/* { */
		/* 	u22=2; */
		/* 	/\* This loop is just a very crude delay implementation.  There is */
		/* 	nothing to do in here.  Later exercises will replace this crude */
		/* 	loop with a proper delay/sleep function. *\/ */
		/* } */
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


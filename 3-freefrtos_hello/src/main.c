
#include <stdint.h>
#include "tm4c123gh6pm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );



int main(void)
{

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

  while(1)
    {
    }
  return 0;

}

void vTask1( void *pvParameters )
{
volatile unsigned long ul;
volatile unsigned long u2;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
    // Red
    GPIO_PORTF_DATA_R  = 0x02U; // write led

		/* Delay for a period. */

		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
//		for( ul = 0; ul < 0xFFFE0; ul++ )

		{
			u2=2;
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
	}
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
volatile unsigned long ul2;
volatile unsigned long u22;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
    // Blue
    GPIO_PORTF_DATA_R  = 0x04U; // write led

		/* Delay for a period. */
		for( ul2 = 0; ul2 < mainDELAY_LOOP_COUNT; ul2++ )
		{
			u22=2;
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
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

/* void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ) */
/* { */
/* 	/\* This function will only be called if a task overflows its stack.  Note */
/* 	that stack overflow checking does slow down the context switch */
/* 	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW */
/* 	is set to either 1 or 2 in FreeRTOSConfig.h. *\/ */
/* 	for( ;; ); */
/* } */
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}
/* ----------------------------------------------------------- */

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}

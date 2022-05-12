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

/*-----------------------------------------------------------*/
/* configs and intits */
/*-----------------------------------------------------------*/
// init uart for printing
void InitConsole(void); 

// Timer0B handler





int main(void)
{

  //-----------------------------------------------------------------------
  // Initializing the LEDS
  /* //----------------------------------------------------------------------- */
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  GPIO_PORTF_DATA_R  = 0x00U; // write led

  //-----------------------------------------------------------------------
  // Initializing Timer0B
  //-----------------------------------------------------------------------
  // The Timer0 peripheral must be enabled for use.
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  // Set up the serial console to use for displaying messages.  This is
  // just for this example program and is not needed for Systick operation.
  InitConsole();

  // Configure Timer0B as a 16-bit periodic timer.
  TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

  // Set the Timer0B load value to 1ms.
  TimerLoadSet(TIMER0_BASE, TIMER_B, 0xffff);

  // Enable interrupts to the processor.
  IntMasterEnable();

  // Configure the Timer0B interrupt for timer timeout.
  TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

  // Enable the Timer0B interrupt on the processor (NVIC).
  IntEnable(INT_TIMER0B);

  // Enable Timer0B.
  TimerEnable(TIMER0_BASE, TIMER_B);



  // Display the setup on the console.
  UARTprintf("Starting Code ->");
  UARTprintf("\n   >>>>>>>>>>>\n\n");


  while(1)
    {
    }
  return 0;

}

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



void Timer0BIntHandler(void)
{


  // Clear the timer interrupt flag.
  TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

  GPIO_PORTF_DATA_R  ^= 0x04U; // toggle blue led
  UARTprintf("hit timer \n");

}

#include "BoardSupportPackage.h"


#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"


// form tivaware
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

extern void os_tick();
extern void os_sched();


// systick counter
static uint64_t volatile systick_counter;


void
bsp_initUartPrintf(void)
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
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

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
    UARTStdioConfig(0, 115200, CLOCK_RATE);
}



void bsp_init() {
  //-----------------------------------------------------------------------
  // Initializing the LEDS
  //-----------------------------------------------------------------------
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  /* GPIO_PORTF_DATA_R  = 0x08U; // write led */


  //-----------------------------------------------------------------------
  // Initializing Uart
  //-----------------------------------------------------------------------
  bsp_initUartPrintf();
}

void bsp_os_init(){
  //-----------------------------------------------------------------------
  // Initializing systick counter
  //-----------------------------------------------------------------------
  systick_counter =0;

  //-----------------------------------------------------------------------
  // Initializing Systick
  //-----------------------------------------------------------------------


  // Enable the SysTick Interrupt.
  /* SysTickIntEnable(); */

  // Enable SysTick.
  /* SysTickEnable(); */

  // STCTRL systick status and control reegister
  // enabling systicka and its interrupt with the
  // source is the MCU clock
  NVIC_ST_CTRL_R = 0x7;

  // setting the period of the systick
  NVIC_ST_RELOAD_R = CLOCK_RATE / SYSTICK_TICK_PER_SECOND; //24 bit
  NVIC_ST_CURRENT_R = 0;

  //setting the systick prority to 5
  // System Handler Priority 3 (SYSPRI3) [29:31]
  NVIC_SYS_PRI3_R |= 0xA0000000; // 5


  /* To fire the systick maually we set the peding bit (26) in */
  /* NVIC_INT_CTRL_R: Interrupt control and state register */
  /* NVIC_INT_CTRL_R = NVIC_INT_CTRL_R | 0x04000000; */


  //-----------------------------------------------------------------------
  // Initializing Pendsv
  //-----------------------------------------------------------------------

  //setting the pendsv prority to the lowest ->7
  // System Handler Priority 3 (SYSPRI3) [21:23]
  NVIC_SYS_PRI3_R |= (0xe << 20);
}






void bsp_os_start() {
  // Enable interrupts to the processor.
  IntMasterEnable();
}




void SystickHandler(void) {
  // disabling interrupt 
  IntMasterDisable();

  systick_counter ++;


  // decrement thread->deadlineCouner for all threads and.
  // puhes new threads to the os_servieQueue
  os_tick();


  // reomoves the current thread that called os_threadYield.
  //and gets the next thread to run form the foint of the Ascednding order
  os_sched();

  // enabling interrupt 
  IntMasterEnable();
}



uint64_t bsp_getSystickCounter() {
  uint32_t counter;

  IntMasterDisable();
  counter = systick_counter;
  IntMasterEnable();

  return counter;
}


void bsp_delay(uint32_t delay){
  uint64_t start;
  start = bsp_getSystickCounter();
  while ((uint32_t)(bsp_getSystickCounter() - start) < delay) ;
}



void bsp_LedsOffAll() {
  GPIO_PORTF_DATA_R  = 0x0U; 
}

void bsp_LedGreenOn() {
  GPIO_PORTF_DATA_R  |= 0x8U; // writing green led
}



void bsp_LedBlueOn() {
  GPIO_PORTF_DATA_R  |= 0x4U; // writing blue led
}



void bsp_LedRedOn() {
  GPIO_PORTF_DATA_R  |= 0x2U; // writing red led
}

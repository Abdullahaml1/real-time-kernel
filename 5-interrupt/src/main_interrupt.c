#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h" // include form tivaware 




int main(void)
{

  //-----------------------------------------------------------------------
  // Initializing the LEDS
  //-----------------------------------------------------------------------
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  GPIO_PORTF_DATA_R  = 0x08U; // write led

  //-----------------------------------------------------------------------
  // Initializing Systick
  //-----------------------------------------------------------------------

  // Enable interrupts to the processor.
  IntMasterEnable();

  // Enable the SysTick Interrupt.
  SysTickIntEnable();

  // Enable SysTick.
  SysTickEnable();

  // STCTRL systick control reegister
  NVIC_ST_CTRL_R = 0x7;

  NVIC_ST_RELOAD_R = 0xFFFFFF;
  NVIC_ST_CURRENT_R = 0;


  while(1)
    {
    }
  return 0;

}


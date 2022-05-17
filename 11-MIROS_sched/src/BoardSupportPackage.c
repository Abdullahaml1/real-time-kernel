#include "BoardSupportPackage.h"


#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/interrupt.h" // include form tivaware



// systick counter
static uint64_t volatile systick_counter;

void bsp_init() {
  //-----------------------------------------------------------------------
  // Initializing the LEDS
  //-----------------------------------------------------------------------
  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  /* GPIO_PORTF_DATA_R  = 0x08U; // write led */
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

  //setting the systick prority to the highest ->0
  // System Handler Priority 3 (SYSPRI3) [29:31]
  NVIC_SYS_PRI3_R &= 0x0fffffff;


  /* To fire the systick maually we set the peding bit (26) in */
  /* NVIC_INT_CTRL_R: Interrupt control and state register */
  /* NVIC_INT_CTRL_R = NVIC_INT_CTRL_R | 0x04000000; */


  //-----------------------------------------------------------------------
  // Initializing Pendsv
  //-----------------------------------------------------------------------

  //setting the pendsv prority to the lowest ->7
  // System Handler Priority 3 (SYSPRI3) [21:23]
  NVIC_SYS_PRI3_R |= (0xe << 20);



  // Enable interrupts to the processor.
  IntMasterEnable();
}




void SystickHandler(void) {
  systick_counter ++;
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

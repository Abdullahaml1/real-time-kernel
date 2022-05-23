#include <stdint.h>
#include "BoardSupportPackage.h"
#include "miros.h"


//UARTprintf
#include "utils/uartstdio.h"

//disable interrupt
#include "driverlib/interrupt.h"


// definition the struct that will handle the the thread's variables
// and stack for blinkRred thread
os_Thread blinkRedThread;
void blinkRed();

os_Thread blinkGreenThread;
void blinkGreen();

os_Thread blinkBlueThread;
void blinkBlue();


// the function that will execute while there are not
// threads to run
void os_idleThreadHandler();

int main(void)
{
  bsp_init();
  bsp_os_init();
  os_init();

  //Initializing the thread with:
  os_createThreadPeriodic(&blinkRedThread,
                          &blinkRed, // the thread's handler
                          200); // the rate at which the thread will run
                                // with respect to the systick counter

  os_createThreadPeriodic(&blinkGreenThread,
                          &blinkGreen,
                          100);

  os_createThreadPeriodic(&blinkBlueThread,
                          &blinkBlue,
                          50);

  UARTprintf("starting ->>\n");

  // Starting the OS IE: Enabling Interrupt
  bsp_os_start();

  while(1)
    {
     }
  return 0;

}

void os_idleThreadHandler() {
  while (1) {
  }
}


void blinkGreen() {
  while (1){
    UARTprintf("Green\n");
    bsp_LedGreenOn();
    /* bsp_delay(100); */
    bsp_LedsOffAll();
    /* bsp_delay(100); */

    // giving the control to the OS
    os_threadYield();
  }
}


void blinkBlue() {
  while(1){
    UARTprintf("Blue\n");
    bsp_LedBlueOn();
    /* bsp_delay(100); */
    bsp_LedsOffAll();
    /* bsp_delay(100); */

    // giving the control to the OS
    os_threadYield();
  }
}



void blinkRed() {
  while(1){
    UARTprintf("Red\n");
    bsp_LedRedOn();
    /* bsp_delay(100); */
    bsp_LedsOffAll();
    /* bsp_delay(100); */

    // giving the control to the OS
    os_threadYield();
  }
}

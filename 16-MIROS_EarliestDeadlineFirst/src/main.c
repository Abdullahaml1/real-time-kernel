#include <stdint.h>
#include "BoardSupportPackage.h"
#include "miros.h"


//UARTprintf
#include "utils/uartstdio.h"

//disable interrupt
#include "driverlib/interrupt.h"


os_Thread blinkRedThread;
void blinkRed();

os_Thread blinkGreenThread;
void blinkGreen();

os_Thread blinkBlueThread;
void blinkBlue();



int main(void)
{
  bsp_init();
  bsp_os_init();
  os_init();

  os_createThreadPeriodic(&blinkRedThread,
                          &blinkRed,
                          200);

  os_createThreadPeriodic(&blinkGreenThread,
                          &blinkGreen,
                          100);

  os_createThreadPeriodic(&blinkBlueThread,
                          &blinkBlue,
                          50);

  UARTprintf("starting ->>\n");
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

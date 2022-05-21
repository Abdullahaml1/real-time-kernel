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

  os_createThread(&blinkRedThread,
                  &blinkRed);

  os_createThread(&blinkGreenThread,
                  &blinkGreen);

  os_createThread(&blinkBlueThread,
                  &blinkBlue);

  UARTprintf("starting ->>\n");
  bsp_os_start();

  while(1)
    {
     }
  return 0;

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

/* This program will toggle the onboard LED if SW1 is pressed, and keep the
 * onboard LED on if SW2 is pressed or keep it off if buttons are released */

//By: Yusef Karim
//July 14, 2017

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>




int main(void)
{

  SYSCTL_RCGCGPIO_R = 0x20U; // enable prortF clock gating
  GPIO_PORTF_DIR_R  = 0x0EU; // direction to output
  GPIO_PORTF_DEN_R  = 0x0EU;
  GPIO_PORTF_DATA_R  = 0x04U; // write led

  while(1)
    {
    }
  return 0;

}


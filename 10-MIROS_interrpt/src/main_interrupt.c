#include <stdint.h>
#include "BoardSupportPackage.h"


void blinkGreen() {
  bsp_LedGreenOn();
  bsp_delay(100);
  bsp_LedsOffAll();
  bsp_delay(100);
}



void blinkBlue() {
  bsp_LedBlueOn();
  bsp_delay(100);
  bsp_LedsOffAll();
  bsp_delay(100);
}


int main(void)
{
  bsp_init();


  while(1)
    {
      blinkBlue();
      blinkBlue();

     }
  return 0;

}


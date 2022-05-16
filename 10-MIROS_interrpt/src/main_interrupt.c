#include <stdint.h>
#include "BoardSupportPackage.h"


void blinkGreen() {
  while (1){
    bsp_LedGreenOn();
    bsp_delay(100);
    bsp_LedsOffAll();
    bsp_delay(100);
  }
}



void blinkBlue() {
  while(1){
    bsp_LedBlueOn();
    bsp_delay(100);
    bsp_LedsOffAll();
    bsp_delay(100);
  }
}


int main(void)
{
  bsp_init();


  while(1)
    {
      blinkBlue();
      blinkGreen();

     }
  return 0;

}


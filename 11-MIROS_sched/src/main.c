#include <stdint.h>
#include "BoardSupportPackage.h"
#include "miros.h"


os_Thread blinkGreenThread;
void blinkGreen();

os_Thread blinkBlueThread;
void blinkBlue();



int main(void)
{
  bsp_init();
  bsp_os_init();

  os_CreateThread(&blinkBlueThread,
                  &blinkBlue);


  os_CreateThread(&blinkGreenThread,
                  &blinkGreen);

  while(1)
    {
     }
  return 0;

}


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

#include "interruptHandlers.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void SystickHandler(void) {
  GPIO_PORTF_DATA_R  ^= 0x08U; // write  green led
}

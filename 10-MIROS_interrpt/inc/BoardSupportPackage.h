#ifndef BOARD_SUPPORT_PACKAGE_H
#define BOARD_SUPPORT_PACKAGE_H


#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/interrupt.h" // include form tivaware 


#define CLOCK_RATE  16000000U
#define SYSTICK_TICK_PER_SECOND  100U //10 ms


/*
 * [Initializing PortF, Systick, and PendSv]
 */
void bsp_init();


/*
 * [The handler for Systick Interrupt]
 */
void SystickHandler(void);



/*
 * [getter method for the counter]
 * @return [returns the current systick counter]
 */
uint64_t bsp_getSystickCounter();


/**
 * [block delay using systick]
 * @param delay [the value of the delay]
 */
void bsp_delay(uint32_t delay);


void bsp_LedsOffAll();

void bsp_LedGreenOn();
void bsp_LedBlueOn();
void bsp_LedRedOn();


#endif

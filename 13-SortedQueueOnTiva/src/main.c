#include <stdint.h>
#include <stdbool.h>

// form tivaware
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h" // UARTUARTprintf

#include "SortedQueue.h"


#define CLOCK_RATE 16000000U


void print_queue(sq_Queue *queue) {
  sq_Node *itr = queue->head;

  while (itr != NULL) {
    UARTprintf("[%d]=%d, ", itr->priority, itr->block);
    itr = itr->next;
  }
  UARTprintf("\n");
  UARTprintf("size=%d", sq_getSize(queue));
  UARTprintf("\n");
}




void
initUartUARTprintf(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, CLOCK_RATE);
}





int main(void)
{
  initUartUARTprintf();

  sq_Queue queue;
  sq_init(&queue);
  int32_t i=0;
  uint32_t x;
  uint32_t arr[] = {8, 1, 3, 2, 4, -1, 3, 3, 3, 1, 9, 10, 11, 2, 3, 13};

  for (i=0; i<8; i++) {
    if (!sq_isFull(&queue)) {
      sq_pushAndSort(&queue, i+10, arr[i]);
    }

    print_queue(&queue);
    UARTprintf("-----------\n");
  }
  UARTprintf("\n\n");

  for (i=0; i<4; i++) {
    if (!sq_isEmpty(&queue)) {
      x = sq_popFront(&queue);
      UARTprintf("x=%d\n",x);
    }

    print_queue(&queue);
    UARTprintf("-----------\n");
  }
  UARTprintf("\n\n");


  for (i=8; i<16; i++) {
    if (!sq_isFull(&queue)) {
      sq_pushAndSort(&queue, i+10, arr[i]);
    }

    print_queue(&queue);
    UARTprintf("-----------\n");
  }
  UARTprintf("\n\n");

  for (i=0; i<10; i++) {
    if (!sq_isEmpty(&queue)) {
      x = sq_popFront(&queue);
      UARTprintf("x=%d\n",x);
    }

    print_queue(&queue);
    UARTprintf("-----------\n");
  }
  UARTprintf("\n\n");



  while(1)
    {

     }
  return 0;

}


#include "miros.h"
#include "tm4c123gh6pm.h"
#include <stddef.h>

#include <stdbool.h>
#include "driverlib/interrupt.h" //enable disable interrupt

/**
 * [Switching context Algorithm]
 * 1-when interrupts happens MCU pushes 8 regs in
 * the stack: xpsr, pc, lr, r12, r3, r2 , r1, r0
 * 2-aftet the ISR returns is pops them back ie:
 * pc = pc saved from stack
 * ** to switch context: **
 * 3-Inside the ISR Handler we changes pc to the
 * our stack like struct: sp = ourStacksSp with
 * the 8 location prefailed with xpsr,
 pc=ourfunction Address, lr, r12, r3, r2 , r1, r0
 * 4-after the return form the ISR pc = pc form
 our stack which is the addresss of the function
 * 5-when ISR hits again with the intention to
 switch context save the current pc at the
 thread's pc: currentThread -> pc = pc
 * 6- the pc will equals to the next thread's pc
 * pc = nextThread->pc
 */



os_Thread *volatile os_threadPool[MAX_NUM_THREADS];

os_Thread *volatile os_currentThread;
os_Thread *volatile os_nextThread;


uint32_t volatile i;
uint8_t volatile os_switchContext;



uint32_t os_threadCounter;

uint8_t os_yield;


void os_init() {
  os_currentThread = NULL;
  os_nextThread = NULL;

  os_switchContext =0;
  os_threadCounter =0;
  os_yield =0;
  i =0;
}




void os_createThread(os_Thread *thread,
                     os_ThreadHandler threadHandler
                     ) {
  //---------------------------------------------
  // creating Thread's stack
  //---------------------------------------------
  // our stack grows form lower address to the
  // higher address
  os_StackElement *sp =
    (os_StackElement *)((uint32_t)(thread->stack + THREAD_STACK_SIZE)/8 * 8);

  #ifdef DEBUG_STACK
  uint32_t i=0;
  for(i=0; i<THREAD_STACK_SIZE; i++)
    {
      thread->stack[i]=i;
    }
  #endif

  *(--sp) = 0x61000000;  /* xPSR */
  *(--sp) = (os_StackElement)threadHandler; /* PC */
  *(--sp) = 0x0000000EU; /* LR  */
  *(--sp) = 0x0000000CU; /* R12 */
  *(--sp) = 0x00000003U; /* R3  */
  *(--sp) = 0x00000002U; /* R2  */
  *(--sp) = 0x00000001U; /* R1  */
  *(--sp) = 0x00000000U; /* R0  */
  /* additionally, fake registers R4-R11 */
  *(--sp) = 0x0000000BU; /* R11 */
  *(--sp) = 0x0000000AU; /* R10 */
  *(--sp) = 0x00000009U; /* R9 */
  *(--sp) = 0x00000008U; /* R8 */
  *(--sp) = 0x00000007U; /* R7 */
  *(--sp) = 0x00000006U; /* R6 */
  *(--sp) = 0x00000005U; /* R5 */
  *(--sp) = 0x00000004U; /* R4 */

  thread->sp = sp;


  //---------------------------------------------
  // Inserting tasks into the pool
  //---------------------------------------------
  os_threadPool[os_threadCounter] = thread;
  os_threadCounter ++;

}


void os_sched(){

  // if os_yield=1
  if (os_yield==1) {

    // take the task out of the queue

    //get the next thread
    os_nextThread = os_threadPool[i];
    i= (i+1)%os_threadCounter;

    // os_yield=0
    os_yield =0;
  }
  else {
    //get the next thread
    os_nextThread = os_threadPool[i];
    i= (i+1)%os_threadCounter;
  }

  if (os_currentThread != os_nextThread) {
    os_switchContext =1;
    //fires pendsv interrupt INTCTRL bit 28
    NVIC_INT_CTRL_R |= 0x10000000;
  }
}

void PendsvHandler(void) {
  __asm volatile
    (
     "CPSID   I      \n " //disable interrupt

     /* if (OS_curr != (os_currentThread *)0) */
     "  LDR           r1,=os_currentThread  \n"
     "  LDR           r1,[r1,#0x00]     \n"
     "  CBZ           r1,next_thread \n"

     /*     push registers r4-r11 on the stack */
     "  PUSH          {r4-r11}          \n"

     // currentThread->sp = sp
     "  LDR           r1,=os_currentThread  \n"
     "  LDR           r1,[r1,#0x00]     \n"
     "  STR           sp,[r1,#0x00]     \n"

     "next_thread:                      \n"
     // sp = nextThread->sp
     "  LDR           r1,=os_nextThread  \n"
     "  LDR           r1,[r1,#0x00]     \n"
     "  LDR           sp,[r1,#0x00]     \n"


     /* os_currentThread = os_nextThread ; */
     "  LDR           r1,=os_nextThread \n"
     "  LDR           r1,[r1,#0x00]     \n"
     "  LDR           r2,=os_currentThread  \n"
     "  STR           r1,[r2,#0x00]     \n"

     /* pop registers r4-r11 */
     "  POP           {r4-r11}          \n"

     "CPSIE   I      \n " //disable interrupt


     /* return to the next thread */
     "  BX            lr                \n"
     );

}



void os_threadYield(os_Thread *thread) {
  IntMasterDisable();

  os_yield=1;
  os_sched();

  IntMasterEnable();
}

#include "miros.h"

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
 */


void os_CreateThread(os_Thread *thread,
                     os_ThreadHandler threadHandler
                     ) {
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
  /* *(--sp) = 0x0000000BU; /\* R11 *\/ */
  /* *(--sp) = 0x0000000AU; /\* R10 *\/ */
  /* *(--sp) = 0x00000009U; /\* R9 *\/ */
  /* *(--sp) = 0x00000008U; /\* R8 *\/ */
  /* *(--sp) = 0x00000007U; /\* R7 *\/ */
  /* *(--sp) = 0x00000006U; /\* R6 *\/ */
  /* *(--sp) = 0x00000005U; /\* R5 *\/ */
  /* *(--sp) = 0x00000004U; /\* R4 *\/ */

  thread->sp = sp;

}

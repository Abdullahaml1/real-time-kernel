#ifndef MIROS_H
#define MIROS_H

#include <stdint.h>

#define THREAD_STACK_SIZE 80
#define MAX_NUM_THREADS 10
// #define DEBUG_STACK


typedef void (*os_ThreadHandler)();

typedef uint32_t os_StackElement;



/*
 * the definition of the Thread struct
 */
typedef struct {
  os_StackElement *sp;
  os_StackElement stack[THREAD_STACK_SIZE];
  uint32_t rate;
  int32_t deadlineCounter;
} os_Thread;






/*
 * [initializing the OS]
 * */
void os_init();

/*
 * [Creating a new periodic thread IE: inside while(1) loop
 * @param thread [apointer to the the the thread struct]
 * @param threadhandler [a pointer to a function (out thread to create)
 * @param rate [the rate at which the task will arrive]
 * **/
void os_createThreadPeriodic(os_Thread *thread,
                             os_ThreadHandler threadHandler,
                             uint32_t rate
                             );


void os_createThread(os_Thread *thread,
                     os_ThreadHandler threadHandler
                     );

/**
 * [called from SystickHandler only to decrement
 * every deadlineCounter in threads and pushes
 * new thread to the os_serviceQueue]
 */
void os_tick();

/*
 * [schedles the threads as earliest deadline first algorithm. If the thread
 *  called os_threadYield or the deadline comes it will swthch context to the
 *  thread having least deadlineConter IE: front of os_serviceQueue (which is a
 *  sorted queue)]
 * */
void os_sched();

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
 * 3+-push
 * 4-after the return form the ISR pc = pc form
 our stack which is the addresss of the function
 * 5-when ISR hits again with the intention to
 switch context save the current pc at the
 thread's pc: currentThread -> pc = pc
 * 6- the pc will equals to the next thread's pc
 * pc = nextThread->pc
 */
void PendsvHandler(void);

void os_threadYield();


#endif

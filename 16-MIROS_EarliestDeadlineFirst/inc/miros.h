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






void os_init();

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

void os_sched();

void PendsvHandler(void);

void os_threadYield();


#endif

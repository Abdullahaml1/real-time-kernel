#ifndef MIROS_H
#define MIROS_H

#include <stdint.h>

#define THREAD_STACK_SIZE 40

#define DEBUG_STACK


typedef void (*os_ThreadHandler)();

typedef uint32_t os_StackElement;



/*
 * the definition of the Thread struct
 */
typedef struct {
  os_StackElement *sp;
  os_StackElement stack[THREAD_STACK_SIZE];
} os_Thread;


void os_CreateThread(os_Thread *thread,
                     os_ThreadHandler threadHandler
                     );


#endif

#ifndef SORTED_QUEUE_H
#define SORTED_QUEUE_H

#include "DynamicMemory.h"
#include "DynamicMemoryTypes.h"
#include <stdbool.h>

typedef struct sq_Queue {
  sq_Node *head;
  uint32_t len;
} sq_Queue;

void sq_init();

uint32_t sq_getSize();

void sq_pushAndSort(sq_Type block, int32_t priority);

sq_Type sq_showFront();

sq_Type sq_popFront();

bool sq_isEmpty();

bool sq_isFull();

#endif

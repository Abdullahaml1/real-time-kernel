#ifndef SORTED_QUEUE_H
#define SORTED_QUEUE_H

#include "DynamicMemory.h"
#include "DynamicMemoryTypes.h"
#include <stdbool.h>

typedef struct sq_Queue {
  sq_Node *head;
  uint32_t len;
} sq_Queue;

void sq_init(sq_Queue *queue);

uint32_t sq_getSize(sq_Queue *queue);

void sq_pushAndSort(sq_Queue *queue, sq_Type block, int32_t priority);

sq_Type sq_showFront(sq_Queue *queue);

sq_Type sq_popFront(sq_Queue *queue);

bool sq_isEmpty(sq_Queue *queue);

bool sq_isFull(sq_Queue *queue);

#endif

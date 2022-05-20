#include "SortedQueue.h"
#include <stdio.h>
#include <stdint.h>



void print_queue(sq_Queue *queue) {
  sq_Node *itr = queue->head;

  while (itr != NULL) {
    printf("[%d]=%d, ", itr->priority, itr->block);
    itr = itr->next;
  }
  printf("\n");
  printf("size=%d", sq_getSize(queue));
  printf("\n");
}

uint32_t arr[] = {8, 1, 3, 2, 4, -1, 3, 3, 3, 1, 9, 10, 11, 2, 3, 13};

int main(void) {

  sq_Queue queue;
  sq_init(&queue);

  int32_t i=0;
  uint32_t x;
  for (i=0; i<8; i++) {
    if (!sq_isFull(&queue)) {
      sq_pushAndSort(&queue, i+10, arr[i]);
    }

    print_queue(&queue);
    printf("-----------\n");
  }
  printf("\n\n");

  for (i=0; i<4; i++) {
    if (!sq_isEmpty(&queue)) {
      x = sq_popFront(&queue);
      printf("x=%d\n",x);
    }

    print_queue(&queue);
    printf("-----------\n");
  }
  printf("\n\n");


  for (i=8; i<16; i++) {
    if (!sq_isFull(&queue)) {
      sq_pushAndSort(&queue, i+10, arr[i]);
    }

    print_queue(&queue);
    printf("-----------\n");
  }
  printf("\n\n");

  for (i=0; i<10; i++) {
    if (!sq_isEmpty(&queue)) {
      x = sq_popFront(&queue);
      printf("x=%d\n",x);
    }

    print_queue(&queue);
    printf("-----------\n");
  }
  printf("\n\n");


  return 0;
}

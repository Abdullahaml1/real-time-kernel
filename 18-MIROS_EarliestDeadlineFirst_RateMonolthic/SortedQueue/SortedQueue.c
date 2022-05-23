#include "SortedQueue.h"
#include "DynamicMemory.h"
#include <stddef.h>


void sq_init(sq_Queue *queue){
  // initializing dynamic memory allocation
  dym_init();

  queue->head = NULL;
  queue->len=0;
}


uint32_t sq_getSize(sq_Queue *queue) {
  return queue->len;
}



void sq_pushAndSort(sq_Queue *queue, sq_Type block, int32_t *priority){

  //allocating the new node
  sq_Node *new= dym_alloc();
  if (new == NULL) {
    //TODO do something
    return;
  }
  new->block = block;
  new->priority = priority;


  // incrementing len
  queue->len ++;

  // if queue is empty
  if ((queue->head == NULL)) {
    // add the block
    queue->head = new;
    new->next = NULL;
  }

  //the queue is not empty
  else {
    //loop until you find current >prev, current < next
    sq_Node *itr = queue->head;
    sq_Node *past = NULL;
    while(itr != NULL) {

      if (*priority SQ_OPERATOR_PAST *(itr->priority) ) {
        // moving the itr
        past = itr;
        itr = itr->next;

      }
      else if (*priority SQ_OPERATOR_NEXT *(itr->priority) ) {
        break;
      }
    }


    // place it at the head
    if (past == NULL) {

      //place at the top
      new->next = queue->head;
      queue->head =new;
    }

    else {
      new->next = past->next;
      past->next = new;
    }

  } //the queue is not empty else
}


sq_Type sq_showFront(sq_Queue *queue){
  return queue->head->block;
}



sq_Type sq_popFront(sq_Queue *queue) {

  sq_Node *del = queue->head;
  sq_Type block = del->block;

  //remove it
  queue->head = queue->head->next;
  dym_delete(del);
  queue->len --;

  return block;
}


bool sq_isEmpty(sq_Queue *queue) {
  return queue->head == NULL;
}


bool sq_isFull(sq_Queue *queue ) {
  return queue->len == DYM_MEM_MAX_SIZE;
}


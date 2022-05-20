#include "SortedQueue.h"
#include "DynamicMemory.h"
#include <stddef.h>

sq_Queue sq_queue;

void sq_init(){
  // initializing dynamic memory allocation
  dym_init();

  sq_queue.head = NULL;
  sq_queue.len=0;
}


uint32_t sq_getSize() {
  return sq_queue.len;
}



void sq_pushAndSort(sq_Type block, int32_t priority){

  //allocating the new node
  sq_Node *new= dym_alloc();
  if (new == NULL) {
    //TODO do something
    return;
  }
  new->block = block;
  new->priority = priority;


  // incrementing len
  sq_queue.len ++;

  // if queue is empty
  if ((sq_queue.head == NULL)) {
    // add the block
    sq_queue.head = new;
    new->next = NULL;
  }

  //the queue is not empty
  else {
    //loop until you find current >prev, current < next
    sq_Node *itr = sq_queue.head;
    sq_Node *past = NULL;
    while(itr != NULL) {

      if (priority SQ_OPERATOR_PAST itr->priority ) {
        // moving the itr
        past = itr;
        itr = itr->next;

      }
      else if (priority SQ_OPERATOR_NEXT itr->priority ) {
        break;
      }
    }


    // place it at the head
    if (past == NULL) {

      //place at the top
      new->next = sq_queue.head;
      sq_queue.head =new;
    }

    else {
      new->next = past->next;
      past->next = new;
    }

  } //the queue is not empty else
}


sq_Type sq_showFront(){
  return sq_queue.head->block;
}



sq_Type sq_popFront() {

  sq_Node *del = sq_queue.head;
  sq_Type block = del->block;

  //remove it
  sq_queue.head = sq_queue.head->next;
  dym_delete(del);
  sq_queue.len --;

  return block;
}


bool sq_isEmpty() {
  return sq_queue.head == NULL;
}


bool sq_isFull() {
  return sq_queue.len == DYM_MEM_MAX_SIZE;
}


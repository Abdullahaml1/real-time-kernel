#include "DynamicMemory.h"
#include <stddef.h>


dym_List dym_list;

void dym_init() {
  dym_list.head = &dym_list.mem[0];

  uint32_t i=1;
  for(i=0; i<DYM_MEM_MAX_SIZE-1; i++) {
    dym_list.mem[i].next = &dym_list.mem[i+1];
  }

  dym_list.mem[DYM_MEM_MAX_SIZE-1].next=NULL;

}



dym_Type *dym_alloc() {

  if (dym_list.head == NULL) {
    return NULL;
  }
  else {
    // taking the heads memory block;
    dym_Type *p= &dym_list.head->block;

    // forwarding the head to the next location
    dym_list.head = dym_list.head->next;

    return p;
  }
}


void dym_delete(dym_Type *block) {
  if (block == NULL) {
    return;
  }
  dym_Node *node=(dym_Node*)block;
  node->next = dym_list.head;
  dym_list.head = node;
}

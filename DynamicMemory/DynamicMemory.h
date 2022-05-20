#ifndef DYNAMIC_MEMORY_H
#define DYNAMIC_MEMORY_H

#include <stdint.h>
#include "DynamicMemoryTypes.h" // for DYM_MEM_MAX_SIZE, DYM_DATA_TYPE





typedef DYM_DATA_TYPE dym_Type;


typedef struct dym_Node{
  dym_Type block;
  struct dym_Node *next;
} dym_Node;

typedef struct {
  dym_Node *head;
  dym_Node mem[DYM_MEM_MAX_SIZE];
} dym_List;


void dym_init();


dym_Type *dym_alloc();
void dym_delete(dym_Type *block);

#endif

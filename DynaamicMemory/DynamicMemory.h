#ifndef DYNAMIC_MEMORY_H
#define DYNAMIC_MEMORY_H

#include <stdint.h>

#define MEM_MAX_SIZE 16

typedef uint32_t dym_Type;

typedef struct dym_Node{
  dym_Type block;
  struct dym_Node *next;
} dym_Node;

typedef struct {
  dym_Node *head;
  dym_Node mem[MEM_MAX_SIZE];
} dym_List;


void dym_init();


dym_Type *dym_alloc();
void dym_delete(dym_Type *block);

#endif

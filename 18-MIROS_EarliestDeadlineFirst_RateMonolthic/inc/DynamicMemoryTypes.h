#ifndef DYNAMIC_MEMORY_TYPES_H
#define DYNAMIC_MEMORY_TYPES_H

#include "stdint.h"
#include "miros.h" // os_Thread


//for dynamic memory allocation
#define SQ_MEM_MAX_SIZE 16

//ascending queue, or descending
#define SQ_ASCENDING // or SQ_DESCENDING

typedef  os_Thread* sq_Type;




typedef struct sq_Node {
  sq_Type block;
  int32_t *priority;

  struct sq_Node *next;
} sq_Node;

#define DYM_DATA_TYPE sq_Node
#define DYM_MEM_MAX_SIZE SQ_MEM_MAX_SIZE



// choseing ascending or descending with
// rescpect to the new block
#ifdef SQ_ASCENDING
#define SQ_OPERATOR_PAST >=
#define SQ_OPERATOR_NEXT <
#else

#ifdef SQ_DESCENDING
#define SQ_OPERATOR_PAST <=
#define SQ_OPERATOR_NEXT >
#endif

#endif
//--------------------------------


#endif

# Sorted Queue
This is the implmentation of a sorted linked based queue with [Static Dynamic Memory](../DynamicMemory/README.md) as the backend for allocating memeory.

# Usage
we have to define the type of the data block and max memory in file `DynamicMemoryTypes.h`
```c
typedef yourType sq_block;
```

and the max memory so we do not fregment memory as described in [Static Dynamic Memory](../DynamicMemory/README.md)


```c
#define SQ_MEM_MAX_SIZE 16
```

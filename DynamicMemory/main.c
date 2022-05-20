#include "DynamicMemory.h"

#include <stdio.h>

extern dym_List dym_list;

void print_list()
{
  uint32_t i=0;
  for(i=0; i<MEM_MAX_SIZE;i++)
    {
      printf("[%d]=%d, ", i, dym_list.mem[i].block);
    }
  printf("\n");
}

int main(void) {
  dym_init();


  dym_Type *p;
  dym_Type *arr[16];
  uint32_t i=0;

  print_list();
  for(i=0;i < 16;i ++)
    {
      //allocating
      p = dym_alloc();
      if (p == NULL)
        {
          printf("error\n");
        }
      else {
        arr[i]=p;
        *p = i+10;
        printf("*p=%d\n", *p);
      }
      print_list();

      printf("---------------------------------------------------\n");
    }
  printf("\n\n");


  print_list();
  for(i=0;i < 16;i ++)
    {
      //deleting and allocating again
      printf("deleting\n");
      dym_delete(arr[i]);
      print_list();
      printf("---------------------------------------------------\n");
    }
  printf("\n\n");


  for(i=0;i < 16;i ++)
    {
      //allocating
      p = dym_alloc();
      if (p == NULL)
        {
          printf("error\n");
        }
      else {
        arr[i]=p;
        *p = i+100;
        printf("*p=%d\n", *p);
      }
      print_list();

      printf("---------------------------------------------------\n");
    }
  printf("\n\n");




  return 0;
}

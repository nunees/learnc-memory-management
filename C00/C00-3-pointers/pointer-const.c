#include <stdio.h>
#include <stdlib.h>

/**
 * const int *p (pointer cannot change)
 * int *const p (value cannot change through pointer)
 */

int main()
{
  int number = 42;

  // Pointer to const
  // p pointer to int and should not modify through p (readonly)
  const int *p = &number;
  // This is allowed
  //printf("%d\n", *p);
  // Not allowed (P is read only)
  //*p = 20;
  // However, the pointer itself can change:
  int y = 30;
  p = &y;
  printf("%d\n", *p);

  // x cannot point somewhere else
  int *const x = &y;
  // we can modify
  *x = 20;
  printf("%d\n", *x);
  // this is not allowed
  //x = &p; 

  return 0;
}
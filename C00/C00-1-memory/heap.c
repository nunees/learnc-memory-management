#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *ptr = malloc(sizeof(int));
  *ptr = 43;

  printf("Value of pointer: %d\n", *ptr);

  free(ptr);
  ptr = NULL;

  printf("Value of pointer: %d\n", *ptr);

  return 0;
}
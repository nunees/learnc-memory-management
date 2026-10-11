#include <stdio.h>

int main(int argc, char const *argv[])
{
  int *p = malloc(sizeof(int));
  int *q = malloc(sizeof(int));

  // hold the address of different object types
  void *ptr;

  *p = 42;
  *q = 44;

  // This works
  ptr = &p;
  ptr = &q;

  // This wont work because c doesnt know the pointer type
  // printf("Value of p: %d", *ptr);

  // This will work, we cast the type
  printf("Value of p: %d", *(int *)ptr);

  return 0;
}

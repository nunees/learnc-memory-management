#include <stdlib.h>
#include <stdio.h>

/**
 * They're heavily used for:
    callbacks
    event systems
    drivers
    operating systems
    state machines
    sorting
    plugin systems
    virtual dispatch
    embedded systems
 */

int add(int a, int b){
  return a + b;
}

int (*operation)(int, int) = add;


int main(int argc, char **argv)
{
   for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

  int result = operation(10, 20);
  printf("\n\nThe result is: %d\n", result);

  return 0;
}
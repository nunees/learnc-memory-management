#include <stdio.h>

//Always use volatile for hardware registers.
// 40

int main(int argc, char const *argv[])
{
  
  volatile unsigned int *status = 
    (volatile unsigned int *)0x40000000;

    unsigned int value = *status;

  return 0;
}

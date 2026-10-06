#include <stdio.h>
#include <stdlib.h>

// assign 38 - 39

int main()
{
  // You can convert between pointer types:
  int x = 0x12345678;
  unsigned char *bytes = (unsigned char *)&x;

  // Now you can inspect the individual bytes of the integer.
  for(size_t i=0; i < sizeof(x); i++){
    printf("%02x\n", bytes[i]);
  }

  return 0;
}
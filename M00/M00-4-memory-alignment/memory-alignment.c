#include <stdio.h>
#include <stddef.h>

struct Example
{
  int x;
  char c;
  char d;
};

int main()
{
  printf("char alignment:   %zu\n", _Alignof(char));
  printf("int alignment:    %zu\n", _Alignof(int));
  printf("double alignment: %zu\n\n", _Alignof(double));

  printf("Size: %zu\n", sizeof(struct Example));
  printf("Alignment: %zu\n", _Alignof(struct Example));

  printf("c offset: %zu\n",
         offsetof(struct Example, c));
  printf("x offset: %zu\n",
         offsetof(struct Example, x));
  printf("d offset: %zu\n",
         offsetof(struct Example, d));

  return 0;
}

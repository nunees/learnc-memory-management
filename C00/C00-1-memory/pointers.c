#include <stdio.h>

int main()
{
  int age = 25;

  printf("Value of age: %d\n", age);
  printf("Address of age: %p\n", (void *)&age);

  //Lets change the age value through pointer

  int *ptr = &age;
  printf("Value of age through pointer: %d\n", *ptr);
  *ptr = 33;
  printf("New value of age: %d\n", age);

  return 0;
}
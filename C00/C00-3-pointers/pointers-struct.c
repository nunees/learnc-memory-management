#include <stdio.h>
#include <stdlib.h>

struct Person
{
  int age;
  double salary;
};


int main() 
{
  struct Person *person = malloc(sizeof(*person));
  person->age = 33;
  person->salary = 5000.0;

  printf("Person has %d years\n", person->age);
  printf("Person receive R$%f\n", person->salary);

  free(person);
  

  return 0;
}
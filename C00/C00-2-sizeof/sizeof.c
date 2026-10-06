#include <stdio.h>
#include <stdlib.h>

struct Person
{
  int age;
  double salary;
};

int main()
{

  size_t array_size = 10;
  size_t size_t_alloc = array_size * sizeof(int);
  size_t *numbers = malloc(size_t_alloc);
  size_t numbers_count = size_t_alloc / sizeof(numbers[0]);

  printf("Size of one integer: %zu bytes\n", sizeof(size_t_alloc));
  printf("Allocated Memory: %zu bytes\n", 5*sizeof(*numbers));
  printf("Number of elements: %zu\n\n", numbers_count);

  for (int i = 0; i < array_size; i++)
  {
    numbers[i] = i;
  }

  int *ptr = numbers;
  size_t ptr_size = sizeof(ptr);
  size_t ptr_size_numbers = ptr_size/sizeof(ptr[0]);
  printf("Size of pointer: %zu\n", ptr_size);
  printf("Size of the pointer array: %zu\n\n", ptr_size_numbers);

  // compiler can add padding for alignment.
  printf("Size of struct: %zu", sizeof(struct Person));

  printf("\n");
  free(numbers);
  return 0;

  return 0;
}
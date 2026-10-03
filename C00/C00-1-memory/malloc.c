#include <stdio.h>
#include <stdlib.h>

int main()
{

  int ARRAY_SIZE = 5;
  int size_t_alloc = ARRAY_SIZE * sizeof(int);
  int *numbers = malloc(size_t_alloc);
  size_t numbers_count = size_t_alloc / sizeof(numbers[0]);

  if (numbers == NULL)
  {
    return 1;
  }

  printf("Size of one integer: %zu bytes\n", sizeof(size_t_alloc));
  printf("Allocated Memory: %zu bytes\n", 5*sizeof(*numbers));
  // We can calculate the number of elements with
  printf("Number of elements: %zu\n", numbers_count);

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    numbers[i] = i;
  }

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    printf("%d\t", numbers[i]);
  }

  printf("\n");
  free(numbers);
  return 0;
}
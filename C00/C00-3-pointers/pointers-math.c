#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/** 
 * p++ - Move the pointer
 * *(p + 1) - Increment the value
*/

void allocate(int **ptr){
  *ptr = malloc(sizeof(int));
}

int main(){
  int array_size = 10;
  int array_alloc_size = array_size * sizeof(int);
  int *numbers = malloc(array_alloc_size);
  int numbers_count = array_alloc_size / sizeof(numbers[0]);

  printf("Array initialized with %d elements\n", numbers_count);

  // Initialize the array
  for(int i=0; i < array_size; i++){
    // This assignment is the same as: numbers[i] = i * 20
    *(numbers + i) = i * 20;
    printf("Address %p has value %d\n", numbers+i, numbers[i]);
  }
  printf("\n\n");
  printf("Fetching third element: %d\n ", *(numbers + 2));

  //Subtracting arrays
  int *a = &numbers[2];
  int *b = &numbers[6];

  // The return type of pointer subtract will be ptrdiff_t
  ptrdiff_t calc_result = b - a;
  printf("Subtract index 6 and 2: %ld\n\n", calc_result);

  // Pointer to a pointer
  int **number_copy_ptr = &numbers;
  printf("Value of second element is from pointer is: %d\n\n", (*number_copy_ptr)[2]);

  // Passing pointer to functions
  int *p = NULL;
  allocate(&p);
  *p = 42;
  printf("The pointer now has value: %d\n", *p);
  free(p);

  return 0;
}
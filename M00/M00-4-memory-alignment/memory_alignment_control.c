#include <stdio.h>
#include <stdalign.h>

_Alignas(16) int number = 42;
// or C11
// alignas(16) int number = 42;

int main(void)
{
    printf("Address: %p\n", (void *)&number);
    printf("Alignment requirement: %zu\n",
           _Alignof(int));

    return 0;
}
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int x = 42;
    uintptr_t address = (uintptr_t)&x;

    if (address % _Alignof(int) == 0) {
        printf("Address is aligned for int\n");
    } else {
        printf("Address is not aligned for int\n");
    }

    return 0;
}

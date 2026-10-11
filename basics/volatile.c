#include <stdio.h>

int main(int argc, char const *argv[])
{
  volatile int ready = 0;

    printf("ready = %d\n", ready);

    ready = 1;  // Simulate an external update

    printf("ready = %d\n", ready);

    return 0;
}

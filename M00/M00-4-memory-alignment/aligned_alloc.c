#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t alignment = 64;
    size_t size = 128;

    void *ptr = aligned_alloc(alignment, size);

    if (ptr == NULL) {
        perror("aligned_alloc");
        return 1;
    }

    printf("Address: %p\n", ptr);

    free(ptr);
    return 0;
}
# Memory address alignment in C

Memory alignment is a fundamental C programming concept. It explains why variables are stored at certain memory addresses, how structs use padding, and how to write efficient and portable low-level code.

## 1. What is memory alignment?
Every variable in a C program occupies memory at some address.

For example:

```c
char c = 'A';
int  x = 42;
```
Memory alignment means placing an object at an address that satisfies its alignment requirement.

For example, if an integer requires 4-byte alignment, its address must be a multiple of 4:

- `0x1000` — aligned to 4 bytes.
- `0x1004` — aligned to 4 bytes.
- `0x1008` — aligned to 4 bytes.
- `0x1002` — not aligned to 4 bytes.

In general, for a power-of-two alignment `A`, an address `P` is aligned when:

```
P mod A = 0
```

Here, P is the numeric address and A is the required alignment in bytes.

Important: The required alignment depends on the type and platform. A common platform might require 4-byte alignment for int and 8-byte alignment for double, but these are not universal rules.

## 2. Why does alignment matter?
There are three main reasons.

- Performance: Some processors handle aligned memory accesses more efficiently.
- Correctness: Certain processors or operations may not support unaligned accesses in the way you expect.
- Language rules: In C, accessing an object through a pointer that is not correctly aligned for its type can result in undefined behavior.

Alignment also matters in operating systems, embedded systems, device drivers, networking, and systems programming.

## 3. How to check alignment in C
C11 introduced the `_Alignof` operator, which reports a type's alignment requirement.

```c
#include <stdio.h>
#include <stddef.h>

int main(void)
{
    printf("char alignment:   %zu\n", _Alignof(char));
    printf("int alignment:    %zu\n", _Alignof(int));
    printf("double alignment: %zu\n", _Alignof(double));

    return 0;
}
```
Compile with a C11-compatible compiler:

```shell
gcc -std=c11 -Wall -Wextra alignment.c -o alignment
./alignment
```

The output might look like this:

```text
char alignment:   1
int alignment:    4
double alignment: 8
```

Your results may differ by platform and compiler.

You can also use sizeof to compare an object's size with its alignment:

- `sizeof(int)` tells you how many bytes an int occupies.
- `_Alignof(int)` tells you the alignment requirement of int.

These are different concepts. An object can have a size of 4 bytes and an alignment requirement of 4 bytes, but that relationship is not guaranteed for every type.

## 4. How alignment affects structs (very important)
This is where alignment becomes especially useful.

Consider this structure:

```c
struct Example {
    char c;
    int x;
    char d;
};
```

You might expect its size to be:

```
char: 1 byte
int: 4 bytes
char: 1 byte
Total: 6 bytes.
```

But on a typical system, sizeof(struct Example) may be 12 bytes because the compiler inserts padding.

Why does this happen?

1. The char member occupies one byte.
2. The compiler adds padding so that x can begin at an appropriately aligned address.
3. The int occupies its bytes.
4. The compiler adds trailing padding so that consecutive elements in an array of this structure can satisfy the structure's alignment requirement.

You can inspect the result yourself:

```c
#include <stdio.h>
#include <stddef.h>

struct Example {
    char c;
    int x;
    char d;
};

int main(void)
{
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
```

`offsetof` is declared in `<stddef.h>` and reports the byte offset of a member from the beginning of its structure.

**Can you reduce the padding?**

Often, you can change the member order:

```c
struct Better {
    int x;
    char c;
    char d;
};
```

On a typical system where int has size and alignment of 4 bytes, this structure may occupy 8 bytes rather than 12.

This technique is useful when you have arrays containing millions of structures.

However, don't reorder structure members blindly when the structure is part of a public API, binary file format, hardware interface, or network protocol. Its layout may need to remain compatible with an external specification.

## 5. How to control alignment

Sometimes, you need a variable to have a specific alignment.

Using _Alignas in C11

```c
#include <stdio.h>
#include <stdalign.h>

_Alignas(16) int number = 42;

int main(void)
{
    printf("Address: %p\n", (void *)&number);
    printf("Alignment requirement: %zu\n",
           _Alignof(int));

    return 0;
}
```

`_Alignas(16)` requests that number be aligned to at least 16 bytes. This does not change the size of the int itself.

You can also use the C11 spelling alignas from `<stdalign.h>`:

```c
alignas(16) int number = 42;
```

This requests a stronger alignment than an ordinary int might need.

The requested alignment must be supported by the implementation; an unsupported extended alignment can result in a diagnostic.

Using `aligned_alloc`
C11 also provides `aligned_alloc` for dynamically allocated, specially aligned memory.

```c
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
```

Here, size is a multiple of alignment, as required by C11 `aligned_alloc`.

This can be useful for SIMD processing, cache-conscious data structures, and some low-level programming tasks. You generally should not use it unless you have a specific reason to require stronger alignment.

## 6. How to check whether an address is aligned
You can examine an address using uintptr_t when your implementation provides that optional integer type.

```c
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
```

This illustrates checking an address numerically on platforms that support `uintptr_t`. For an ordinary, correctly declared int object, the implementation already ensures the required alignment.

Do not take an arbitrary byte address, cast it to int *, and dereference it just because the address looks plausible. The pointer must satisfy alignment requirements, and the access must also obey C's object and aliasing rules.

For example, this is not a safe general way to read an integer from a byte buffer:

```c
unsigned char buffer[8] = {0};

/* Potentially invalid: alignment and other rules may be violated. */
int value = *(int *)(buffer + 1);
```

A safer way to copy an integer's representation into a properly aligned object is:

```c
#include <string.h>

unsigned char buffer[sizeof(int)] = {0};
int value;

memcpy(&value, buffer, sizeof value);
```

This avoids an unaligned typed dereference. If the bytes represent a value from a file or network packet, you must also account for byte order, the data format, and whether the representation is valid for int.


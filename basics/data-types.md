# Data Types

### 1. Basic C data types

**Integer types**

Integer types store whole numbers.

| Type | Example | Typical Size |
| -------- | -------- | -------- |
| char | 'A' | 1 byte |
| short |	100 |	At least 2 bytes |
| int |	42 |	At least 2 bytes, commonly 4 |
| long |	100000L |	At least 4 bytes |
| long | long 9000000000LL |	At least 8 bytes |

The actual sizes depend on the platform and compiler. You can check them using sizeof.

```c
#include <stdio.h>

int main(void)
{
    printf("char: %zu bytes\n", sizeof(char));
    printf("short: %zu bytes\n", sizeof(short));
    printf("int: %zu bytes\n", sizeof(int));
    printf("long: %zu bytes\n", sizeof(long));
    printf("long long: %zu bytes\n", sizeof(long long));

    return 0;
}
```

**Signed and unsigned integers**

You can use signed or unsigned to control whether an integer type represents negative values.

```c
int temperature = -10;
unsigned int age = 20;
signed char difference = -5;
unsigned char byte = 255;
```

- signed: represents negative and positive values.
- unsigned: represents zero and positive values, with a larger nonnegative range for the same number of bits.
An unsigned char is commonly useful for working with raw bytes.

**Floating-point types**

These store numbers with fractional parts.

| Type | Example | Typical precision |
| -------- | -------- | -------- |
| float |	3.14f | 	About 6–7 decimal digits |
| double |	3.1415926535 | 	About 15–16 decimal digits |
| long double |	3.14L | 	Implementation-dependent |

```c
float voltage = 3.3f;
double price = 19.99;
long double measurement = 123.456L;
```

Use double for many general-purpose calculations when you need floating-point values.

**Boolean type**

C99 introduced _Bool. You can use bool, true, and false by including `<stdbool.h>`.

```c
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool is_connected = true;

    if (is_connected) {
        printf("Connected!\n");
    }

    return 0;
}
```

**void type**

void indicates the absence of a value or a specific type.
For example, a function that returns nothing:

```c
void say_hello(void)
{
    printf("Hello!\n");
}
````

It also appears in generic pointers:

```c
void *ptr;
```

A void * can hold the address of an object of any type, but you generally need to convert it to an appropriate pointer type before dereferencing it.

## Fixed-width integer types

When working with embedded systems, communication protocols, binary files, or memory-mapped hardware, predictable integer widths are often important.

Include <stdint.h>:

```c
#include <stdint.h>

uint8_t byte = 255;
uint16_t sensor_value = 1024;
uint32_t address = 100000;
int32_t temperature = -20;
```

| Type |	Meaning |
| -------- | -------- |
| uint8_t |	Unsigned integer with exactly 8 bits |
| uint16_t |	Unsigned integer with exactly 16 bits |
| uint32_t |	Unsigned integer with exactly 32 bits |
| int32_t |	Signed integer with exactly 32 bits |

These exact-width types are provided when the implementation supports the specified width.
For example, an 8-bit byte value can represent values from 0 to 255.
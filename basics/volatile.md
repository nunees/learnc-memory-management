# Volatile Keyword

In C, the volatile keyword tells the compiler that a variable's value may change unexpectedly outside the normal flow of the program. Therefore, the compiler must not assume that the value remains unchanged between accesses.

It is especially useful when working with hardware registers, embedded systems, interrupts, and memory-mapped I/O.

## 1. Why do we need volatile?

Consider this example:

```c
int ready = 0;

while (ready == 0) {
    // Wait for ready to change
}
```
Imagine another part of the system changes ready to 1, such as an interrupt handler or hardware-related code.

An optimizing compiler might assume that ready never changes inside this loop because the loop itself doesn't modify it. It could optimize the code into an infinite loop.

Using volatile tells the compiler to access the variable's value each time it is evaluated:

```c
volatile int ready = 0;

while (ready == 0) {
    // Read ready again on each iteration
}
```

Now the compiler must preserve the required volatile accesses.

Important: volatile does not make a variable thread-safe, atomic, or automatically synchronized.

## 2. How does volatile work?

Compare these declarations:

```c
int a = 10;
volatile int b = 10;
```

For a normal variable, the compiler can reuse a previously loaded value when it determines that doing so preserves program behavior.

For a volatile variable, each required read or write must be treated as an observable access according to C's volatile rules.

## 3. Using volatile with hardware registers
This is one of its most important applications in embedded C.

Imagine you're programming an Arduino or ESP32 and need to read a hardware status register.

```c
#define STATUS_REGISTER (*(volatile unsigned int *)0x40000000)

int main(void)
{
    while ((STATUS_REGISTER & 1u) == 0) {
        // Wait for the hardware status bit
    }

    // Continue when the bit becomes 1
    return 0;
}
```

Here's what happens:
1. 0x40000000 represents a hypothetical hardware register address.
2. The pointer is declared as a pointer to volatile unsigned int.
3. Dereferencing the pointer reads the register.
4. The compiler must preserve the required volatile reads instead of assuming the register never changes.

This address is only an example. Real register addresses and access widths must come from the microcontroller's technical documentation.

Why is this important?
Hardware can change a register without your C code assigning a new value to it.
For example, a peripheral might update a status register when:
- A UART receives a byte.
- A timer reaches a particular value.
- An ADC conversion completes.
- A communication controller detects an event.

Without the appropriate volatile qualification, compiler optimizations can make register access incorrect.

## 4. Using volatile with interrupts
Suppose an interrupt handler sets a flag when a hardware event occurs.

```c
#include <stdbool.h>

volatile bool data_received = false;

void uart_interrupt_handler(void)
{
    data_received = true;
}

int main(void)
{
    while (!data_received) {
        // Wait for the interrupt
    }

    // Process the received data
    return 0;
}
```

The `volatile` qualifier ensures that the main loop doesn't simply reuse an old value of `data_received`.

However, actual interrupt-handler declarations and interrupt behavior depend on the platform and compiler.

Also, `volatile` doesn't guarantee that a multi-step operation such as `counter++` is atomic. If an interrupt and the main program both modify a variable, you may need additional synchronization or a platform-specific critical section.

## 5. volatile with pointers
Since you're learning pointers and memory-mapped I/O, it's important to understand where volatile is placed.
There are three useful variations:

**A. Pointer to volatile data**
```c
volatile int *ptr;
```

Equivalent to:
```c
int volatile *ptr;
```

You can change the pointer, but accesses through it treat the pointed-to integer as volatile.

```c
int x = 10;
volatile int *ptr = &x;

int value = *ptr;  // Volatile read
*ptr = 20;         // Volatile write
```


**B. Volatile pointer**
```c
int * volatile ptr;
```

The pointer itself is volatile, but the integer it points to isn't necessarily volatile.
```c
int x = 10;
int y = 20;

int * volatile ptr = &x;

ptr = &y;   // Volatile pointer assignment
*ptr = 30;  // Ordinary access through the pointer
```

**C. Volatile pointer to volatile data**
```c
volatile int * volatile ptr;
```

Both the pointer and the pointed-to integer are volatile.

|Declaration | Pointer can change? | Pointed-to value is volatile? |
|------------|---------------------|-------------------------------|
|int *ptr |	Yes |	No |
|volatile int *ptr |	Yes |	Yes |
|int * volatile ptr |	Volatile access to pointer |	No |
|volatile int * volatile ptr |	Volatile access to pointer |	Yes |

## 6. volatile versus const

These keywords serve different purposes.

```c
const int max_speed = 100;
volatile int hardware_status = 0;
```

- `const`: You cannot modify the object through this identifier.
- `volatile`: Accesses must respect the special `volatile` rules because the value may change unexpectedly.

They can also be combined:

```c
const volatile unsigned int *status_register;
```

This means you can read the register through this pointer, but you cannot modify its value through this pointer. The hardware may still change it.

This combination is common for read-only hardware status registers.

## 7. When should you use volatile?
Use it when the implementation requires volatile accesses, particularly for:

- Memory-mapped hardware registers.
- Variables shared between an interrupt handler and ordinary code.
- Certain hardware polling loops.
- Other platform-specific situations where values can change outside ordinary program execution.

Do not use it as a general solution for:

- Making multithreaded code safe.
- Preventing all compiler optimizations.
- Protecting shared data from race conditions.
- Replacing mutexes or atomic operations.
- Preventing memory leaks.
For example, if you need synchronization between C threads, investigate the C11 `<stdatomic.h>` library and atomic types such as atomic_int.

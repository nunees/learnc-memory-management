# Memory-Mapped I/O

Pointers are the primary way C interacts with memory-mapped I/O (MMIO). In MMIO, hardware registers appear at specific memory addresses. Instead of calling functions, your program reads from or writes to those addresses.

What is Memory-Mapped I/O?
Suppose a microcontroller has an LED control register at address:

```
0x40021018
```

Writing a 1 to a specific bit might turn on the LED.
From C's perspective, this address looks like ordinary memory.

**Basic Example**
```c
#define LED_REGISTER ((volatile unsigned int *)0x40021018)

int main() {
    *LED_REGISTER = 1;
    return 0;
}
```

Explanation:
```
LED_REGISTER
```
is a pointer to address 0x40021018.
```
*LED_REGISTER = 1;
```
writes the value 1 to that hardware register.

**Why volatile?**

Always use volatile for hardware registers.
Without it:
```c
*LED_REGISTER = 1;
```
the compiler might optimize away reads or writes because it assumes memory doesn't change unexpectedly.
With:
```c
volatile unsigned int *
```
the compiler is forced to perform every access exactly as written.

**Reading a Register**

Suppose a button status register is at:
```
0x4002101C
```

```c
#define BUTTON_REGISTER ((volatile unsigned int *)0x4002101C)

int state = *BUTTON_REGISTER;
```

The CPU loads the value directly from the hardware register.

**Bit Manipulation**

Registers often contain multiple control bits.
Example:
```
Bit 0 = LED ON/OFF
Bit 1 = LED BLINK
Bit 2 = ERROR FLAG
```

Turn on the LED:
```c
*LED_REGISTER |= (1 << 0);
```

Turn off the LED:
```c
*LED_REGISTER &= ~(1 << 0);
```

Toggle the LED:
```c
*LED_REGISTER ^= (1 << 0);
```

**Using a Struct**
Many embedded projects map registers into a struct.
Suppose a peripheral has:
```
0x40021000 CONTROL
0x40021004 STATUS
0x40021008 DATA
```

You can define:
```c
typedef struct {
    volatile unsigned int CONTROL;
    volatile unsigned int STATUS;
    volatile unsigned int DATA;
} Peripheral;
```

Then:
```c
#define PERIPH ((Peripheral *)0x40021000)
```

Usage:
```
PERIPH->CONTROL = 1;
unsigned int status = PERIPH->STATUS;
PERIPH->DATA = 42;
```

This is much cleaner than raw addresses.


**ESP32 Example Concept**

ESP32 peripherals are controlled through MMIO registers.
A simplified example:
```c
volatile uint32_t *gpio_out =
    (volatile uint32_t *)0x3FF44004;

*gpio_out |= (1 << 2);
```

This would manipulate a GPIO register directly.
In practice, ESP-IDF provides macros and drivers so you rarely need raw addresses.

**What the CPU Does**

When the CPU executes:

```c
*LED_REGISTER = 1;
```

it roughly performs:
```asm
MOV R0, #1
MOV R1, #0x40021018
STR R0, [R1]
```

STR stores the value in the memory location, which is actually a hardware register.


**Common Pitfalls**

**1. Forgetting volatile**
Bad:
```c
unsigned int *reg = (unsigned int *)0x40021018;
```

Good:
```c
volatile unsigned int *reg =
    (volatile unsigned int *)0x40021018;
```

**2. Wrong register size**
If the register is 32-bit:
```c
volatile uint32_t *reg;
```

not:
```c
volatile uint8_t *reg;
```

unless the hardware documentation explicitly says so.

**3. Writing reserved bits**

Many registers contain reserved bits that must not be modified.
Instead of:
```c
*reg = 0xFFFFFFFF;
```

use masks:
```c
*reg |= (1 << 5);
```

Relating This to Pointers
If you've learned:
```c
int x = 10;
int *p = &x;
*p = 20;
```

then MMIO is conceptually the same thing:
```c
volatile uint32_t *reg =
    (volatile uint32_t *)0x40021018;

*reg = 20;
```

The difference is that `0x40021018` is not RAM holding a variable—it is a hardware register connected to a peripheral. Writing to it may turn on a GPIO, start a timer, transmit a UART byte, or trigger some other hardware action.


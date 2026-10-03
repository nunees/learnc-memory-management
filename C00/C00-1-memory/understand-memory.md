# Understanding Memory (Basics)

Think of a C program as having different areas of memory with different purposes:

```
                 PROCESS MEMORY

        Higher addresses
        ┌─────────────────┐
        │      Stack      │
        │                 │
        │ local variables │
        │ function calls  │
        ├─────────────────┤
        │       ↓         │
        │                 │
        │       ↑         │
        ├─────────────────┤
        │       Heap      │
        │                 │
        │ malloc / free   │
        ├─────────────────┤
        │ Global / Static │
        ├─────────────────┤
        │      Code       │
        └─────────────────┘
        Lower addresses
```
We'll focus first on stack, heap, pointers, allocation, and deallocation.

## 1. Variables live somewhere in memory

Consider:
```c
#include <stdio.h>

int main(void)
{
    int age = 25;

    printf("%d\n", age);

    return 0;
}
```
When you write:
```c
int age = 25;
```
the computer needs somewhere to store 25.

Conceptually:
```
Memory

Address       Value
0x7ffd...     25
              ↑
             age
```

The variable age is associated with a memory location.

You can see that location using &

```c
printf("%p\n", (void *)&age);
```

For example:

```c
0x7ffc12345678
```

# 2. & means "address of"

This is extremely important.
```c
int age = 25;
```
There are two different things:
```
age
 ↓
25

&age
 ↓
address where 25 is stored
```
Example:
```c
printf("Value: %d\n", age);
printf("Address: %p\n", (void *)&age);
```
You might get:
```
Value: 25
Address: 0x7ffd1234
```
So:
```
age
```
means:
```
Give me the value.
```
while:
```
&age
```
means:
```
Give me the address.
```

# 3. Pointers

A pointer is a variable that stores an address.

```c
int age = 25;

int *ptr = &age;
```
Think:
```
age
┌─────────┐
│   25    │
└─────────┘
    ↑
    │
    │ address
    │
ptr
┌─────────┐
│ 0x1234  │
└─────────┘
```

`ptr` doesn't contain 25.

It contains the `address of` age.

# 4. * means "follow the address"

Given:
```c
int age = 25;
int *ptr = &age;
```
You can access age through ptr:
```c
printf("%d\n", *ptr);
```
Output:
```
25
```
So:
```
ptr
 ↓
address of age
 ↓
*ptr
 ↓
25
```
This operation is called `dereferencing`.

# 5. You can modify memory through a pointer

```c
int age = 25;

int *ptr = &age;

*ptr = 30;

printf("%d\n", age);
```

Output:
```
30
```
Why?

Initially:
```
age
┌────┐
│ 25 │
└────┘
```
Then:
```c
*ptr = 30;
```
means:
```
Go to the memory address stored in ptr and put 30 there.
```
Result:
```
age
┌────┐
│ 30 │
└────┘
```
This concept is fundamental to low-level programming.

# 6. Stack memory

Consider:

```c
int main(void)
{
    int x = 10;
    int y = 20;

    return 0;
}
```

x and y are local variables.

They normally live in the stack.

Conceptually:
```
Stack
┌──────────────┐
│      y       │
│      20      │
├──────────────┤
│      x       │
│      10      │
└──────────────┘
```
`The stack is automatically managed.`

When main() finishes, those local variables cease to exist.

You don't need:
```c
free(x);
```
That's because they weren't allocated with `malloc()`.

# 7. Functions create stack frames

Look at this:
```c
void calculate(void)
{
    int x = 10;
}

int main(void)
{
    calculate();

    return 0;
}
```
When `main()` calls `calculate()`:

```
main()
   ↓
calculate()
```

The CPU creates a stack frame for calculate().

Conceptually:
```
Stack

┌──────────────────┐
│ calculate()      │
│ x = 10           │
├──────────────────┤
│ main()           │
│ variables        │
└──────────────────┘
```
When calculate() returns:
```
calculate()
   ↓
returns
```
its stack frame disappears.

This is one of the most important concepts for understanding CPU execution.

# 8. What is the heap?

The heap is memory that you request manually while your program is running.

For example:

```c
int *ptr = malloc(sizeof(int));
```

You're essentially saying:

Give me enough memory to store an int.

Then:

```c
*ptr = 42;
```

Now:

```
Stack                     Heap

┌─────────────┐           ┌─────────────┐
│ ptr         │──────────>│     42      │
│ 0x123456    │           └─────────────┘
└─────────────┘
```

Notice something important:

The pointer ptr itself can be on the stack, while the memory it points to is on the heap.

*Note: include stdlib.h to use malloc*

# 9. malloc()

Let's look at a complete example:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *ptr = malloc(sizeof(int));

    *ptr = 42;

    printf("%d\n", *ptr);

    free(ptr);

    return 0;
}
```

Let's break it down.

Step 1
```c
int *ptr;
```

Create a pointer.
```
Stack

ptr
┌──────────┐
│ ???      │
└──────────┘
```
It doesn't point to valid allocated memory yet.

Step 2
```c
ptr = malloc(sizeof(int));
```
Now memory is allocated:
```
Stack                     Heap

ptr
┌──────────┐              ┌──────────┐
│ 0x5000   │─────────────>│    ???   │
└──────────┘              └──────────┘
```
Step 3
```c
*ptr = 42;
```
Now:
```
Stack                     Heap

ptr
┌──────────┐              ┌──────────┐
│ 0x5000   │─────────────>│    42    │
└──────────┘              └──────────┘
```
# 10. free()

When you call:
```c
free(ptr);
```
you're telling the allocator:

I'm finished with this memory. It can be used again.

Conceptually:

Before:
```
ptr ──────> [ 42 ]
```
After free:
```
ptr ──────> [ invalid ]
```
Important:

`free()` does not necessarily erase the bytes.

It tells the memory allocator that the region is no longer allocated to your program.

# 11. A very important bug

Don't do this:
```c
int *ptr = malloc(sizeof(int));

*ptr = 42;

free(ptr);

printf("%d\n", *ptr);
```
After:
```c
free(ptr);
```
you no longer own that memory.

Using it afterward is called a `use-after-free`.

The behavior is undefined.

A common habit is:
```c
free(ptr);
ptr = NULL;
```
Then:
```c
if (ptr != NULL)
{
    // safe to use
}
```

# 12. Allocating arrays

You can allocate multiple elements:
```c
int *numbers = malloc(5 * sizeof(int));
```
Now you've requested space for five integers:
```
Heap

┌────┬────┬────┬────┬────┐
│  ? │  ? │  ? │  ? │  ? │
└────┴────┴────┴────┴────┘
  0    1    2    3    4
```
You can use normal array syntax:
```
numbers[0] = 10;
numbers[1] = 20;
numbers[2] = 30;
numbers[3] = 40;
numbers[4] = 50;
```
Then:
```
free(numbers);
```

# 13. Why sizeof() matters

Don't assume an int is always 4 bytes on every possible C implementation.

Instead:
```c
malloc(sizeof(int))
```
For an array:
```c
malloc(5 * sizeof(int))
```
Even better:
```c
int *numbers = malloc(5 * sizeof(*numbers));
```
This automatically uses the correct type size.

# 14. calloc()

Another allocation function is:
```c
calloc()
```
Example:
```c
int *numbers = calloc(5, sizeof(int));
```
This allocates space for five integers and initializes the allocated bytes to zero.

Conceptually:
```
┌────┬────┬────┬────┬────┐
│  0 │  0 │  0 │  0 │  0 │
└────┴────┴────┴────┴────┘
```

# 15. realloc()

Suppose you initially allocate:
```c
int *numbers = malloc(5 * sizeof(int));
```

Later you need 10 integers.

You can use:
```c
numbers = realloc(numbers, 10 * sizeof(int));
```
Conceptually:

Before:
```
[ 1 ][ 2 ][ 3 ][ 4 ][ 5 ]

             ↓ realloc
```
After:
```
[ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ ? ][ ? ][ ? ][ ? ][ ? ]
```
The allocator may be able to expand the block in place, or it may move the data to another location.

That's an important concept for understanding memory management.

# 16. Stack vs Heap

Here's the fundamental comparison:

*Stack <-> Heap*

- Automatically managed	Manually managed
- Local variables	Dynamic allocations
- Function call data	malloc() memory
- Very fast to allocate	More overhead
- Lifetime tied to scope/function	Lifetime controlled by programmer
- Limited size	Usually much larger

Example:
```c
void example(void)
{
    int x = 10;                    // stack

    int *ptr = malloc(sizeof(int)); // heap

    *ptr = 20;

    free(ptr);
}
```
Conceptually:
```
STACK                         HEAP

┌──────────────┐             ┌──────────────┐
│ x = 10       │             │              │
├──────────────┤             │ *ptr = 20    │
│ ptr = 0x5000 │────────────>│              │
└──────────────┘             └──────────────┘
```

# 17. The most important mental model

When learning low-level programming, always distinguish:

The variable
```c
int x = 10;
```
The address
```c
&x
```
The pointer
```c
int *p = &x;
```
The value pointed to
```c
*p
```

```
Think:

       address
          │
          ▼
      ┌─────────┐
      │   10    │
      └─────────┘
          ▲
          │
         *p

p contains the address.
*p accesses the value.
&x obtains the address.
x accesses the value directly.
```
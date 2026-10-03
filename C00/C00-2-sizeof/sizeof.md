# The sizeof Operator

`sizeof` tells you how many bytes a type or object occupies in memory.

```c
#include <stdio.h>

int main(void)
{
    int x = 10;

    printf("%zu\n", sizeof(x));

    return 0;
}
```

On many systems, you'll get:

```
4
```

That means an int occupies 4 bytes on that particular system.

You can also ask about a type:

```c
sizeof(int)
sizeof(char)
sizeof(double)
```

For example:

```c
printf("%zu\n", sizeof(char));
printf("%zu\n", sizeof(int));
printf("%zu\n", sizeof(double));
```
A typical result might be:
```
1
4
8
```

## Why is sizeof important?

The biggest reason is memory allocation.

Suppose you want memory for one int:

```c
int *ptr = malloc(sizeof(int));
```

You're saying:

> Allocate enough memory to store an int.

Instead of assuming that an int is 4 bytes.

This is important because C can run on different architectures where the sizes of types can differ.

## The best way to use sizeof with malloc

You'll often see:
```c
int *ptr = malloc(sizeof(int));
```
But I recommend learning this form:
```c
int *ptr = malloc(sizeof(*ptr));
```
Why?

Because *ptr is an int.
```
ptr
 │
 │ points to
 ▼
 int
```
Therefore:
```c
sizeof(*ptr)
```
means:

How many bytes are needed for the object that ptr points to?

Example:
```c
int *numbers = malloc(5 * sizeof(*numbers));
```
This means:
```
5 × size of an int
```
So if int is 4 bytes:
```
5 × 4 = 20 bytes
```

## sizeof with arrays

This is where sizeof becomes especially useful.
```c
int numbers[5];
```
You can do:
```c
printf("%zu\n", sizeof(numbers));
```
If an int is 4 bytes:
```
20
```
Because:
```
5 integers × 4 bytes = 20 bytes
```
You can calculate the number of elements:
```c
size_t count = sizeof(numbers) / sizeof(numbers[0]);
```
So:
```c
int numbers[5];

size_t count = sizeof(numbers) / sizeof(numbers[0]);

printf("%zu\n", count);
```
Output:
```
5
```
This is a very useful pattern in C:
```c
sizeof(array) / sizeof(array[0])
```

## But there's an important difference with pointers

This is extremely important for your current studies.

Consider:
```c
int numbers[5];
```
Here:
```c
sizeof(numbers)
```
gives the size of the entire array.

For example:
```
numbers
┌────┬────┬────┬────┬────┐
│  0 │  1 │  2 │  3 │  4 │
└────┴────┴────┴────┴────┘
          20 bytes
```
But:
```c
int *numbers = malloc(5 * sizeof(*numbers));
```
Now numbers is a pointer, not an array.

Therefore:
```c
sizeof(numbers)
```
gives you the size of the pointer.

For example, on a typical 64-bit system:
```c
sizeof(numbers) → 8
```
It does not give you the 20 bytes allocated by malloc.

This is a very common beginner mistake.

## sizeof(*numbers) is different

Given:
```c
int *numbers = malloc(5 * sizeof(*numbers));
```
These are different:
```c
sizeof(numbers)
```
and:
```c
sizeof(*numbers)
```
Think:
```
numbers
   │
   │ pointer
   ▼
┌────────────┐
│    int     │
└────────────┘
```
So:
```c
sizeof(numbers)
```
→ size of the pointer

while:
```c
sizeof(*numbers)
```
→ size of the int being pointed to

For example:
```
sizeof(numbers)   → 8 bytes
sizeof(*numbers)  → 4 bytes
```
on a typical 64-bit machine.

## `sizeof` does not tell you how much malloc allocated

This is directly related to your previous code.

You had:
```c
int *numbers = malloc(5 * sizeof(int));
```
You might think:
```c
sizeof(numbers)
```
will give:
```
20
```
But it won't.

It might give:
```
8
```
because numbers is a pointer.

The C language does not make the pointer remember:
```
"I point to 5 integers."
```
It only contains an address.

So you should store the number of elements separately:
```c
size_t count = 5;

int *numbers = malloc(count * sizeof(*numbers));
```
Then you know:
```c
count = 5
sizeof(*numbers) = size of one int
```
and therefore:
```c
allocated memory = count × sizeof(*numbers)
```

## sizeof with structs

It's also extremely important when working with structures.
```c
struct Person
{
    int age;
    double salary;
};
```
You can do:
```c
printf("%zu\n", sizeof(struct Person));
```
The result may be larger than simply:
```c
sizeof(int) + sizeof(double)
```
because the compiler can add padding for alignment.

## `sizeof(char)` is always 1

One interesting rule:
```c
sizeof(char)
```
is always:
```
1
```
But be careful:
```
1 byte in C is not necessarily 8 bits.
```
A byte in C is defined as the size of a char.

On modern computers, it is almost universally 8 bits, but the C standard doesn't require that.

## sizeof and pointers

You'll frequently encounter this:

```c
int *p;
double *d;
char *c;
```
The pointed-to types have different sizes:

```c
sizeof(*p) → sizeof(int)
sizeof(*d) → sizeof(double)
sizeof(*c) → sizeof(char)
```

But the pointer itself has its own size:

```c
sizeof(p)
sizeof(d)
sizeof(c)
```

On a typical 64-bit system, these will commonly all be 8 bytes.

That's because they're addresses.


## The four cases you should memorize

```c
int x;
int *p;
int array[5];
```
Then:
```
Expression	    What it means
sizeof(x)	    Size of one int
sizeof(p)	    ize of the pointer
sizeof(*p)	    Size of the int pointed to
sizeof(array)	Size of the entire 5-element array
```
And this:
```c
sizeof(array) / sizeof(array[0])
```
means:
```
Number of elements in the array.
```
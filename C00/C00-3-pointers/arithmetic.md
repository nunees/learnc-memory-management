# 1. What is a pointer?

A pointer is a variable that **stores a memory address**.

Normally:

```c
int age = 25;
```

You have:

```text
age
┌─────────┐
│   25    │
└─────────┘
```

The variable `age` exists somewhere in memory.

Imagine its address is:

```text
0x1000
```

Then conceptually:

```text
Address       Value

0x1000        25
```

You can obtain that address with `&`:

```c
int age = 25;

printf("%p\n", (void *)&age);
```

`&age` means:

> Give me the address of `age`.

---

# 2. Creating a pointer

You create a pointer using `*` in the declaration:

```c
int *ptr;
```

This means:

> `ptr` is a pointer to an `int`.

You can make it point to `age`:

```c
int age = 25;

int *ptr = &age;
```

Now:

```text
STACK

age
┌──────────┐
│    25    │
└──────────┘
    ▲
    │
    │ address
    │
ptr │
┌───┴──────┐
│  0x1000  │
└──────────┘
```

The pointer doesn't contain `25`.

It contains the **address where `25` is stored**.

---

# 3. The three things you must distinguish

Consider:

```c
int x = 42;
int *p = &x;
```

There are three different concepts:

### `x`

The value:

```text
42
```

### `&x`

The address:

```text
0x1000
```

### `p`

The pointer's stored value:

```text
0x1000
```

### `*p`

The value located at that address:

```text
42
```

So:

```text
x       → 42
&x      → address of x
p       → address of x
*p      → 42
```

This is probably the most important pointer relationship to memorize.

---

# 4. Dereferencing

When you use `*` on a pointer:

```c
*p
```

you're saying:

> Go to the address stored in `p` and access the value there.

Example:

```c
int x = 42;
int *p = &x;

printf("%d\n", *p);
```

Output:

```text
42
```

But you can also modify the value:

```c
*p = 100;
```

Now:

```c
printf("%d\n", x);
```

prints:

```text
100
```

Why?

Because:

```text
p ───────► x
           │
           42
```

and:

```c
*p = 100;
```

means:

> Write `100` into the memory pointed to by `p`.

---

# 5. Pointers don't contain the object

This distinction is important.

```c
int x = 42;
int *p = &x;
```

You have two objects:

```text
x
┌─────────┐
│   42    │
└─────────┘

p
┌─────────┐
│ address │
└─────────┘
```

`p` itself occupies memory too.

For example, on a typical 64-bit system:

```text
sizeof(x) → 4
sizeof(p) → 8
```

The exact size of `int` varies by implementation, but pointer size is commonly 8 bytes on modern 64-bit systems.

---

# 6. Pointer types

Pointers have types.

```c
int *p;
char *c;
double *d;
float *f;
```

The type tells C what kind of object the pointer is expected to point to.

For example:

```c
int x = 100;
int *p = &x;
```

C knows that:

```c
*p
```

is an `int`.

This matters enormously for pointer arithmetic.

---

# 7. Why pointer types matter

Suppose:

```c
int *p;
```

and:

```c
char *p;
```

When you do:

```c
p + 1
```

the result depends on the type.

For example, if:

```text
sizeof(int) = 4
```

then:

```c
int *p;
p + 1;
```

moves forward **4 bytes**.

But:

```c
char *p;
p + 1;
```

moves forward **1 byte**.

So pointer arithmetic is based on the size of the pointed-to type.

---

# 8. Pointer arithmetic

Suppose:

```c
int numbers[5] = {10, 20, 30, 40, 50};

int *p = numbers;
```

`numbers` points to the first element:

```text
numbers

0x1000       0x1004       0x1008       0x100C       0x1010
   │            │             │            │             │
   ▼            ▼             ▼            ▼             ▼
┌──────┐     ┌──────┐     ┌──────┐     ┌──────┐     ┌──────┐
│  10  │     │  20  │     │  30  │     │  40  │     │  50  │
└──────┘     └──────┘     └──────┘     └──────┘     └──────┘
```

If `int` is 4 bytes:

```c
p
```

points to:

```text
0x1000
```

Then:

```c
p + 1
```

points to:

```text
0x1004
```

And:

```c
p + 2
```

points to:

```text
0x1008
```

So:

```c
*(p + 0) → 10
*(p + 1) → 20
*(p + 2) → 30
```

---

# 9. Pointer arithmetic isn't normally "add one byte"

This is an extremely important concept.

When you write:

```c
p + 1
```

C effectively performs:

```text
address + 1 × sizeof(*p)
```

So if:

```c
int *p;
sizeof(int) == 4;
```

then:

```c
p + 1
```

means:

```text
address + 4
```

If:

```c
double *p;
sizeof(double) == 8;
```

then:

```c
p + 1
```

means:

```text
address + 8
```

---

# 10. Pointer arithmetic with arrays

This:

```c
numbers[i]
```

is closely related to:

```c
*(numbers + i)
```

For example:

```c
numbers[3]
```

is equivalent to:

```c
*(numbers + 3)
```

This is one of the fundamental relationships in C.

Therefore:

```c
numbers[0]
```

means:

```c
*(numbers + 0)
```

and:

```c
numbers[1]
```

means:

```c
*(numbers + 1)
```

---

# 11. Arrays and pointers are related, but NOT the same

This is a common misconception.

```c
int numbers[5];
```

is an array.

```c
int *p;
```

is a pointer.

They are different types of objects.

However, in many expressions, an array **decays into a pointer to its first element**.

For example:

```c
int numbers[5];

int *p = numbers;
```

is effectively:

```c
int *p = &numbers[0];
```

But:

```c
sizeof(numbers)
```

and:

```c
sizeof(p)
```

are completely different.

```text
sizeof(numbers)
    ↓
size of entire array

sizeof(p)
    ↓
size of pointer
```

---

# 12. Pointer subtraction

You can subtract two pointers when they point into the same array.

Example:

```c
int numbers[10];

int *a = &numbers[2];
int *b = &numbers[7];

printf("%td\n", b - a);
```

Result:

```text
5
```

Because there are five `int` elements between them.

The result type is `ptrdiff_t`.

You can get it from:

```c
#include <stddef.h>
```

---

# 13. Pointer comparison

You can compare pointers:

```c
if (p == q)
{
    printf("Same address\n");
}
```

You can also compare their positions when they refer to the same array:

```c
if (p < q)
{
    ...
}
```

But don't casually compare unrelated pointers with `<` or `>` and assume the result has meaningful array-order semantics.

---

# 14. Pointer increment

You can do:

```c
p++;
```

If:

```c
int *p;
```

then `p++` moves to the next `int`.

Example:

```c
int numbers[] = {10, 20, 30};

int *p = numbers;

printf("%d\n", *p);

p++;

printf("%d\n", *p);

p++;

printf("%d\n", *p);
```

Output:

```text
10
20
30
```

---

# 15. `p++` versus `(*p)++`

These look similar but do completely different things.

### Move the pointer

```c
p++;
```

means:

> Move the pointer to the next element.

### Increment the value

```c
(*p)++;
```

means:

> Increment the value that the pointer points to.

Example:

```c
int x = 10;
int *p = &x;

(*p)++;
```

Now:

```text
x = 11
```

But:

```c
p++;
```

changes the address stored in `p`.

---

# 16. Pointer to pointer

You can have a pointer pointing to another pointer.

```c
int x = 42;

int *p = &x;

int **pp = &p;
```

Think:

```text
pp
 │
 ▼
 p
 │
 ▼
 x
 │
 ▼
42
```

Then:

```c
*pp
```

gives you `p`.

And:

```c
**pp
```

gives you `42`.

Example:

```c
printf("%d\n", **pp);
```

Output:

```text
42
```

---

# 17. Why use pointer-to-pointer?

One major use is modifying a pointer inside a function.

For example:

```c
void allocate(int **ptr)
{
    *ptr = malloc(sizeof(int));
}
```

Then:

```c
int *p = NULL;

allocate(&p);

*p = 42;

free(p);
```

Why `int **`?

Because the function needs to modify the caller's pointer.

---

# 18. Pointers and functions

Pointers allow functions to modify variables belonging to the caller.

Without pointer:

```c
void change(int x)
{
    x = 100;
}
```

This doesn't change the original.

```c
int x = 10;

change(x);

printf("%d\n", x);
```

Still:

```text
10
```

With pointer:

```c
void change(int *x)
{
    *x = 100;
}
```

Call:

```c
int x = 10;

change(&x);
```

Now:

```text
100
```

---

# 19. Pass-by-pointer

This is often described as "pass by reference", but technically C uses **pass-by-value**.

You're passing a copy of the pointer:

```c
void change(int *p)
```

The function receives a copy of the address.

But both pointers point to the same object:

```text
main                 function

p ──────┐
         │
         ▼
       ┌─────┐
       │ 10  │
       └─────┘
         ▲
         │
         └──── q
```

Therefore:

```c
*q = 100;
```

changes the original object.

---

# 20. Pointers and structs

Pointers are extremely common with structures.

```c
struct Person
{
    int age;
    double salary;
};
```

Create one:

```c
struct Person person;
```

Pointer:

```c
struct Person *p = &person;
```

You could access:

```c
(*p).age
```

But C provides a much nicer syntax:

```c
p->age
```

These are equivalent:

```c
p->age
```

and:

```c
(*p).age
```

---

# 21. Dynamic structures

This is very common:

```c
struct Person *person = malloc(sizeof(*person));
```

Then:

```c
person->age = 25;
person->salary = 5000.0;
```

Finally:

```c
free(person);
```

This pattern appears everywhere in systems programming.

---

# 22. `NULL` pointers

A pointer can represent:

> "I currently don't point to anything."

Use:

```c
int *p = NULL;
```

Then:

```c
if (p == NULL)
{
    printf("No object\n");
}
```

Never do:

```c
*p = 42;
```

when `p == NULL`.

That attempts to access memory through a null pointer.

---

# 23. Always initialize pointers

Avoid:

```c
int *p;
```

and immediately using it.

`p` contains an indeterminate value.

Prefer:

```c
int *p = NULL;
```

Then you know:

```text
p
 ↓
NULL
```

until you intentionally make it point somewhere.

---

# 24. `void *`

A `void *` is a generic object pointer.

```c
void *ptr;
```

It can hold the address of different object types:

```c
int x = 10;
double y = 3.14;

void *p;

p = &x;
p = &y;
```

But you cannot directly dereference a `void *`:

```c
*p
```

because C doesn't know what type is there.

You need to convert it to the appropriate pointer type.

For example:

```c
int x = 10;

void *p = &x;

printf("%d\n", *(int *)p);
```

---

# 25. Why `malloc` returns `void *`

This is why you can write:

```c
int *numbers = malloc(5 * sizeof(*numbers));
```

`malloc()` returns a `void *`.

The assignment converts it to `int *` automatically in C.

In C, you generally **should not cast `malloc()`**:

```c
int *p = malloc(sizeof(*p));
```

is preferred over:

```c
int *p = (int *)malloc(sizeof(*p));
```

---

# 26. Pointer to `const`

Now we start getting into more advanced pointer techniques.

Consider:

```c
const int *p;
```

This means:

> `p` points to an `int` that you should not modify through `p`.

For example:

```c
int x = 10;

const int *p = &x;

printf("%d\n", *p);
```

But:

```c
*p = 20;
```

is not allowed.

However, the pointer itself can change:

```c
int y = 30;

p = &y;
```

---

# 27. `int *const`

This is different:

```c
int *const p = &x;
```

Now:

> `p` itself cannot point somewhere else.

But you can modify the object:

```c
*p = 20;
```

This is allowed.

But:

```c
p = &y;
```

is not allowed.

---

# 28. `const int *const`

You can combine them:

```c
const int *const p = &x;
```

Now:

```text
pointer cannot change
        +
value cannot change through pointer
```

This is a useful rule:

Read declarations from the variable outward.

```c
const int *p;
```

`p` is a pointer to const int.

```c
int *const p;
```

`p` is a const pointer to int.

---

# 29. Function pointers

Pointers aren't limited to data.

You can point to a function.

Suppose:

```c
int add(int a, int b)
{
    return a + b;
}
```

You can create:

```c
int (*operation)(int, int) = add;
```

Then:

```c
int result = operation(10, 20);
```

Result:

```text
30
```

This is a **function pointer**.

---

# 30. Why function pointers are useful

They're heavily used for:

* callbacks
* event systems
* drivers
* operating systems
* state machines
* sorting
* plugin systems
* virtual dispatch
* embedded systems

For example:

```c
qsort(array, count, sizeof(int), compare);
```

`qsort()` receives a function pointer telling it how to compare elements.

---

# 31. Function pointer syntax

This:

```c
int (*operation)(int, int);
```

means:

```text
operation
    ↓
pointer
    ↓
function
    ↓
takes two ints
    ↓
returns int
```

Parentheses are important.

Compare:

```c
int *operation(int, int);
```

This means something completely different:

> `operation` is a function returning `int *`.

While:

```c
int (*operation)(int, int);
```

means:

> `operation` is a pointer to a function returning `int`.

---

# 32. Pointers and strings

C strings are fundamentally pointer-based.

```c
char *name = "Felipe";
```

Conceptually:

```text
name
 │
 ▼
┌───┬───┬───┬───┬───┬───┬─────┐
│ F │ e │ l │ i │ p │ e │ \0  │
└───┴───┴───┴───┴───┴───┴─────┘
```

The `\0` marks the end of the string.

You can iterate:

```c
char *p = name;

while (*p != '\0')
{
    printf("%c\n", *p);
    p++;
}
```

---

# 33. Pointer arithmetic is especially useful for strings

For example:

```c
char text[] = "hello";

char *p = text;

while (*p)
{
    printf("%c\n", *p);
    p++;
}
```

Because `char` is one byte, each increment moves to the next character.

---

# 34. Arrays of pointers

You can have an array containing pointers.

For example:

```c
char *names[] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

Conceptually:

```text
names
┌─────────┐
│ pointer ├────► "Alice"
├─────────┤
│ pointer ├────► "Bob"
├─────────┤
│ pointer ├────► "Charlie"
└─────────┘
```

This is commonly used for:

```c
char *argv[]
```

in `main()`.

---

# 35. `argv` and pointers

You've probably seen:

```c
int main(int argc, char **argv)
```

`argv` is effectively an array of pointers to strings.

Conceptually:

```text
argv
 │
 ▼
┌─────────┐
│   *─────┼────► "program"
├─────────┤
│   *─────┼────► "hello"
├─────────┤
│   *─────┼────► "world"
└─────────┘
```

This is a practical example of:

```text
pointer
+
pointer to pointer
+
array
+
string
```

---

# 36. Dynamic 2D arrays

Pointers can be used to create dynamically allocated structures.

One approach:

```c
int **matrix = malloc(rows * sizeof(*matrix));

for (int i = 0; i < rows; i++)
{
    matrix[i] = malloc(cols * sizeof(*matrix[i]));
}
```

Then:

```c
matrix[2][3] = 42;
```

And you release each row:

```c
for (int i = 0; i < rows; i++)
{
    free(matrix[i]);
}

free(matrix);
```

This is an important example because there are **multiple allocations** and therefore multiple ownership relationships.

---

# 37. But contiguous 2D memory can be better

Instead of multiple allocations, you can allocate one block:

```c
int *matrix = malloc(rows * cols * sizeof(*matrix));
```

Then access:

```c
matrix[row * cols + column]
```

For example:

```c
matrix[2 * cols + 3] = 42;
```

This gives you one contiguous block:

```text
┌────┬────┬────┬────┬────┬────┐
│    │    │    │    │    │    │
└────┴────┴────┴────┴────┴────┘
             ↑
        row * cols + col
```

This approach is often better for cache locality.

---

# 38. Pointer casts

You can convert between pointer types:

```c
int x = 0x12345678;

unsigned char *bytes = (unsigned char *)&x;
```

Now you can inspect the individual bytes of the integer.

For example:

```c
for (size_t i = 0; i < sizeof(x); i++)
{
    printf("%02x\n", bytes[i]);
}
```

This is a powerful low-level technique.

It's used when studying:

* binary formats
* serialization
* network packets
* memory representation
* endianness
* device interfaces

But casting pointers incorrectly can create alignment and aliasing problems, so advanced pointer casting needs care.

---

# 39. Accessing raw memory with `unsigned char *`

C gives special treatment to character types for examining object representations.

This makes:

```c
unsigned char *bytes = (unsigned char *)&x;
```

a very useful low-level technique.

For example:

```c
int x = 0x12345678;

unsigned char *p = (unsigned char *)&x;

for (size_t i = 0; i < sizeof(x); i++)
{
    printf("%02X ", p[i]);
}
```

On a little-endian machine, you might see something like:

```text
78 56 34 12
```

This introduces an important architecture concept:

**endianness.**

---

# 40. Pointers and memory-mapped I/O

This is where pointers start becoming directly relevant to hardware.

Operating systems and embedded systems can expose hardware registers at specific memory addresses.

Conceptually:

```c
volatile unsigned int *status =
    (volatile unsigned int *)0x40000000;
```

Then:

```c
unsigned int value = *status;
```

You're telling the compiler:

> Access the object located at this address.

`volatile` is important in hardware contexts because the value may change independently of normal program execution.

**Don't casually dereference arbitrary addresses on your normal desktop.** This technique is for environments where that address is actually mapped and valid.

---

# 41. `volatile` pointers

You may see:

```c
volatile int *p;
```

This means accesses through `p` are volatile.

A classic use is hardware registers:

```c
volatile unsigned int *register_address;
```

Hardware can change the value without your C code explicitly doing so.

Without appropriate `volatile` semantics, compiler optimizations could make assumptions that aren't appropriate for such memory.

Important:

**`volatile` does not mean thread-safe.**

It does not replace:

* atomics
* mutexes
* memory barriers
* synchronization

---

# 42. Pointer alignment

Some types have alignment requirements.

For example:

```c
int x;
```

might need an address aligned to a particular boundary.

Conceptually:

```text
valid:
0x1000
0x1004
0x1008

possibly invalid:
0x1001
0x1002
```

The exact requirements depend on the architecture and type.

This matters when you start doing:

```c
char *buffer;
```

and then trying to treat part of that buffer as another type.

---

# 43. Strict aliasing

This is one of the more advanced and important C topics.

Suppose:

```c
int x = 42;

float *p = (float *)&x;
```

Then:

```c
printf("%f\n", *p);
```

is not generally a valid way to reinterpret an `int` as a `float`.

Why?

Because C has rules about **which types may be used to access an object's stored value**.

This is called the **strict aliasing rule**.

Don't assume:

```c
(T *)&object
```

automatically makes it valid to access the object as `T`.

---

# 44. Safe type reinterpretation

If your goal is to inspect the representation of an object, techniques such as `memcpy()` can be appropriate.

For example:

```c
int x = 42;
float f;

memcpy(&f, &x, sizeof(f));
```

This is different from simply pretending the `int` object is a `float` object through an incompatible pointer.

This becomes important in optimized low-level C.

---

# 45. Dangling pointers

We discussed this with `free()`, but it's important enough to revisit.

```c
int *p = malloc(sizeof(*p));

*p = 42;

free(p);
```

Now:

```c
p
```

still contains the old address.

But that memory is no longer yours.

Therefore:

```c
*p = 100;
```

is invalid.

This is a **use-after-free**.

A useful habit:

```c
free(p);
p = NULL;
```

---

# 46. Returning pointers from functions

This is dangerous:

```c
int *get_number(void)
{
    int x = 42;

    return &x;
}
```

Why?

`x` is a local variable.

When the function returns, its lifetime ends.

So the returned pointer becomes dangling.

Don't do this.

---

# 47. Returning heap memory

This is different:

```c
int *get_number(void)
{
    int *x = malloc(sizeof(*x));

    if (x == NULL)
        return NULL;

    *x = 42;

    return x;
}
```

This can be valid because the heap allocation continues to exist after the function returns.

The caller then owns the returned allocation and must eventually free it:

```c
int *p = get_number();

if (p != NULL)
{
    printf("%d\n", *p);
    free(p);
}
```

This introduces the important concept of **ownership**.

---

# 48. Ownership

When working with pointers, always ask:

> Who owns this memory?

For example:

```c
int *p = malloc(sizeof(*p));
```

Your code owns the allocation.

Eventually:

```c
free(p);
```

transfers it back to the allocator.

In larger programs, ownership might be documented as:

```text
create() → caller owns result
use()    → does not take ownership
destroy() → caller gives ownership back
```

This concept is extremely important for large C projects.

---

# 49. Pointer to dynamically allocated struct

A common pattern:

```c
struct User
{
    int id;
    char name[50];
};

struct User *user = malloc(sizeof(*user));
```

Initialize:

```c
user->id = 10;
```

Then:

```c
free(user);
```

This pattern is the foundation for many data structures.

---

# 50. Linked lists

Pointers make linked lists possible.

```c
struct Node
{
    int value;
    struct Node *next;
};
```

Conceptually:

```text
head
 │
 ▼
┌──────────────┐
│ value = 10   │
│ next ────────┼─────┐
└──────────────┘     │
                     ▼
                ┌──────────────┐
                │ value = 20   │
                │ next ────────┼─────┐
                └──────────────┘     │
                                     ▼
                                ┌──────────────┐
                                │ value = 30   │
                                │ next = NULL  │
                                └──────────────┘
```

This is one of the classic applications of pointers.

---

# 51. Trees

Pointers can also connect nodes into trees:

```c
struct Node
{
    int value;

    struct Node *left;
    struct Node *right;
};
```

Conceptually:

```text
             50
            /  \
          30    70
         / \    / \
       20  40  60  80
```

Every connection is a pointer.

---

# 52. Graphs

Graphs can also be represented using pointers.

For example, nodes can contain references to other nodes.

This is why pointers are fundamental to implementing:

* linked lists
* trees
* graphs
* hash tables
* queues
* stacks
* allocators
* kernels
* filesystems

---

# 53. Pointer-to-function tables

A very useful advanced technique is a table of function pointers.

For example:

```c
void add(void)
{
    printf("add\n");
}

void remove_item(void)
{
    printf("remove\n");
}
```

Then:

```c
void (*operations[])(void) =
{
    add,
    remove_item
};
```

You can execute:

```c
operations[0]();
operations[1]();
```

This technique is heavily used for:

* dispatch tables
* drivers
* state machines
* command interpreters
* operating systems

---

# 54. `restrict`

Now we're getting into advanced C optimization.

You may encounter:

```c
void copy(int *restrict dst,
          const int *restrict src,
          size_t count);
```

`restrict` tells the compiler that, under the contract of that code, accesses through those restricted pointers are not aliases of the same relevant objects.

This can allow better optimization.

For example, functions similar to `memcpy()` use this concept.

But don't use `restrict` casually. You must actually satisfy its rules.

---

# 55. `const` + pointers in APIs

Pointers are also used to communicate what a function is allowed to do.

For example:

```c
void print_data(const int *data, size_t count);
```

This tells the caller:

> This function receives a pointer to data but does not intend to modify the elements through that pointer.

Compare:

```c
void modify_data(int *data, size_t count);
```

Now modification is expected.

This makes pointer types part of your API design.

---

# 56. Pointer arithmetic and memory-mapped structures

Advanced systems code often deals with layouts like:

```text
base address
     │
     ▼
┌─────────────┐
│ header      │
├─────────────┤
│ payload     │
├─────────────┤
│ metadata    │
└─────────────┘
```

A pointer can be moved through the representation.

For example, when parsing a binary format, you might work with:

```c
unsigned char *buffer;
```

and advance through bytes.

But robust binary parsing also requires checking:

* bounds
* alignment
* integer overflow
* object lifetime
* endianness
* valid representation

Pointer arithmetic gives you power, but **C doesn't automatically protect you from mistakes**.

---

# 57. Buffer overrun

This is one of the biggest dangers of pointers.

Suppose:

```c
int numbers[5];
```

Valid:

```c
numbers[0]
numbers[1]
numbers[2]
numbers[3]
numbers[4]
```

Invalid:

```c
numbers[5]
numbers[6]
```

Likewise:

```c
int *p = numbers;

p += 10;
```

is not something you can safely dereference.

C doesn't automatically stop you.

That's one reason low-level C requires careful bounds management.

---

# 58. One-past-the-end pointer

There is an interesting rule.

For:

```c
int numbers[5];
```

this is allowed:

```c
int *end = numbers + 5;
```

`end` points **one past the last element**.

You cannot dereference it:

```c
*end; // invalid
```

But you can use it as a boundary:

```c
for (int *p = numbers; p != end; p++)
{
    printf("%d\n", *p);
}
```

This is a fundamental pattern in C and C++.

---

# 59. `memcpy` and pointers

Functions such as:

```c
memcpy()
memmove()
memset()
memcmp()
```

are fundamentally pointer-based.

For example:

```c
memcpy(destination, source, size);
```

means:

> Copy `size` bytes from the memory starting at `source` to the memory starting at `destination`.

Example:

```c
int source[5] = {1, 2, 3, 4, 5};
int destination[5];

memcpy(destination, source, sizeof(source));
```

Now both arrays contain the same bytes.

---

# 60. `memmove` versus `memcpy`

If source and destination overlap:

```text
source
   ↓
┌─────────────┐
│ A B C D E   │
└─────────────┘
    ↑
 destination
```

`memcpy()` is not suitable for overlapping regions.

`memmove()` is designed to handle overlap.

This is another example of why understanding pointers means understanding the **memory regions** they refer to.

---

# 61. Pointers and DMA

This connects directly to your longer-term goal.

DMA means a device can transfer data to/from memory without the CPU performing every individual transfer.

Conceptually:

```text
             CPU
              │
              │ configures
              ▼
        ┌───────────┐
        │ DMA       │
        │ controller│
        └─────┬─────┘
              │
              │ transfer
              ▼
        ┌───────────┐
        │ RAM       │
        └───────────┘
```

In driver development, pointers and memory addresses become extremely important.

But there is an important distinction:

```text
C pointer
    ≠
automatically a physical DMA address
```

A C pointer normally represents an address in the process's virtual address space.

DMA involves concepts such as:

* virtual addresses
* physical addresses
* DMA/bus addresses
* IOMMU mappings
* cache coherency
* DMA-safe buffers

That's why mastering pointers is an important prerequisite, but it is only the beginning of DMA.

---

# 62. Pointers and virtual memory

This is another major concept for your roadmap.

Suppose:

```c
int x = 42;
int *p = &x;
```

`p` normally contains a **virtual address**.

Conceptually:

```text
Program

p
│
▼
virtual address
0x7fff1234
       │
       ▼
      MMU
       │
       ▼
physical memory
0x12345000
```

The CPU and OS use virtual memory so that processes can have their own address spaces.

So when you learn pointers deeply, eventually you need to understand:

```text
C pointer
   ↓
virtual address
   ↓
page tables
   ↓
MMU
   ↓
physical address
   ↓
RAM
```

That's where C starts connecting directly to computer architecture and operating systems.

---

# 63. The most important pointer bugs

As you progress, learn to recognize these immediately:

### Uninitialized pointer

```c
int *p;
*p = 10;
```

Bad.

---

### NULL dereference

```c
int *p = NULL;

*p = 10;
```

Bad.

---

### Use after free

```c
int *p = malloc(sizeof(*p));

free(p);

*p = 10;
```

Bad.

---

### Double free

```c
free(p);
free(p);
```

Bad.

---

### Returning address of local variable

```c
int *function(void)
{
    int x = 10;
    return &x;
}
```

Bad.

---

### Out-of-bounds access

```c
int array[5];

array[10] = 42;
```

Bad.

---

### Wrong pointer type / aliasing

```c
int x;

double *p = (double *)&x;
```

Don't assume this makes it valid to access `x` as a `double`.

---

# 64. A powerful mental model

When looking at pointer code, always ask four questions:

### 1. What is the pointer?

```c
int *p;
```

It's a pointer to `int`.

### 2. What address does it contain?

```c
p
```

### 3. What object is at that address?

```c
*p
```

### 4. Is that address currently valid?

This last question is extremely important.

For example:

```c
free(p);
```

changes the answer.

Before:

```text
p → valid allocated object
```

After:

```text
p → invalid/dangling address
```

---

# 65. The pointer hierarchy

As you progress, think of pointers in levels:

```text
Level 1
int *p
    ↓
int

Level 2
int **p
     ↓
   int *
       ↓
      int

Level 3
int ***p
      ↓
    int **
       ↓
     int *
        ↓
       int
```

You don't normally need huge pointer depths, but `**` is extremely common in systems programming.

---

# 66. What you should master first

Because your goal is low-level programming, I'd recommend learning pointers in this order:

### Level 1 — Fundamentals

Master:

```c
int *p;
&p;
*p;
```

Understand:

```text
value
address
pointer
dereference
```

---

### Level 2 — Arrays

Master:

```c
array[i]
*(array + i)
```

Understand:

```text
array ↔ pointer to first element
```

and pointer arithmetic.

---

### Level 3 — Dynamic memory

Master:

```c
malloc()
calloc()
realloc()
free()
```

Understand:

```text
pointer
   ↓
heap allocation
```

and:

```text
memory leak
dangling pointer
double free
use-after-free
```

---

### Level 4 — Functions

Master:

```c
void function(int *p);
```

Then:

```c
int **p;
```

Understand how functions modify caller-owned objects and pointers.

---

### Level 5 — Structs

Master:

```c
struct Person *p;

p->field
```

Then build:

* linked lists
* stacks
* queues
* trees

---

### Level 6 — Advanced pointers

Learn:

```text
void *
const pointers
function pointers
pointer-to-pointer
restrict
volatile
alignment
aliasing
object representation
```

---

### Level 7 — Systems programming

Then connect pointers to:

```text
process memory
virtual memory
page tables
MMU
syscalls
memory mapping
shared memory
memory-mapped I/O
device drivers
DMA
```

---

# 67. The big picture

Eventually, you want this mental model:

```text
                     C PROGRAM
                         │
                         ▼
                    POINTER
                         │
                  stores address
                         │
                         ▼
                VIRTUAL ADDRESS
                         │
                         ▼
                       MMU
                         │
                  page translation
                         │
                         ▼
                  PHYSICAL MEMORY
                         │
                         ▼
                       RAM
```

And when hardware enters the picture:

```text
                         CPU
                          │
                          │ virtual address
                          ▼
                         MMU
                          │
                          ▼
                         RAM
                          ▲
                          │
                       DMA
                          ▲
                          │
                     DEVICE
```

That's the path from a seemingly simple C statement:

```c
*p = 42;
```

all the way down to the CPU, MMU, memory system, and eventually hardware.

## The core rules to memorize

```c
int x = 10;
int *p = &x;
```

Then:

```text
x       → value
&x      → address of x
p       → address stored in pointer
*p      → value at that address
```

And for arrays:

```c
array[i]
```

is equivalent to:

```c
*(array + i)
```

while:

```c
p + 1
```

means:

```text
move to the next object of the type pointed to by p
```

Finally:

```c
free(p);
```

means:

```text
release the dynamically allocated object p points to
```

—not "delete the pointer."

If you get these fundamentals completely solid, the next major step for your low-level path is **understanding exactly how pointers, arrays, stack frames, heap allocations, and CPU addresses appear in memory**, including examining them with a debugger and tools like `gdb`.

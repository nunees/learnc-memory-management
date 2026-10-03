# Memory Management Best Practices in C

The central rule is:

> **Every dynamically allocated object should have a clear owner, a clear lifetime, and exactly one responsible path that releases it.**

Think of memory management as:

```text
ALLOCATE
   ↓
OWN
   ↓
USE
   ↓
RELEASE
   ↓
NO LONGER USE
```

Let's go through the most important practices.

---

## 1. Always check `malloc()`

Never assume allocation succeeded.

Bad:

```c
int *numbers = malloc(100 * sizeof(*numbers));

numbers[0] = 10;
```

If `malloc()` fails, it returns `NULL`.

Better:

```c
int *numbers = malloc(100 * sizeof(*numbers));

if (numbers == NULL) {
    return 1;
}

numbers[0] = 10;
```

The mental model is:

```text
malloc()
   │
   ├── success → valid pointer
   │
   └── failure → NULL
```

Trying to dereference `NULL` can crash your program.

---

# 2. Use `sizeof(*pointer)`

Prefer:

```c
int *numbers = malloc(5 * sizeof(*numbers));
```

instead of:

```c
int *numbers = malloc(5 * sizeof(int));
```

Both work here, but the first is safer when the type changes.

For example:

```c
double *numbers = malloc(5 * sizeof(*numbers));
```

You don't have to remember to change `sizeof(int)`.

A very useful pattern is:

```c
type *ptr = malloc(count * sizeof(*ptr));
```

---

# 3. Keep the allocation size

This is particularly important with dynamic arrays.

Remember:

```c
int *numbers = malloc(5 * sizeof(*numbers));
```

The pointer does **not** remember that there are five elements.

You should therefore track the size separately:

```c
size_t count = 5;

int *numbers = malloc(count * sizeof(*numbers));
```

Now:

```c
for (size_t i = 0; i < count; i++) {
    numbers[i] = 0;
}
```

Think:

```text
numbers ──────────→ [ ][ ][ ][ ][ ]
                     0  1  2  3  4
                     ↑
                   count = 5
```

---

# 4. Always pair `malloc()` with `free()`

If you allocate:

```c
int *number = malloc(sizeof(*number));
```

eventually:

```c
free(number);
```

A good mental habit is to immediately ask:

> "Where will this memory be freed?"

For example:

```c
int *number = malloc(sizeof(*number));

if (number == NULL)
    return 1;

/* use number */

free(number);
```

This prevents many memory leaks.

---

# 5. Don't use memory after `free()`

This is one of the most important rules in C.

Bad:

```c
int *number = malloc(sizeof(*number));

*number = 42;

free(number);

printf("%d\n", *number);  // WRONG
```

After:

```c
free(number);
```

you no longer own that memory.

Conceptually:

```text
Before free:

number ─────→ [ 42 ]
               valid


After free:

number ─────→ [ ??? ]
               no longer yours
```

Accessing it is **use-after-free**.

---

# 6. Set pointers to `NULL` after freeing when useful

A common defensive pattern is:

```c
free(number);
number = NULL;
```

Now:

```text
number
   ↓
 NULL
```

This prevents the pointer from continuing to contain an address to memory you no longer own.

It also makes this safe:

```c
free(number);
number = NULL;

free(number);
```

Because:

```c
free(NULL);
```

is defined to do nothing.

However, setting one pointer to `NULL` doesn't invalidate other aliases:

```c
int *a = malloc(sizeof(*a));
int *b = a;

free(a);
a = NULL;
```

`b` still contains the old address.

So:

```c
*b = 10; // still WRONG
```

This leads to an important advanced topic: **ownership and aliases**.

---

# 7. Avoid double `free()`

Never do:

```c
int *p = malloc(sizeof(*p));

free(p);
free(p);  // WRONG
```

This is a **double free**.

It can cause undefined behavior and, historically, has been an important class of security vulnerability.

A simple defensive pattern:

```c
free(p);
p = NULL;
```

Then:

```c
free(p);
```

is harmless.

---

# 8. Don't overwrite the only pointer to allocated memory

This causes a memory leak:

```c
int *p = malloc(sizeof(*p));

p = malloc(sizeof(*p));
```

The first allocation is now unreachable.

```text
First malloc
     ↓
┌───────────┐
│ allocation │
└───────────┘
      X
      │
      │ pointer lost
      │

Second malloc
     ↓
p ─────────→ ┌───────────┐
             │ allocation │
             └───────────┘
```

If you need another allocation:

```c
int *new_p = malloc(sizeof(*new_p));

if (new_p == NULL) {
    free(p);
    return 1;
}

free(p);
p = new_p;
```

---

# 9. Be careful with `realloc()`

This is a very common mistake.

Don't write:

```c
numbers = realloc(numbers, new_size);
```

Why?

If `realloc()` fails, it returns `NULL`.

You could lose the original pointer:

```text
numbers
   ↓
old allocation

realloc()
   ↓
failure
   ↓
NULL

numbers → NULL
```

The original allocation may still exist, but you've lost its address.

Better:

```c
int *temp = realloc(numbers, new_size);

if (temp == NULL) {
    /* numbers is still valid */
} else {
    numbers = temp;
}
```

This is an extremely useful pattern:

```c
int *temp = realloc(ptr, new_size);

if (temp != NULL) {
    ptr = temp;
}
```

---

# 10. Initialize pointers

Avoid uninitialized pointers.

Bad:

```c
int *p;

*p = 42;
```

`p` contains an indeterminate value.

You don't know where it points.

Better:

```c
int *p = NULL;
```

Now you have a well-defined state:

```text
p → NULL
```

Later:

```c
p = malloc(sizeof(*p));
```

---

# 11. Don't return the address of a local variable

This is another important lifetime rule.

Bad:

```c
int *create_number(void)
{
    int number = 42;

    return &number;
}
```

`number` is a local variable.

Its lifetime ends when the function returns.

Conceptually:

```text
create_number()
      │
      ↓
stack frame
┌─────────────┐
│ number = 42 │
└─────────────┘
      │
 function returns
      ↓
stack frame disappears
```

The returned pointer points to memory whose lifetime has ended.

If you need the object to survive the function, dynamically allocate it:

```c
int *create_number(void)
{
    int *number = malloc(sizeof(*number));

    if (number == NULL)
        return NULL;

    *number = 42;

    return number;
}
```

Then the caller owns it:

```c
int *number = create_number();

if (number != NULL) {
    printf("%d\n", *number);
    free(number);
}
```

---

# 12. Keep ownership clear

This is one of the most important concepts for larger C programs.

Imagine:

```c
int *create_buffer(size_t size);
```

Who is responsible for freeing the returned buffer?

You should establish a clear rule.

For example:

```text
create_buffer()
      │
      ↓
caller receives pointer
      │
      │ owns memory
      ↓
caller must free()
```

Then your API becomes predictable.

This becomes extremely important when working with:

* libraries
* operating systems
* network programs
* device drivers
* linked lists
* parsers
* emulators

---

# 13. Keep `count` and `capacity` separate

This is a very useful pattern for dynamic arrays.

Suppose you have:

```c
size_t count = 3;
size_t capacity = 8;
```

Memory:

```text
capacity = 8

┌────┬────┬────┬────┬────┬────┬────┬────┐
│ A  │ B  │ C  │    │    │    │    │    │
└────┴────┴────┴────┴────┴────┴────┴────┘
 ↑              ↑
 count = 3     capacity = 8
```

`count` means:

> How many elements am I actually using?

`capacity` means:

> How many elements can I store before reallocating?

This is the foundation of a dynamic vector.

---

# 14. Watch array boundaries

This:

```c
int numbers[5];
```

creates:

```text
index:

0   1   2   3   4
↓   ↓   ↓   ↓   ↓
[ ] [ ] [ ] [ ] [ ]
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
```

There is no sixth element.

For dynamic arrays:

```c
int *numbers = malloc(5 * sizeof(*numbers));
```

the same rule applies:

```text
0   1   2   3   4
↓   ↓   ↓   ↓   ↓
[ ] [ ] [ ] [ ] [ ]
```

Never access beyond the allocated range.

Buffer overflows are among the most important memory-safety problems in C.

---

# 15. Don't confuse pointer size with allocation size

Remember:

```c
int *numbers = malloc(100 * sizeof(*numbers));
```

This:

```c
sizeof(numbers)
```

is the size of the **pointer**.

Not the allocated memory.

While:

```c
sizeof(*numbers)
```

is the size of one `int`.

And the allocation was:

```c
100 * sizeof(*numbers)
```

For example, on a typical 64-bit system:

```text
sizeof(numbers)      → 8 bytes
sizeof(*numbers)     → 4 bytes
allocated memory     → 400 bytes
```

Don't use:

```c
sizeof(numbers)
```

to determine the size of a dynamic array.

---

# 16. Use the correct integer type for sizes

For memory sizes and array indexes, `size_t` is generally the appropriate type:

```c
size_t count = 100;

int *numbers = malloc(count * sizeof(*numbers));
```

And:

```c
for (size_t i = 0; i < count; i++) {
    numbers[i] = 0;
}
```

When printing a `size_t`:

```c
printf("%zu\n", count);
```

---

# 17. Watch for integer overflow during allocation

This is more advanced, but very important for secure C programming.

Suppose:

```c
size_t count = ...;
size_t size = ...;

void *ptr = malloc(count * size);
```

If:

```text
count × size
```

overflows `size_t`, you may allocate less memory than you intended.

Then later:

```c
ptr[i]
```

could write beyond the allocation.

So for security-sensitive code, validate multiplication before allocating.

This becomes particularly important when processing:

* files
* network packets
* user input
* image data
* serialized data

---

# 18. Use `calloc()` when zero-initialization is actually needed

Instead of:

```c
int *numbers = malloc(100 * sizeof(*numbers));

for (int i = 0; i < 100; i++)
    numbers[i] = 0;
```

you can use:

```c
int *numbers = calloc(100, sizeof(*numbers));
```

`calloc()` allocates space and initializes the allocated bytes to zero.

But don't use `calloc()` automatically.

Use it when zero-initialization is part of what you need.

---

# 19. Keep allocation and cleanup easy to see

Compare:

```c
void complicated_function(void)
{
    int *a = malloc(...);
    char *b = malloc(...);
    double *c = malloc(...);

    // hundreds of lines...

    // lots of possible returns...

    free(a);
    free(b);
    free(c);
}
```

This becomes difficult to maintain.

A common C technique is to have a centralized cleanup path:

```c
int process(void)
{
    int *a = NULL;
    char *b = NULL;

    a = malloc(...);
    if (a == NULL)
        goto cleanup;

    b = malloc(...);
    if (b == NULL)
        goto cleanup;

    /* work */

cleanup:
    free(b);
    free(a);

    return 0;
}
```

`goto` is often discouraged in general programming, but **controlled `goto` cleanup is a common and legitimate C pattern**, especially when a function owns multiple resources.

You'll see this frequently in systems programming and Linux kernel code.

---

# 20. Use tools to detect memory problems

Don't rely exclusively on manually inspecting your code.

For your Linux/C learning path, learn:

### AddressSanitizer

```bash
gcc -g -fsanitize=address -fno-omit-frame-pointer program.c -o program
```

Then:

```bash
./program
```

It can detect many memory errors such as:

```text
heap-buffer-overflow
use-after-free
double-free
invalid free
```

### Valgrind

```bash
valgrind --leak-check=full ./program
```

This is particularly useful for learning about leaks.

### GDB

Use GDB to inspect:

```text
pointers
addresses
stack
memory
registers
```

For example:

```gdb
p ptr
p &ptr
x/10wx ptr
```

This is where memory management starts becoming much more concrete.

---

# A practical checklist

Whenever you use dynamic memory, ask yourself:

```text
┌─────────────────────────────────────────────┐
│          MEMORY MANAGEMENT CHECKLIST        │
├─────────────────────────────────────────────┤
│ 1. Did I check malloc/calloc/realloc?      │
│ 2. Who owns this memory?                    │
│ 3. How many bytes/elements did I allocate? │
│ 4. Do I know the allocation's lifetime?   │
│ 5. Can I accidentally access past it?      │
│ 6. Where is free() called?                 │
│ 7. Can free() happen twice?                │
│ 8. Can I use the pointer after free()?     │
│ 9. Can I lose the pointer and leak it?    │
│ 10. Can realloc() fail?                    │
└─────────────────────────────────────────────┘
```

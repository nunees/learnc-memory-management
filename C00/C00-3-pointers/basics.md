# Pointers Basics

The four cases you should memorize
```c
int x;
int *p;
int array[5];
```
Then:
```
Expression	    What it means
sizeof(x)	      Size of one int
sizeof(p)	      Size of the pointer
sizeof(*p)	      Size of the int pointed to
sizeof(array)	  Size of the entire 5-element array
```
And this:
```c
sizeof(array) / sizeof(array[0])
```
means:
```
Number of elements in the array.
```

## Dereferencing

When you use * on a pointer:
```c
*p
```
you're saying:

Go to the address stored in p and access the value there.

Example:
```c
int x = 42;
int *p = &x;

printf("%d\n", *p);
```
Output:
```
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
```
100
```
Why?

Because:
```
p ───────► x
           │
           42
```
and:
```c
*p = 100;
```
means:
```
Write 100 into the memory pointed to by p.
```

## Pointers don't contain the object

This distinction is important.
```c
int x = 42;
int *p = &x;
```
You have two objects:
```
x
┌─────────┐
│   42    │
└─────────┘

p
┌─────────┐
│ address │
└─────────┘
```
p itself occupies memory too.

For example, on a typical 64-bit system:
```c
sizeof(x) → 4
sizeof(p) → 8
```
The exact size of int varies by implementation, but pointer size is commonly 8 bytes on modern 64-bit systems.

## Why pointer types matter

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
```c
sizeof(int) = 4
```
then:
```c
int *p;
p + 1;
```
moves forward 4 bytes.

But:
```c
char *p;
p + 1;
```
moves forward 1 byte.

So pointer arithmetic is based on the size of the pointed-to type.
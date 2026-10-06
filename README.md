# Learning C

### Understanding Memory Management in C (C00)
1. [**Understanding Memory**](C00/C00-1-memory/understand-memory.md): Learn about how memory works in C, including stack vs heap, memory allocation, and deallocation.
2. [**Sizeof Operator**](C00/C00-2-sizeof/sizeof.md): Understand the `sizeof` operator and how it is used to determine the size of data types and structures in C.
3. [**Pointers**](C00/C00-3-pointers/basics.md): Understand pointers, pointer arithmetic, and how to use them effectively in C.
4. [**Dynamic Memory Allocation**](C00/C00-4-dynamic-memory/dynamic-mem-alloc.md): Learn how to use `malloc`, `calloc`, `
realloc`, and `free` for dynamic memory management.
5. [**Memory Leaks**](C00/C00-5-mem-leaks/mem-leaks.md): Understand what memory leaks are, how to detect them, and how to prevent them in your C programs.
6. [**Memory Management Best Practices**](C00/C00-6-management/best-pratices.md): Learn best practices for managing memory in C, including proper allocation and deallocation, avoiding dangling pointers, and using smart pointers or memory management libraries if applicable.

### Memory Operations (M00)

1. **Memory Copying**: Learn how to copy memory using functions like `memcpy` and `memmove`, and understand the differences between them.
2. **Memory Setting**: Understand how to set memory using functions like `memset`, and when to use them.
3. **Memory Comparison**: Learn how to compare memory blocks using functions like `memcmp`, and understand the implications of comparing memory in C.
4. **Memory Alignment**: Understand the concept of memory alignment, how it affects performance, and how to ensure proper alignment in your C programs.
5. [**Memory Mapping**](M00/M00-5-memory-mapped/basics.md): Learn about memory-mapped files and how to use them in C for efficient file I/O operations.

### Memory Operators (MO1)

1. **Bitwise Operators**: Learn about bitwise operators in C, including AND, OR, XOR, NOT, and bit shifts, and how they can be used for memory manipulation.
2. **Pointer Arithmetic**: Understand how to perform arithmetic operations on pointers, including incrementing, decrementing, and calculating offsets.
3. **Memory Access Operators**: Learn about the dereference operator (`*`) and the address-of operator (`&`), and how they are used to access and manipulate memory in C.
4. **Memory Management Functions**: Explore standard library functions for memory management, such as `malloc`, `free`, `calloc`, and `realloc`, and understand their usage and implications.
5. **Memory Safety**: Learn about common memory safety issues in C, such as buffer overflows, dangling pointers, and use-after-free errors, and how to mitigate them through careful programming practices and tools like Valgrind or AddressSanitizer.
6. **Memory Profiling and Debugging**: Understand how to profile and debug memory usage in C programs using tools like Valgrind, gdb, and memory profiling libraries to identify leaks, fragmentation, and performance bottlenecks.

### CPU (C01)

1. **CPU Architecture**: Learn about different CPU architectures and how they affect memory access patterns and performance in C programs.
2. **Cache Memory**: Understand the role of cache memory in CPU performance, including cache levels, cache hits and misses, and how to optimize memory access for better cache utilization.
3. **Memory Hierarchy**: Explore the memory hierarchy in modern computer systems, including registers, cache, main memory, and secondary storage, and how to design C programs that take advantage of this hierarchy for optimal performance.
4. **Instruction Pipelining**: Learn about instruction pipelining in CPUs and how it affects the execution of C programs, including techniques for optimizing code to minimize pipeline stalls and improve instruction throughput.
5. **Multithreading and Concurrency**: Understand how multithreading and concurrency affect memory access in C programs, including issues like race conditions, memory consistency, and synchronization mechanisms such as mutexes and semaphores to ensure safe access to shared memory.
6. **Memory Access Patterns**: Learn about different memory access patterns in C programs, such as sequential vs random access, and how to optimize data structures and algorithms for better memory locality and performance.
7. **DMA (Direct Memory Access)**: Understand how DMA works in computer systems, its advantages for high-speed data transfer, and how to leverage DMA in C programs for efficient memory operations without CPU intervention.

## Assembly Language (A00)

1. **Introduction to Assembly Language**: Learn the basics of assembly language programming, including syntax, instructions, and how it relates to C programming.
2. **Assembly Language Instructions**: Understand common assembly language instructions, including data movement, arithmetic, control flow, and how they map to C constructs.
3. **Calling Conventions**: Learn about calling conventions in assembly language, including how functions are called, how parameters are passed, and how return values are handled, and how this relates to C function calls.
4. **Inline Assembly**: Explore how to use inline assembly within C programs, including syntax, constraints, and best practices for integrating assembly code with C code for performance optimization.
5. **Assembly Language Optimization**: Understand techniques for optimizing assembly language code, including instruction selection, loop unrolling, and register allocation, and how these optimizations can improve the performance of C programs.
6. **Debugging Assembly Code**: Learn how to debug assembly code using tools like gdb, objdump, and disassemblers, and how to analyze assembly output generated from C code to identify performance bottlenecks and optimize memory usage.
7. **Assembly Language and Memory Management**: Understand how assembly language interacts with memory management in C, including stack and heap management, memory alignment, and how to write efficient assembly code that complements C memory management practices for better performance and resource utilization.   

## Projects

1. **Memory Management Project**: Create a C program that implements a custom memory allocator, including functions for allocation, deallocation, and memory tracking, and demonstrate its usage in a sample application.
2. **Pointer Manipulation Project**: Develop a C program that demonstrates advanced pointer manipulation techniques, including pointer arithmetic, dynamic memory allocation, and memory access patterns, and analyze its performance and memory usage.
3. **Assembly Language Project**: Write a C program that includes inline assembly code for performance-critical sections, and analyze the impact of assembly optimizations on memory access and overall program performance.
4. **Cache Optimization Project**: Create a C program that demonstrates the effects of cache memory on performance, including techniques for optimizing data structures and algorithms for better cache utilization, and measure the performance improvements achieved through these optimizations.
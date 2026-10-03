# Projects Roadmap

# 1. Digital Logic (Foundation)

Before CPUs, understand how hardware is built.

Learn:

- Binary and hexadecimal
- Boolean algebra
- Logic gates (AND, OR, XOR, NOT)
- Adders and ALUs
- Multiplexers and decoders
- Flip-flops and registers
- Finite State Machines (FSMs)

Projects:

- Build an 8-bit adder
- Build a simple ALU
- Build a CPU in a simulator like Logisim

Why?

Because a CPU is ultimately millions of logic gates connected together.

# 2. Computer Architecture

This is where you learn how processors actually work.

Learn:

- Registers
- Program Counter (PC)
- Stack Pointer (SP)
- Instruction Register (IR)
- Fetch → Decode → Execute
- Pipelines
- Branch prediction
- Instruction sets (ISA)
- Microarchitecture

Resources:

- Computer Organization and Design (Patterson & Hennessy)
- Computer Systems: A Programmer's Perspective (CS:APP)

Projects:

- Build a toy CPU emulator
- Implement an instruction decoder

# 3. Assembly Language

Pick one architecture.

I recommend:

- x86-64
- ARM64

Learn:

- Registers
- Calling conventions
- Stack frames
- Function calls
- Interrupts
- Syscalls

Example:

```asm
mov rax, 1
mov rdi, 1
syscall
```

Understand exactly what happens when a function is called.

# 4. Memory Fundamentals

This is critical.

Learn:

- Physical Memory
- RAM
- Memory addresses
- Bus systems
- Process Memory Layout
- High Memory

```
+------------+
| Stack      |
+------------+
| Heap       |
+------------+
| BSS        |
+------------+
| Data       |
+------------+
| Text       |
+------------+
Low Memory
```

Learn:

- Stack
- Heap
- Static memory
- Global variables
- Memory alignment

Projects:

- Write your own allocator
- Implement a simple heap manager

# 5. Virtual Memory

This is where things become interesting.

Learn:

- Page tables
- Virtual addresses
- Physical addresses
- MMU
- TLB
- Demand paging
- Copy-on-write

Understand:
```
Program thinks:
0x400000

CPU translates:
0x400000
   ↓
MMU
   ↓
0x12345000
```
Tools:

- cat /proc/self/maps
- pmap

# 6. Operating Systems

Learn how memory and processes are managed.

Topics:

- Processes
- Threads
- Scheduling
- Context switching
- Signals
- System calls
- Shared memory
- Synchronization

Books:

-Operating Systems: Three Easy Pieces (free)
-Modern Operating Systems (Tanenbaum)

Projects:

- Build a toy scheduler
- Write a small shell

# 7. C Programming at a Low Level

Become very comfortable with:

- malloc
- free
- memcpy
- memmove
- mmap

```c
Pointers:

int *ptr;

Pointer arithmetic:

ptr + 1
```

Memory debugging:

- gdb
- valgrind

# 8. CPU Emulation

Start simple.

Order:
```
CHIP-8
↓
6502
↓
Game Boy CPU
↓
RISC-V
↓
x86
```

Learn:

- Instruction decoding
- Memory mapping
- Timers
- Interrupts
- DMA
- Hardware peripherals

Projects:

- CHIP-8 emulator
- Game Boy emulator

# 9. Caches and Performance

Many developers never study this deeply.

Learn:

- L1 cache
- L2 cache
- L3 cache
- Cache lines
- Locality of reference
- Cache misses

Example:

```c
for(i=0;i<n;i++)
```

can be much faster than:

```c
for(i=n;i>=0;i--)
```
depending on memory access patterns.

Tools:

- perf
- cachegrind

# 10. Linux Internals

Given your interest in Docker and infrastructure, this is extremely valuable.

Learn:

- ELF files
- Process creation
- fork()
- execve()
- clone()
- Signals
- Namespaces
- cgroups

Investigate:

- strace
- ltrace
- perf

Read:

Linux Programming Interface

# 11. Compilers

Understand what transforms source code into machine code.

Learn:

- Lexing
- Parsing
- ASTs
- Intermediate Representations
- Optimization
- Code generation

Projects:

- Tiny interpreter
- Small compiler

Books:

Crafting Interpreters
Engineering a Compiler

# 12. Virtualization

After understanding CPUs and memory, virtualization becomes much easier.

Learn:

- Hypervisors
- VT-x
- AMD-V
- KVM
- QEMU

Study:
```
Guest OS
↓
Virtual CPU
↓
Hypervisor
↓
Real CPU
```
Projects:

- Run Linux with QEMU
- Explore KVM

13. Kernel Development

Eventually:

Learn:

- Bootloaders
- Interrupt Descriptor Tables
- Paging
- Device drivers
- Scheduler design
- Memory manager design

Projects:

- Build a toy kernel
- Add paging
- Add multitasking
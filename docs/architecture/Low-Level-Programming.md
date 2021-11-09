# Notes of **Low-Level Programming: C, Assembly, and Program Execution on Intel® 64 Architecture**


|时间|内容|
|:---|:---|
|20211105|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### Part I: Assembly Language and Computer Architecture
#### 1. Basic Computer Architecture
#### 2. Assembly Language

##### 2.1 Setting Up the Environment
##### 2.2 Writing “Hello, world”

To perform system calls:

- `rax` register to hold the system call's number;
- pass arguments in the order of `rdi`, `rsi`, `rdx`, `r10`, `r8`, `r9`;
- execute `syscall` instruction;
- return value: `rax`;
- side effect: destroy register `rcx`, `r11`.

##### 2.3 Example: Output Register Contents
##### 2.4 Function Calls

```
call <address>
ret
```

- the first 6 arguments are passed in `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`;
- rest arguments are passed on to the stack in reverse order;
- return value: `rax`, `rdx`.

convention:

- callee-saved registers: `rbx`, `rbp`, `rsp`, `r12-r15`;
- caller-saved registers: all other registers.

##### 2.5 Working with Data
##### 2.6 Example: Calculating String Length
##### 2.7 Assignment: Input/Output Library

#### 3. Legacy

processor modes:

- real mode: 16-bit
- protected mode: 32-bit
- virtual mode: emulate real mode inside protected
- system management mode: sleep mode, power management, etc
- long mode: 64-bit

real mode:

physical address = segment base * 16 + offset

protected mode:

linear address = segment base(taken from system table) + offset

- segment selector: cs, ds, ss, es, fs, gs
- LDT: Local Descriptor Table
- GDT: Global Descriptor Table
- GDTR: a register to store GDT address and size
- RPL: Request Privilege Level, stored in segment selector registers
- DPL: Descriptor Privilege Level, stored in descriptor table
- privilege levels: protection rings

long mode:

at least 3 descriptors should be presented in GDT:

- the null descriptor
- code segment descriptor
- data segment descriptor

#### 4. Virtual Memory

- CPU: Central Processing Unit
- instruction cache
- TLB: Translation Lookaside Buffer
- locality
- address space: physical address, logical address(virtual address)
- MMU: Memory Management Unit
- page: the address space of a single process is split into pages
- region:  a continuous area of memory
- page frame: physical address space is divided into slots to be filled with virtual pages, these slots are called page frames


- PML4: Page Map Level 4
- Page Directory Pointer Table
- Page Directory
- Page Table

#### 5. Compilation Pipeline
#### 6. Interrupts and System Calls

##### Input and Output

applications access I/O ports in 2 ways:

- through a separate I/O address space:

`rflags` register field IOPL(I/O priviledge level) <br/>
I/O permission bit map of a Task State Segment

- through memory-mapped I/O

terms:

- TSS: Task State Segment
- `tr`: register holds the segment selector to the TSS descriptor
- shadow register: updated from GDT when `tr` is updated via `ltr` instruction(load task register)
- IST: Interrupt Statck Table

##### Interrupt

- interrupt handler
- IDT: Interrupt Descriptor Table
- `idtr`: register stores IDT address and size

##### System Calls

- MSR: Model Specific Register

#### 7. Models of Computation

##### 7.1 Finite State Machines
##### 7.2 Forth Machine

```
: sq dup * ;


swap (a b -- b a)
rot (a b c -- b c a)


: discr rot 4 * * swap sq swap - ;
```

##### 7.3 Assignment: Forth Compiler and Interpreter

### Part II: The C Programming Language
#### 8. Basics
#### 9. Type System
#### 10. Code Structure
#### 11. Memory
#### 12. Syntax, Semantics, and Pragmatics
#### 13. Good Code Practices

### Part III: Between C and Assembly
#### 14. Translation Details
#### 15. Shared Objects and Code Models

##### 15.1 Dynamic Loading
##### 15.2 Relocations and PIC

- PIC: Position Independent Code

##### 15.3 Example: Dynamic Library in C
##### 15.4 GOT and PLT

- GOT: Global Offset Table
- PLT: Program Linkage Table

##### 15.5 Preloading
##### 15.6 Symbol Addressing Summary
##### 15.7 Examples
##### 15.8 Which Objects Are Linked?
##### 15.9 Optimizations
##### 15.10 Code Models
##### 15.11 Summary

#### 16. Performance

##### 16.1 Optimizations
##### 16.2 Caching
##### 16.3 SIMD Instruction Class

- SIMD: Single Instruction, Multiple Data

##### 16.4 SSE and AVX Extensions

- SSE: Streaming SIMD Extensions
- AVX: Advanced Vector Extensions

##### 16.5 Summary

- valgrind, cachegrind: check amount of cache misses

#### 17. Multithreading

##### 17.1 Processes and Threads
##### 17.2 What Makes Multithreading Hard?
##### 17.3 Execution Order
##### 17.4 Strong and Weak Memory Models
##### 17.5 Reordering Example
##### 17.6 What Is Volatile and What Is Not
##### 17.7 Memory Barriers
##### 17.8 Introduction to pthreads
##### 17.9 Semaphores
##### 17.10 How Strong Is Intel 64?
##### 17.11 What Is Lock-Free Programming?
##### 17.12 C11 Memory Model
##### 17.13 Summary


### Part IV: Appendices
#### 18. Appendix A. Using gdb
#### 19. Appendix B. Using Make
#### 20. Appendix C. System Calls
#### 21. Appendix D. Performance Tests Information
#### 22. Bibliography

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

```

@Book{Zhirkov2017,
  author    = {Igor Zhirkov},
  publisher = {Apress},
  title     = {Low-Level Programming: C, Assembly, and Program Execution on Intel® 64 Architecture},
  year      = {2017},
  isbn      = {978-1-4842-2402-1},
}

```

## 其他备注

### Linux

- [Searchable Linux Syscall Table for x86 and x86_64](https://filippo.io/linux-syscall-table/)

### MacOS

- [Mac OS X 64 bit Assembly System Calls](http://dustin.schultz.io/mac-os-x-64-bit-assembly-system-calls.html): `0×2000000 + unix syscall #`
- [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
- [BEYOND HELLO WORLD - The Daft Guide to 64-bit Assembly for macOS by Virgil Grimes](http://daft.getforge.io/)
- [syscalls.master](https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master)

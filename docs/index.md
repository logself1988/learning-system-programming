# Learning System Programming

## Tools

### GNU

- [GNU toolchain](./tools/gnu/gnu-toolchain.md)
- [An Introduction to GCC](./tools/gnu/gcc-intro.md)
- [The GNU C Library Reference Manual](./tools/gnu/gnu-glibc.md)
- [Managing Projects with GNU Make](./tools/gnu/gnu-make.md)
- [GNU Autotools](./tools/gnu/gnu-autotools.md)

### Programming

- [C工具](./tools/programming/c-tool.md)
- [C++工具](./tools/programming/cpp-tool.md)
- [CMake](./tools/programming/cmake/mastering-cmake.md)
- [The Ninja build system](./tools/programming/ninja.md)

## Architecture


### Books

- [Computer Architecture: A Quantitative Approach](./architecture/CAQA.md)
- [Low-Level Programming: C, Assembly, and Program Execution on Intel® 64 Architecture](./architecture/Low-Level-Programming.md)


### Linux CPU Architectures

- [The Linux Kernel >> CPU Architectures](./architecture/linux-cpu-architecture.md)

ABI:

- [System V Application Binary Interface: Intel386 and AMD64](./architecture/ABI.md)


### Specific Architecture

Intel 64, IA-32 Manual:

- [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 1: Basic Architecture](./architecture/intel/vol1-basic-architecture.md)
- [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3A: System Programming Guide, Part 1](./architecture/intel/vol3a-system-programming-guide.md)
- [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3B: System Programming Guide, Part 2](./architecture/intel/vol3b-system-programming-guide.md)

Instruction listings:

- [x86 instruction listings](https://en.wikipedia.org/wiki/X86_instruction_listings): x86 integer instructions, x87 floating-point instructions, SIMD instructions, Cryptographic instructions, Undocumented instructions


## Assembly

### Books

- [Professional Assembly Language](./assembly/pro-assembly.md)
- [Instructions](./assembly/instructions.md)
- [Assembly Language Step-by-Step](./assembly/assembly-step-by-step.md): mostly Assembly concenpts, can also used as a NASM intriduction
- [NASM – The Netwide Assembler](./assembly/nasm.md)

### Resources

- Professional Assembly Language, Richard Blum, 2016.
- Examples: [GNU Assembler Examples](https://cs.lmu.edu/~ray/notes/gasexamples/), [How to Mix C and Assembly](https://www.devdungeon.com/content/how-mix-c-and-assembly)
- IA-32 Volume 1: Basic Architecture
- IA-32 Volume 2: Instruction Set Reference
- IA-32 Volume 3: System Programming Guide
- [ELF x86-64-ABI psABI](https://github.com/hjl-tools/x86-psABI): AMD64 ABI.
- [application binary interface (ABI) - wikipedia](https://en.wikipedia.org/wiki/Application_binary_interface)

### Community

- stackoverflow assembly: https://stackoverflow.com/questions/tagged/assembly
- stackoverflow nasm: https://stackoverflow.com/questions/tagged/nasm
- nasm forum: https://forum.nasm.us/

### FAQ

- [x86 Assembly pushl/popl don't work with “Error: suffix or operands invalid”](https://stackoverflow.com/questions/5485468/x86-assembly-pushl-popl-dont-work-with-error-suffix-or-operands-invalid): 32-bit与64-bit系统调用的区别.
- [Compiling x86 Assembly on x64 Linux](https://denniskubes.com/2017/01/31/compiling-x86-assembly-on-x64-linux/): 在64-bit Linux机器上编译32-bit的代码.
- [IA-32 ASSEMBLY ON MAC OS X](https://fabiensanglard.net/macosxassembly/index.php): 在Mac OSX上使用IA32汇编.
- [Calling printf in x86_64 using GNU assembler](https://stackoverflow.com/questions/38335212/calling-printf-in-x86-64-using-gnu-assembler)
- [What are the calling conventions for UNIX & Linux system calls on i386 and x86-64](https://stackoverflow.com/questions/2535989/what-are-the-calling-conventions-for-unix-linux-system-calls-on-i386-and-x86-6)


## C

- [Headers](./c/c-headers.md)
- [C Core](./c/c-core.md)

## C++


- [The Definitive C++ Book Guide and List](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list/388282#388282): at stackoverflow

> This question attempts to collect the few pearls among the dozens of bad C++ books that are published every year.

- [Programming: Principles and Practice Using C++'](./cpp/PPP2/PPP2.md)
- [C++ Primer](./cpp/CP5/CP5.md)
- [C++ 11](./cpp/CXX11-Standard.md)
- [C++ Concurrency in Action](./cpp/cpp_concurrency.md)
- [Q&A](./cpp/QA.md)

## Kernel

### Programming

- [APUE](./kernel/programming/apue.md): Advanced Programming in the UNIX® Environment
- [TLPI](./kernel/programming/tlpi.md): The Linux Programming Interface
- [系统调用的概览](./kernel/programming/syscall.md)

### Specifications

- [Linux Manual Page](./kernel/specification/linux-man.md)
- [Linux Standard Base](./kernel/specification/linux-standard-base.md)
- [Linux Foundation Referenced Specifications](./kernel/specification/linux-ref-spec.md)

### Linux Architecture

- [Linux内核设计与实现](./kernel/linux-arch/kernel-dev/kernel-dev.md)
- [深入Linux内核架构](./kernel/linux-arch/linux-arch.md)
- [Linux内核设计的艺术](./kernel/linux-arch/linux-0.11.md): kernel 0.11

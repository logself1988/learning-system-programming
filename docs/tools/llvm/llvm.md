# Notes of LLVM

|时间|内容|
|:---|:---|
|20210818|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- LLVM: Low Level Virtual Machine

## 介绍

<!-- 描述软件的来源、特性、解决的关键性问题等. -->

## 动机

<!-- 描述阅读软件源码的动机, 要达到什么目的等. -->

## 系统结构

<!-- 描述软件的系统结构, 核心和辅助组件的结构; 系统较复杂时细分展示. -->

### 子项目

|subproject           | Description|
|:---                 |:---|
| LLVM Core           | The LLVM Core libraries provide a modern source- and target-independent optimizer, along with code generation support for many popular CPUs (as well as some less common ones!) These libraries are built around a well specified code representation known as the LLVM intermediate representation ("LLVM IR"). The LLVM Core libraries are well documented, and it is particularly easy to invent your own language (or port an existing compiler) to use LLVM as an optimizer and code generator.|
| Clang               | Clang is an "LLVM native" C/C++/Objective-C compiler, which aims to deliver amazingly fast compiles, extremely useful error and warning messages and to provide a platform for building great source level tools. The Clang Static Analyzer and clang-tidy are tools that automatically find bugs in your code, and are great examples of the sort of tools that can be built using the Clang frontend as a library to parse C/C++ code.|
| LLDB                | The LLDB project builds on libraries provided by LLVM and Clang to provide a great native debugger. It uses the Clang ASTs and expression parser, LLVM JIT, LLVM disassembler, etc so that it provides an experience that "just works". It is also blazing fast and much more memory efficient than GDB at loading symbols.|
| libc++, libc++ ABI  | The libc++ and libc++ ABI projects provide a standard conformant and high-performance implementation of the C++ Standard Library, including full support for C++11 and C++14.|
| compiler-rt         | The compiler-rt project provides highly tuned implementations of the low-level code generator support routines like "__fixunsdfdi" and other calls generated when a target doesn't have a short sequence of native instructions to implement a core IR operation. It also provides implementations of run-time libraries for dynamic testing tools such as AddressSanitizer, ThreadSanitizer, MemorySanitizer, and DataFlowSanitizer.|
| MLIR                | The MLIR subproject is a novel approach to building reusable and extensible compiler infrastructure. MLIR aims to address software fragmentation, improve compilation for heterogeneous hardware, significantly reduce the cost of building domain specific compilers, and aid in connecting existing compilers together.|
| OpenMP              | The OpenMP subproject provides an OpenMP runtime for use with the OpenMP implementation in Clang.|
| polly               | The polly project implements a suite of cache-locality optimizations as well as auto-parallelism and vectorization using a polyhedral model.|
| libclc              | The libclc project aims to implement the OpenCL standard library.|
| klee                | The klee project implements a "symbolic virtual machine" which uses a theorem prover to try to evaluate all dynamic paths through a program in an effort to find bugs and to prove properties of functions. A major feature of klee is that it can produce a testcase in the event that it detects a bug.|
| LLD                 | The LLD project is a new linker. That is a drop-in replacement for system linkers and runs much faster.|

### llvm-project/llvm

--8<--
tools/llvm/snippets/llvm-code-dir.md
--8<--

### LLVM_INSTALL_PATH/lib

--8<--
tools/llvm/snippets/llvm-lib-dir.md
--8<--

### LLVM_INSTALL_PATH/include

--8<--
tools/llvm/snippets/llvm-include-dir.md
--8<--

## 使用

<!-- 记录软件如何使用. -->

## 数据结构和算法

<!-- 描述软件中重要的数据结构和算法, 支撑过程部分的记录. -->

## 过程

<!-- 描述软件中重要的过程性内容, 例如服务器的启动、服务器响应客户端请求、服务器背景活动等. -->

## 文献引用

<!-- 记录软件相关和进一步阅读资料: 文献、网页链接等. -->

### 网页

- [LLVM Documentation](https://llvm.org/docs/index.html)

#### LLVM Design & Overview

- [Introduction to the LLVM Compiler](https://llvm.org/pubs/2008-10-04-ACAT-LLVM-Intro.html): Presentation providing a users introduction to LLVM.
- [Intro to LLVM](http://www.aosabook.org/en/llvm.html): A chapter from the book “The Architecture of Open Source Applications” that describes high-level design decisions that shaped LLVM.
- [LLVM: A Compilation Framework for Lifelong Program Analysis & Transformation](https://llvm.org/pubs/2004-01-30-CGO-LLVM.html): Design overview.
- [LLVM: An Infrastructure for Multi-Stage Optimization](https://llvm.org/pubs/2002-12-LattnerMSThesis.html): More details (quite old now).

#### Documentation

- [Getting Started/Tutorials](https://llvm.org/docs/GettingStartedTutorials.html): For those new to the LLVM system.
- [User Guides](https://llvm.org/docs/UserGuides.html): User guides and How-tos.
- [Reference](https://llvm.org/docs/Reference.html): LLVM and API reference documentation.

####

## 其他备注

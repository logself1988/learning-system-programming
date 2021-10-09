# Notes of **Getting Started with LLVM Core Libraries**


|时间|内容|
|:---|:---|
|20210818|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. Build and Install LLVM

### 2. External Projects

### 3. Tools and Design

- **clang**
- **opt**: optimize a program at the IR level
- **llc**: convert LLVM bitcode to a target-machine assembly language file or object file via a specific backend
- **llvm-mc**: assemble instructions and generate object files(ELF, PE, MachO), disassemble the same objects
- **lli**: an interpreter and a JIT compiler for LLVM IR
- **llvm-link**: link several LLVM bitcodes to produce a single LLVM bitcode
- **llvm-as**: transform LLVM IR filse(human-readable LLVM assemblies) into LLVM bitcodes
- **llvm-dis**: decode LLVM bitcodes into LLVM assemblies
- **llvm-config**: print LLVM compilation options

`*.bc`: LLVM bitcode files
`*.ll`: LLVM assembly files

LLVM basic libraries:

> https://releases.llvm.org/3.0/docs/UsingLibraries.html

- **libLLVMCore**: 提供了LLVM IR相关的逻辑, 包括IR构造(数据布局、指令、基本块和函数)、IR验证器(verifier)和趟管理器(pass manager).
- **libLLVMAnalysis**: 包含几个IR分析趟(alias analysis, dependence analysis, constant folding, loop info, memory dependence analysis, instruction simplify).
- **libLLVMCodeGen**: 实现了独立于目标的代码生成和机器级别的分析和转换.
- **libLLVMTarget**: 通过通用的目标抽象提供了访问目标机器信息的功能.
- **libLLVMX86CodeGen**: 包含构成x86后段的目标代码生成信息、转换和分析趟.
- **libLLVMSupport**: 一组工具，包括错误、整数和浮点数处理、命令行解析、调试、文件支持、字符串处理等.
- **libclang**: 实现了访问Clang前端功能的C接口, 这些功能包括诊断报告、AST遍历、代码补全、游标映射和源代码.
- **libclangDriver**: 包含了一组类， 被编译器驱动器工具用于理解类GCC命令行参数并为外部工具准备作业和组织恰当的参数， 以支持编译的不同步骤.
- **libclangAnalysis**: 由Clang提供的一组前端层级的分析，包括CFG和调用图构造、可达代码等.

### 4. The Frontend

meanings of Clang:

- the frontend: Clang libraries
- the compiler driver: `clang` command, the Clang Driver library
- the actual compiler: `clang -cc1` command

> $ sudo apt-get install libclang-dev

Currently, clang is divided into the following libraries and tool:

> https://clang.llvm.org/features.html

- **libsupport**: Basic support library, from LLVM.
- **libsystem**: System abstraction library, from LLVM.
- **libbasic**: Diagnostics, SourceLocations, SourceBuffer abstraction, file system caching for input source files.
- **libast**: Provides classes to represent the C AST, the C type system, builtin functions, and various helpers for analyzing and manipulating the AST (visitors, pretty printers, etc).
- **liblex**: Lexing and preprocessing, identifier hash table, pragma handling, tokens, and macro expansion.
- **libparse**: Parsing. This library invokes coarse-grained 'Actions' provided by the client (e.g. libsema builds ASTs) but knows nothing about ASTs or other client-specific data structures.
- **libsema**: Semantic Analysis. This provides a set of parser actions to build a standardized AST for programs.
- **libcodegen**: Lower the AST to LLVM IR for optimization & code generation.
- **librewrite**: Editing of text buffers (important for code rewriting transformation, like refactoring).
- **libanalysis**: Static analysis support.
- **clang**: A driver program, client of the libraries at various levels.


Usage of Clang:

- diagnostic
- lexical analysis
- syntactic analysis
- semantic analysis
- generate LLVM IR

```
extern "C"
{
  #include "clang-c/Index.h"
}

CXTranslationUnit

CXDiagnostic

CXToken
enum CXTokenKind

Decl: TranslationUnitDecl, FunctionDecl, VarDecl
Stmt: IfStmt
Type
```


### 5. The LLVM Intermediate Representation

LLVM IR有三种等价形式:

- 内存中表示: `Instruction`类等;
- 磁盘上空间紧凑形式的表示: bitcode文件;
- 磁盘上刻度文本形式的表示: LLVM汇编文件.

```
// file: sum.c
clang sum.c -emit-llvm -c -o sum.bc
clang sum.c -emit-llvm -S -c -o sum.ll
llvm-as sum.ll -o sum.bc
llvm-dis sum.bc -o sum.ll
llvm-extract -func=sum sum.bc -o sum-fn.bc
```

LLVM IR language syntax: [LLVM Language Reference Manual](https://llvm.org/docs/LangRef.html)

- module: `Module`
- functions: `Function`
- basic blocks: `BasicBlock`, function body is explicitly divided into basic blocks
- instructions: `Instruction`
- peripheral entities: global variables(prefixed with `@`), target data layout, external function prototypes, data structure declarations
- use the SSA(Static Single Assignment) form: `Value`, `User`
- organized codes as three-address instructions
- has an infinite number of registers
- local variable: prefixed with `%`

```
target datalayout: type:<size>:<abi>:<preferred>
target triple

define i32 @sum(i32 %a, i32 %b) #0 {
attributes #0 = {
```

- types: `i32`, `i64`, `i128`, `float`, `double`, vectors `<<# elements> x <elementtype>>`


Generating the C++ source code needed to generate the same IR file for a given LLVM IR file(bitcode or assembly):

> has been removed!!!

```
llv -march=cpp sum.bc -o sum.cpp
```

### 6. The Backend


LLVM backend organization

```
|LLVM IR| -> [Passes] -> (Instrction selection)
          -> (Instruction scheduling)/(Pre-register Allocation Scheduling)
          -> [Passes] -> (Register allocation)
          -> [Passes] -> (Instruction scheduling)/(Post-register Allocation Scheduling)
          -> [Passes] -> (Code emission)
          -> <Assembly>, <Object code>

four distinct levels of instruction representation:
|LLVM IR| => |SelectionDAG| => |MachineInstr| => |MCInst|

(Instruction selection): 将内存中IR表示转换为目标特定的SelectionDAG节点. 节点通常表示指令, 边通常编码了指令之间的数据流依赖. 便于使用基于树的藐视匹配指令选择算法. 最终DAG中节点转换为目标机器指令.

(Instruction scheduling)/(Pre-register Allocation Scheduling): 将指令排序并尝试发现指令级并行. 指令被转换为MachineInstr三地址表示.

(Register allocation): 尝试将无限数量的虚拟寄存器映射到有限数量的目标特定寄存器.

(Instruction scheduling)/(Post-register Allocation Scheduling): 使用物理寄存器的信息优化指令排序.

(Code emission): 将MachineInstr三地址表示的指令转换为MCInst表示, 该表示便于汇编器和加载器处理.
```

#### backend code structure, libraries

#### TableGen: describe a backend

#### instruction selection

#### machine instructions

#### instruction scheduling

#### register allocation

#### prologure, epilogue

#### machine code framework

- MC instructions: `MCInst`
- code emission

### 7. The Just-in-Time Compiler

```
llvm::MCJIT
lli
llvm-rtdyld
```

### 8. Cross-platform Compilation

**native executables**: runs on the same platform of the compiler<br/>
**platform**: a combination of hardware, operating system, applicaiton binary interface(ABI [^1]), and system interface choices.

[^1]: ABI: https://en.wikipedia.org/wiki/Application_binary_interface

**Cross-platform compilation** is the process of using a compiler to generate executables for different, non-native platforms.

### 9. The Clang Static Analyzer

### 10. Clang Tools with LibTooling

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Bruno Cardoso Lopes, Rafael Auler. **Getting Started with LLVM Core Libraries**. Packet Publishing: 2014.

## 其他备注

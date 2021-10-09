# Notes of **LLVM Essentials**


|时间|内容|
|:---|:---|
|20210816|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

1. 了解LLVM项目: 常用工具;
2. 了解LLVM IR: 文法, 转换, 选择和代码生成.

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. Playing with LLVM

LLVM core libraries提供了一些工具:

- `opt`, the target independent optimizer

优化器可以运行多个不同的优化趟: `Pass`, `PassManager`

- code generation support for various target architecture

分为多趟: instruction selection, register allocation, scheduleing, code layout optimization, assembly emission

LLVM IR(Intermediate Representation) 三种等价形式:

- in-memory compiler IR
- on-disk bitcode representation
- human readable form: LLVM Assembly

环境和版本:

```
$ uname -a
Linux DESKTOP-V3GKSFN 4.19.128-microsoft-standard #1 SMP Tue Jun 23 12:58:10 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ clang --version
clang version 10.0.0-4ubuntu1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

``` c
int globvar = 12;

int add(int a) {
	return globvar + a;
}
```

```
$ clang -emit-llvm -c -S add.c
$ cat add.ll
; ModuleID = 'add.c'                        ; 模块标识
source_filename = "add.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
                                            ; 目标数据布局: endianess of machine, name mangling
target triple = "x86_64-pc-linux-gnu"       ; 目标三元组

@globvar = dso_local global i32 12, align 4 ; 全局变量: `@`
                                            ; 局部变量: `%`
; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @add(i32 %0) #0 {      
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* @globvar, align 4
  %4 = load i32, i32* %2, align 4
  %5 = add nsw i32 %3, %4
  ret i32 %5
}
; SSA(Static Single Assignment) 静态单赋值
; 每个变量只被赋值一次, 在变量的每次使用之前都有它的定义.
;
; 全局变量: 视为指针, 需要显式解引用和显式存储指令.
; 局部变量:
; (1) 寄存器分配的局部变量: 临时分配的虚拟寄存器, 在代码生成阶段用物理寄存器分配;
; (2) 栈分配的局部变量: 在当前执行的函数的栈帧上用`alloca`指令分配变量.
;
; LLVM使用三地址指令, 有两个源操作数、一个目的操作数, 例: `%4 = add i32 %2 %3`

; 函数的属性字符串
attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}                         ; 标识模块和编译器版本

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
```

LLVM的moudle是包含输入LLVM文件完整内容的顶级数据结构, 由函数、全局变量、外部函数原型和符号表项构成.

LLVM工具:

- (1) llvm-as: LLVM汇编器, 将汇编形式的LLVM IR转换为bitcode格式.

```
llvm-as add.ll -o add.bc
```

- (2) llvm-dis: LLVM反汇编器, 输入bitcode文件, 输出LLVM汇编文件

```
llvm-dis add.bc -o add.ll
```

- (3) llvm-link: 链接两个或多个LLVM bitcode文件, 输出一个LLVM bitcode文件

```
$ cat main.c
#include <stdio.h>

extern int add(int);

int main()
{
    int a = add(2);
    printf("%d\n", a);
    return 0;
}
```

```
$ clang -emit-llvm -c main.c
$ llvm-link main.bc add.bc -o output.bc
```

- (4) lli: 使用当前架构上的JIT编译器或解释器执行执行LLVM bitcode格式的程序

```
$ lli output.bc
14
```

- (5) llc: 静态编译器, 将LLVM 汇编/bitcode形式编译为特定架构的汇编语言

```
$ llc output.bc -o output.s
```

- (6) opt: LLVM分析器和优化器

### 2. Building LLVM IR

```
$ llvm-config --cxxflags --ldflags --system-libs --libs core
-I/usr/lib/llvm-10/include -std=c++14   -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
-L/usr/lib/llvm-10/lib
-lLLVM-10
```

``` c++
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h" // for llvm:outs()
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;
```

``` c++
LLVMContext
Module
IRBuilder
Function, FunctionType, Function::arg_iterator
verifyFunction
BasicBlock
GlobalVariable
Value
SmallVector<>
PHINode
```

``` c++
new Module(Name, LLVMContext)
```

### 3. Advanced LLVM IR

### 4. Basic IR Transformations

### 5. Advanced IR Block Transformations

- Loop processing: Loop Simplification, Loop Invariant Code Motion

CFG: Control-Flow Graph

CFG G = (V, E)

d,n are nodes in G, d dominates n (d -> n) if every path tha passes through n must also pass through d.

``` c++
LoopPass
LPPassManager
LoopInfo
```

Loop Simplification: insertion of a preheader to the loop, insert loop exit blocks

Loop Invariant Code Motion(LICM): remove the code which is invariant inside the loop from the loop

```
opt -licm xxx.ll -o xxx.bc
```

other loop optimizations: Loop Rotation, Loop Interchange, Loop Unswitch...

- Scalar Evolution Optimization

``` c++
ScalarEvolution
```

```
opt -analyze -scalar-evolution xxx.ll
```

- LLVM intrinsics

An intrinsic function is a function built into the compiler: `llvm.xxx`.

- Vectorization: Superword-Level Parallelism(SLP), loop vectorization

```
opt -slp-vectorizer xxx.ll
```

### 6. IR to Selection DAG phase

IR => SelectionDAG => MachineDAG => MachineInstr => MCInst

DAG: Directed Acyclic Graph, LLVM uses DAG representation for code generation.

- convert IR into `SelectionDAG`

``` c++
SelectionDAGBuilder
```

- DAG combine

``` c++
DAGCombiner
```

- DAG legalization

``` c++
SelectionDAGLegalize
```

- instruction selection

``` c++
TableGen
```

- instruction scheduling

``` c++
Scheduler
```

- register allocation

mapping virtual registers to physical registers: direct mapping `TargetRegisterInfo`, `MachineOperand`; indirect mapping `VirtRegMap`

four register allocation techniques:

(1) basic register allocator
(2) fast register allocator
(3) PBQP register allocator: PBQP(Partitioned Boolean Quadratic Problem)
(4) greedy register allocator

- machine code emission: JIT, MC(Machine Code)

target machine aspects: register sets, instruction set, calling convention of functions, instruction pipeline. **tablegen** tool can generate these aspects.

``` c++
InstrEmitter
MachineInstr
MCInst
```

TOY machine:
Simple RISC-type architecture,
registers r0-r3,
a stack pointer SP,
a link register LR
a current state program register CPSR;
arguments passed to function will be stored in r0-r1, then return value will be stored in r0 (ARM thumb-like architecture).


### 7. Generating Code for Target Architecture

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Suyog Sarda, Mayur Pandey. **LLVM Essentials**. Packet Publishing: 2015.

## 其他备注

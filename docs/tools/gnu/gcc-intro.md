# Notes of **An Introduction to GCC**

|时间|内容|
|:---|:---|
|20210803|kick off.|
|20210906|add usage except chapter 7. Compiling a C++ program|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述软件的来源、特性、解决的关键性问题等. -->

## 动机

<!-- 描述阅读软件源码的动机, 要达到什么目的等. -->

## 系统结构

<!-- 描述软件的系统结构, 核心和辅助组件的结构; 系统较复杂时细分展示. -->

## 使用

<!-- 记录软件如何使用. -->

环境:

```
$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.3.0-17ubuntu1~20.04' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-9-HskZEa/gcc-9-9.3.0/debian/tmp-nvptx/usr,hsa --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
```

### 1 Introduction

介绍使用GNU C和C++编译器: `gcc`和`g++`;

#### 1.1 A brief history of GCC

GCC首次发布于1987.

#### 1.2 Major features of GCC

- 可移植的编译器;
- 不仅仅是本地(native)编译器, 还可以交叉编译(cross-compile);
- 有支持多语言的前端(frontend);
- 有模块化的设置, 允许添加新的语言和体系结构;
- 开源, 在GNU GPL下分发.

#### 1.3 Programming in C and C++

除`gcc`和`g++`外, 还支持:

- `gcl`: GNU Common Lisp
- `gst`: GNU Smalltalk
- `guile`: GNU Scheme extension language
- `gcj`: GNU Compiler for Java

#### 1.4 Conventions used in this manual

- `cc`: refer to compilers ohter than `gcc` or `g++`

### 2 Compiling a C program

source code, machine code, executable file/binary file.

#### 2.1 Compiling a simple C program

> hello.c

```
gcc -Wall hello.c -o hello

./hello
```

- `-o`: 指定机器码输出文件的名称; 未指定时默认为`a.out`;
- `-Wall`: 打开所有常用的编译器警告.

#### 2.2 Finding errors in a simple program

> bad.c

GCC产生的消息的形式: `file:line-number:column-number:message`.

#### 2.3 Compiling multiple source files

> main.c, hello.h, hello_fn.c

- `#include "FILE.h"`: 首先在当前目录中查找, 之后在系统头文件目录中查找;
- `#include <FILE.h>`: 只在系统头文件目录中查找.

```
gcc -Wall main.c hello_fn.c -o newhello
```

`hello.h`没有出现在命令行中, 因为源文件中的指令`#include "hello.h"`告知编译器在合适的地方自动导入.

#### 2.4 Compiling files independently

> main.c, hello.h, hello_fn.c

单独编译源文件, 再链接(link)它们.

- `*.o`: 对象文件(object file).
- 链接器(linker)组合目标文件来创建单个可执行文件.

##### 2.4.1 Creating object files from source files

- `-c`: 将源文件编译为目标文件.

```
$ gcc -Wall -c main.c
$ gcc -Wall -c hello_fn.c
```

##### 2.4.2 Creating executables from object files

```
$ gcc main.o hello_fn.o -o newhello
```

##### 2.4.3 Link order of object files

在`gcc`命令行中, 包含函数定义的目标文件, 应该出现在包含调用该函数的目标文件 **之后**.

> gcc hello_fn.o main.o -o newhello 也正常工作.

#### 2.5 Recompiling and relinking

> 修改main.c

```
$ gcc -Wall -c main.c
$ gcc main.o hello_fn.o -o newhello
```

通常链接比编译快. 可以使用GNU Make自动化处理项目中修改文件的重新编译.

#### 2.6 Linking with external libraries

库(library)是预编译的目标文件集合, 可以链接入程序中.

- `*.a`: 归档文件(archive file), 可以使用GNU 归档期`ar`从目标文件生成.

标准系统库目录:

- `/usr/lib`、 `/usr/lib64`
- `/lib`、 `/lib64`

```
$ gcc -Wall calc.c -lm -o calc
$ ./calc
The square root of 2.0 is 1.414214
```

- 编译器选项`-lNAME`尝试用库文件`libNAME.a`链接目标文件.

#### 2.6.1 Link order of libraries

在`gcc`命令行中, 包含函数定义的库, 必须出现在使用该函数的目标文件或源文件 **之后**.

> gcc -Wall -lm calc.c -o calc 也正常工作

调用另一个库中定义的函数的库, 应该在另一个库之前出现:

```
gcc -Wall data.c lglpk -lm
```

- `data.c`使用可GNU Linear Programming library `libglpk.a`, `libglpk.a`使用了`libm.a`.

#### 2.7 Using library header files

> badpow.c

```
$ gcc -Wall badpow.c -lm
badpow.c: In function ‘main’:
badpow.c:5:16: warning: implicit declaration of function ‘pow’ [-Wimplicit-function-declaration]
    5 |     double x = pow(2.0, 3.0);
      |                ^~~
badpow.c:5:16: warning: incompatible implicit declaration of built-in function ‘pow’
badpow.c:2:1: note: include ‘<math.h>’ or provide a declaration of ‘pow’
    1 | #include <stdio.h>
  +++ |+#include <math.h>
    2 |
```

### 3 Compilation options
#### 3.1 Setting search paths

默认情况下, `gcc`的搜索路径:

- 头文件: `/usr/local/include`、`/usr/include` - 包含路径(include path)
- 库文件: `/usr/local/lib`、`/usr/lib` - 库搜索路径(library search path)/链接路径(link path)
- 多个目录, 则按从左往右顺序进行搜索.

编译器选项:

- `-I`: 添加新目录到包含路径的头部;
- `-L`: 添加新目标到库搜索路径的头部.

##### 3.1.1 Search path example

> dbmain.c

```
$ gcc -Wall -I/usr/include -L/usr/lib/x86_64-linux-gnu dbmain.c -lgdbm -o dbmain
$ ./dbmain
Storing key-value pair... done.
```

##### 3.1.2 Environment variables

使用环境变量将目录添加到包含目录搜索路径中:

- `C_INCLUDE_PATH`: C头文件.
- `CPLUS_INCLUDE_PATH`: C++头文件.
- 这些目录在使用选项`-I`之后, 标准默认目录之前, 被执行搜索.

```
$ C_INCLUDE_PATH=/usr/include
$ export C_INCLUDE_PATH
```

将目标添加到库搜索路径中:

- `LIBRARY_PATH`

```
$ LIBRARY_PATH=/usr/lib/x86_64-linux-gnu
$ export LIBRARY_PATH
```

这时可以不指定`-I`和`-L`选项:

```
$ gcc -Wall dbmain.c -lgdbm -o dbmain
```

##### 3.1.3 Extended search paths

环境变量中多个目录:

```
DIR1:DIR2:DIR3:...
```

- `.`: 表示当前目录.

```
$ C_INCLUDE_PATH=.:/usr/include:/net/include
$ LIBRARY_PATH=.:/usr/lib/x86_64-linux-gnu:/net/lib

$ gcc -I. -I/usr/include -I/net/include -L. -L/usr/lib/x86_64-linux-gnu -L/net/lib ......
```

当同事使用环境变量和命令行选项时, 编译器的搜索顺序:

1. 命令行选项`-I`和`-L`, 从左往右;
2. 环境变量指定的目录: `C_INCLUDE_PATH`, `LIBRARY_PATH`;
3. 默认系统目录.

#### 3.2 Shared libraries and static libraries

- `*.so`: 共享对象.
- 动态链接(dynamic linking).

```
$ find /usr/ | grep gdbm
/usr/lib/x86_64-linux-gnu/libgdbm_compat.so.4.0.0
/usr/lib/x86_64-linux-gnu/libgdbm.so.6.0.0
/usr/lib/x86_64-linux-gnu/libgdbm.a
/usr/lib/x86_64-linux-gnu/libgdbm_compat.so.4
/usr/lib/x86_64-linux-gnu/libgdbm.so.6
/usr/lib/x86_64-linux-gnu/libgdbm.so
```

`-static`选项告知`gcc`避免使用共享库:

```
$ gcc -Wall -I/usr/include -L/usr/lib/x86_64-linux-gnu dbmain.c -lgdbm -o dbmain
$ ldd dbmain
        linux-vdso.so.1 (0x00007fff3d3b5000)
        libgdbm.so.6 => /lib/x86_64-linux-gnu/libgdbm.so.6 (0x00007f11169f3000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f1116801000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f1116a1d000)
$ gcc -Wall -static -I/usr/include -L/usr/lib/x86_64-linux-gnu dbmain.c -lgdbm -o dbmain
$ ldd dbmain
        not a dynamic executable
```

直接指定静态库`libgdbm.a`或动态库`libgdbm.so`:

```
$ gcc -Wall dbmain.c /usr/lib/x86_64-linux-gnu/libgdbm.a -o dbmain
$ file dbmain
dbmain: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=6cc09ecc02ac4850614951161ab7a5565acf2756, for GNU/Linux 3.2.0, not stripped
$ ldd dbmain
        linux-vdso.so.1 (0x00007fff6d4d6000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc572eef000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fc573101000)


$ gcc -Wall dbmain.c /usr/lib/x86_64-linux-gnu/libgdbm.so -o dbmain
$ file dbmain
dbmain: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=fc7c456c6a9c9ab8d9a5bffe691575fe1bd603e0, for GNU/Linux 3.2.0, not stripped
$ ldd dbmain
        linux-vdso.so.1 (0x00007ffe53d0f000)
        libgdbm.so.6 => /lib/x86_64-linux-gnu/libgdbm.so.6 (0x00007fdeca579000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fdeca387000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fdeca5a3000)
```


#### 3.3 C language standards

默认情况下, `gcc`编译程序时使用C语言的GNU方言GNU C, 在C语言的ANSI/ISO标准上加了一些诸如嵌套函数、变长数组等扩展.

控制C语言方言的选项: `-ansi`、`-pedantic`、`-std`.

##### 3.3.1 ANSI/ISO

> ansi.c

`-ansi`关闭与ANSI/ISO标准冲突的GNU扩展, 同时也关闭`glibc`中对C标准库的扩展.

GNU C的关键字扩展: `asm`、`inline`、`typeof`、`unix`、`vax`.

GNU C库提供了一些特性测试宏(feature test macros):

- `_POSIX_C_SOURCE`: POSIX扩展;
- `_BSD_SOURCE`: BSD扩展;
- `_SVID_SOURCE`: SVID扩展;
- `_XOPEN_SOURCE`: XOPEN扩展;
- `_GNU_SOURCE`: GNU扩展, 包含上述扩展, 有冲突时优先采用POSIX扩展.

> pi.c

使用`-ansi`:

```
$ gcc -Wall -ansi pi.c
pi.c: In function ‘main’:
pi.c:6:39: error: ‘M_PI’ undeclared (first use in this function)
    6 |     printf("the value of pi is %f\n", M_PI);
      |                                       ^~~~
pi.c:6:39: note: each undeclared identifier is reported only once for each function it appears in
```

不使用`-ansi`:

```
$ gcc -Wall pi.c -o pi
$ ./pi
the value of pi is 3.141593
```

使用`-ansi`, 同时使用`_GNU_SOURCE`开启GNU C库扩展:

```
$ gcc -Wall -ansi -D_GNU_SOURCE pi.c -o pi
$ ./pi
the value of pi is 3.141593
```

##### 3.3.2 Strict ANSI/ISO

> gnuarray.c

`-pedantic`与`-ansi`一起使用时, `gcc`会拒绝所有的GNU C扩展.

##### 3.3.3 Selecting specific standards

- `-std=c89`、`-std=iso9899:1990`
- `-std=iso9899:199409`
- `-std=c99`、`-std=iso9899:1999`
- `-std=gnu89`
- `-std=gnu99`

#### 3.4 Warning options in `-Wall`

- `-Wcomment`: 警告内嵌注释;
- `-Wformat`: 警告`printf`、`scanf`等函数中格式化字符串的错误使用;
- `-Wunused`: 警告未使用的变量;
- `-Wimplicit`: 警告函数未声明但被使用;
- `-Wreturn-type`: 警告函数定义没有返回类型但未声明为`void`.

#### 3.5 Additional warning options

- `-W`: 类似于`-Wall`的通用选项, 包括函数可以无值返回、有符号值与无符号值比较等;
- `-Wconversion`: 警告导致未期望值的隐式类型转换;
- `-Wshadow`: 警告在作用域汇总重新声明了已声明的变量;
- `-Wcast-qual`: 警告指针转换移除了诸如`const`的类型限定符.
- `-Wwrite-strings`: 隐式的给所有字符串常量一个`const`限定符.
- `-Wtraditional`: 警告部分代码会被ANSI/ISO编译器或传统的pre-ASNI编译器产生不同解释;
- `-Werror`: 将警告转为错误, 警告发生时停止编译.

### 4 Using the preprocessor

`cpp`: GNU C预处理器(preprocessor). 在编译源文件之前, 展开源文件中的宏(macro).

#### 4.1 Defining macros

> dtest.c

`-DNAME`: `gcc`选项, 从命令行中定义预处理器宏`NAME`.

一些由编译器自动定义的宏有前缀`__`, 查看所有预定义宏:

```
$ cpp -dM /dev/null
#define __SSP_STRONG__ 3
#define __DBL_MIN_EXP__ (-1021)
#define __FLT32X_MAX_EXP__ 1024
#define __UINT_LEAST16_MAX__ 0xffff
#define __ATOMIC_ACQUIRE 2
```

#### 4.2 Macros with values

> dtestval.c

```
-DNUM=1000
-DNUM="2+2"
-DNUM
-DNAME=""
-DMESSAGE="\"Hello, World!\""
```

只用`-D`定义的宏(例如`-DNUM`), `gcc`使用默认值`1`.

#### 4.3 Preprocessing source files

> test.c

使用`gcc`的`-E`选项查看预处理器的处理结果.

```
$ gcc -E test.c
# 1 "test.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "test.c"

const char str[] = "Hello, World!";
```

> hello.c

使用`-save-temps`可以保存`*.i`、`*.o`和`*.s`等临时文件.

### 5 Compiling for debugging

`-g`调试选项在目标文件和执行体中存储了额外的调试信息: 将函数和变量名称、所有它们的引用、它们相应的源代码中行号, 存储在目标文件和执行体的符号表中.

GNU调试器`gdb`.

#### 5.1 Examining core files

`core`文件: 组合`-g`在符号表中产生的信息, 可用于定位程序停止的行号和相关变量的值.

#### 5.2 Displaying a backtrace

调试器可以显示到当前执行点的函数调用和参数, 即栈回溯(stack backtrace):

```
(gdb) backtrace
#0  0x0000555555555162 in a (p=0x0) at null.c:11
#1  0x0000555555555150 in main (argc=1, argv=0x7fffffffdeb8) at null.c:6
```

### 6 Compiling with optimization
#### 6.1 Source-level optimization
##### 6.1.1 Common subexpression elimination

通用子表达式消除.

``` c
x = cos(v)*(1+sin(u/2)) + sin(w)*(1-sin(u/2))
```

=>

``` v
t = sin(u/2)
x = cos(v)*(1+t) + sin(w)*(1-t)
```

##### 6.1.2 Function inlining

函数内联.

``` c
double sq(double x)
{
  return x * x;
}

for (i = 0; i < 1000000; i++)
{
  sum += sq(i + 0.5);
}
```

=>

``` c
for (i = 0; i < 1000000; i++)
{
  double t = (i + 0.5); // 临时变量
  sum += t * t;
}
```

`inline`关键字显示要求编译器尽量将函数内联.

#### 6.2 Speed-space tradeoffs

权衡: 执行体的执行速度、执行体的大小.

##### 6.2.1 Loop unrolling

循环展开(loop unrolling).

#### 6.3 Scheduling

调度(scheduling): 确定独立指令的顺序.

#### 6.4 Optimization levels

- `-O0`: 不执行优化;
- `-O1`: 打开常见形式的优化;
- `-O2`: 在`-O1`基础上打开更多优化, 例如指令调度;
- `-O3`: 在`-O2`基础上打开更多优化, 例如函数内联;
- `-funroll-loops`: 打开循环展开优化;
- `-Os`: 选择减少执行体大小的优化.

#### 6.5 Examples

> test.c

#### 6.6 Optimization and debugging

GCC允许组合使用优化和调试选项`-g`.

#### 6.7 Optimization and compiler warnings

> uninit.c

数据流分析(data-flow analysis)例: 变量初始化和变量使用. `-Wuninitialized`选项警告使用了未初始化的变量, 只在开发工作流分析的优化时工作.

### 7 Compiling a C++ program - TODO
#### 7.1 Compiling a simple C++ program
#### 7.2 Using the C++ standard library
#### 7.3 Templates
##### 7.3.1 Using C++ standard library templates
##### 7.3.2 Providing your own templates
##### 7.3.3 Explicit template instantiation
##### 7.3.4 The export keyword

### 8 Platform-specific options

GCC为不同类型的CPU提供了多个特定于平台的选项. 这些选项控制诸如硬件浮点模式、使用不同CPU的特殊指令等. 通过`-m`选项指定.

#### 8.1 Intel and AMD x86 options

- `-march=CPU`: 对特定处理器的支持;
- `-mcpu=CPU`: 速度与可移植性的折中;
- `-m32`: 生成32位代码;
- `-mcmmodel`: 指定内存模型.

#### 8.2 DEC Alpha options - SKIP
#### 8.3 SPARC options - SKIP
#### 8.4 POWER/PowerPC options - SKIP
#### 8.5 Multi-architecture support

一些平台支持执行多个体系结构的代码, 例如AMD64、MIPS64、Sparc、和PowerPC64同时执行32位和64位的代码. 在这些平台上, 可以构建GCC支持多个体系结构.

支持多个体系结构依赖于相应的库可用.

### 9 Troubleshooting
#### 9.1 Help for command-line options

```
$ gcc --help
$ gcc -v --help
$ gcc -v --help 2>&1 | more
```

#### 9.2 Version numbers

```
$ gcc --version
$ gcc -v
```

#### 9.3 Verbose compilation

```
$ gcc -v -Wall hello.c
```

### 10 Compiler-related tools

- `ar`: GNU archiver
- `gprof`: GNU profiling program
- `gcov`: GNU coverage testing program

#### 10.1 Creating a library with the GNU archiver

> hello.h, hello_fn.c, bye_fn.c, main.c

#### 10.2 Using the profiler gprof

> collatz.c

$$
x_{n+1} \leftarrow \begin{cases}
x_{n} / 2 & \texttt{ if } x_{n} \texttt{ is even}\\
3x_{n} + 1 & \texttt{ if } x_{n} \texttt{ is odd}
\end{cases}
$$

- `-pg`选项: 需要使用profiler时, 在编译和链接时使用.

#### 10.3 Coverage testing with gcov

```
$ gcc -Wall -fprofile-arcs -ftest-coverage cov.c
$ gcov cov.c
$ cat cov.c.gcov
```

- `-ftest-coverage`: 添加每行代码执行次数计数的指令;
- `-fprofile-arcs`: 协调程序每个分支的instrumentation代码.

### 11 How the compiler works

> hello.c

#### 11.1 An overview of the compilation process

- preprocessing: 展开宏;
- compilation: 从源代码生成汇编语言代码;
- assembly: 从汇编语言代码生成机器码代码;
- linking: 创建执行体.

#### 11.2 The preprocessor

```
$ cpp hello.c > hello.i
```

#### 11.3 The compiler

```
$ gcc -Wall -S hello.i
```

#### 11.4 The assembler

```
$ as hello.s -o hello.o
```

#### 11.5 The linker

```
$ gcc -v hello.o
```

### 12 Examining compiled files

> hello.c

#### 12.1 Identifying files

```
$ file hello
```

#### 12.2 Examining the symbol table

```
$ nm hello
```

#### 12.3 Finding dynamically linked libraries

```
$ ldd hello
```

### 13 Getting help - SKIP

### Further reading

- Using GCC
- Debugging with GDB: The GNU Source-Level Debugger
- GNU Make: A Program for Directing Recompilation
- The GNU C Library Reference Manual

## 数据结构和算法

<!-- 描述软件中重要的数据结构和算法, 支撑过程部分的记录. -->

## 过程

<!-- 描述软件中重要的过程性内容, 例如服务器的启动、服务器响应客户端请求、服务器背景活动等. -->

## 文献引用

<!-- 记录软件相关和进一步阅读资料: 文献、网页链接等. -->

- Brian Gough. **An Introduction to GCC**. 2004.

## 其他备注

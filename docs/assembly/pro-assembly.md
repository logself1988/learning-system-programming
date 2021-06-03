# Notes of Professional Assembly Language


|时间|内容|
|:---|:---|
|20191228|add 背景知识, 程序基本结构, 数据指令.|
|20200102|add 传送数据, 控制执行流程.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. 什么是汇编语言
#### 1.1 处理器指令
#### 1.2 高级语言
#### 1.3 汇编语言

### 2. IA-32平台
#### 2.1 IA-32处理器的核心部分

> IA-32 Volume 1 - 3.4. BASIC PROGRAM EXECUTION REGISTERS

IA32寄存器组:

|名称|数量|说明|
|:---|:---|:---|
|通用     | 8个32位寄存器:<br/> EAX, EBX, ECX, EDX, EDI, ESI, ESP, EBP | 存储正在处理的数据|
|段       | 6个16位寄存器:<br/> CS, DS, SS, ES, FS, GS  | 处理内存访问|
|指令指针 | 1个32位寄存器: EIP | 指向要执行的下一条指令码|
|浮点数据 | 8个80位寄存器 | 用于浮点数学数据|
|控制     | 5个32位寄存器:<br/> CR0, CR1, CR2, CR3, CR4 | 用于确定处理器的操作模式|
|调试     | 8个32位寄存器  | 用于在调试处理器时包含信息|

- 通用寄存器

|名称|说明|
|:---|:---|
|EAX  | 用于操作数和结果数据的累加器|
|EBX  | 指向数据内存段中的数据的指针|
|ECX  | 字符串和循环操作的计数器|
|EDX  | I/O指针|
|EDI  | 用于字符串操作的目标的数据指针|
|ESI  | 用于字符串操作的源的数据指针|
|ESP  | 堆栈指针|
|EBP  | 堆栈数据指针|

- 段寄存器

|名称|说明|
|:---|:---|
|CS   | 代码段|
|DS   | 数据段|
|SS   | 堆栈段|
|ES   | 附加段指针|
|FS   | 附加段指针|
|GS   | 附加段指针|


- 控制寄存器

|名称|说明|
|:---|:---|
|CR0  | 控制操作模式和处理器状态的系统标志|
|CR1  | 当前没有使用|
|CR2  | 内存页面错误信息|
|CR3  | 内存页面目录信息|
|CR4  | 支持处理器特性和说明处理器特性能力的标志|


- 标志

IA32平台使用1个32位的寄存器保存状态：EFLAGS寄存器

(1) 状态标志

|名称|位|说明|备注|
|:---|:---|:---|:---|
|CF   | 0   | 进位标志(Carray)      | 无符号整数值的数学操作最高有效位的进位或者借位，置1|
|PF   | 2   | 奇偶校验标志(Parity)  | 结果中1的个数为偶数时置1|
|AF   | 4   | 辅助进位标志          | 寄存器中第3位进位或借位时置1|
|ZF   | 6   | 零标志(Zero)          | 结果为0时置1|
|SF   | 7   | 符号标志(Sign)        | 结果的最高有效位|
|OF   | 11  | 溢出标志(Overflow)    | 正值过大、负值过小|

(2) 控制标志

|名称|位|说明|
|:---|:---|:---|
|DF   | 10  | 置1字符串指令自动递减内存地址，以到达字符串的下一个字节，置0则递增|

(3) 系统标志

用于控制操作系统级别的操作，应用程序不应该试图修改系统标志

|名称|位|说明|
|:---|:---|:---|
|TF   | 8       | 陷阱标志 |
|IF   | 9       | 中断使能标志 |
|IOPL | 12, 13  | I/O特权级别标志 |
|NT   | 14      | 嵌套任务标志 |
|RF   | 16      | 恢复标志 |
|VM   | 17      | 虚拟8086模式比阿志 |
|AC   | 18      | 对准检查标志 |
|VIF  | 19      | 虚拟中断标志 |
|VIP  | 20      | 虚拟中断挂起标志 |
|ID   | 21      | 识别标志 |

#### 2.2 IA-32的高级特性

(1) x87浮点单元(FPU, floating-point unit)

FPU寄存器:

- 数据寄存器: 用于浮点数据的8个80位寄存器;
- 状态寄存器: 报告FPU状态的16位寄存器;
- 控制寄存器: 控制FPU精度的16位寄存器;
- 标记寄存器: 描述8个数据寄存器内容的16位寄存器;
- FIP寄存器: 指向下一条FPU指令的48位FPU指令指针(FPU instruction pointer);
- FDP寄存器: 指向内存中的数据的48位FPU数据指针(FPU data pointer);
- 操作码寄存器: 保存FPU处理的最后指令的11位寄存器.


(2) 多媒体扩展(multimedia extension, MMX): 是支持Intel的SIMD(Single Instruction, Multiple Data, 单指令多数据)执行模型的第一种技术.

(3) 流化SIMD扩展(Streaming SIMD extension, SSE): 增强了经常用于3D图形、动态视频等复杂浮点算术运算的性能.

(4) 超线程(hyperthreading): 使单一IA-32处理器能够同时处理多个程序执行线程.

#### 2.3 IA-32处理器系列

### 3. 相关的工具

- [Documentation for binutils 2.33.1](https://sourceware.org/binutils/docs/)

```
$ gcc --version
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

$ as --version
GNU assembler (GNU Binutils for Ubuntu) 2.34

$ ld --version
GNU ld (GNU Binutils for Ubuntu) 2.34

$ gdb --version
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
```

#### 3.1 开发工具
#### 3.2 GNU汇编器 as


如果没有特殊说明, 这里使用 **AT&T操作码语法**.

- 使用`$`表示立即操作数, 例如`$4`;
- 在寄存器的名称上加上前缀`%`, 例如`%eax`;
- 源操作数与目标操作数的顺序: `INSTRUCTION source, destination`, 例如`movl $4, %eax`;
- 在助记符后面使用一个字符来引用操作中使用的数据长度, 例如`movl $test, %eax`中的`movl`;
- 长调用和跳转 `ljmp $section, $offset`.

#### 3.3 GNU连接器 ld
#### 3.4 GNU编译器 gcc

#### 3.5 GNU调试程序 gdb

```
as -gstabs -o cpuid.o cpuid.s
ld -o cpuid cpuid.o
gdb cpuid
```

```
(gdb) bread *_start
(gdb) s
(gdb) run
(gdb) n
(gdb) print $eax
(gdb) info registers
(gdb)
```

查看寄存器和内存信息:

(1) info registers: 显示所有寄存器中的值

(2) print: 显示特定寄存器或程序中变量的值

```
print/d 显示十进制值
print/t 显示二进制值
print/x 显示十六进制值

print/x $ebx
print/s &output
```

(3) x: 显示特定内存位置的内容

```
x/nyz

n: 要显示的字段数
y: 输出格式
      c 字符
      d 十进制
      x 十六进制
      s 字符串
      f 浮点数
z: 要显示的字段长度
      b 字节
      h 16位字（半字）
      w 32位字 - 未指定时默认长度

x/s 0xbff59b59
x/s &output
```

#### 3.6 KDE调试器
#### 3.7 GNU objdump程序
#### 3.8 GNU简档器程序 gprof
#### 3.9 完整的汇编开发系统

使用Linux操作系统.

### 4. 汇编语言程序范例

#### 4.1 程序的组成


``` asm
.section .data
     # put data with init value here

.section .bss
     # put data without init value here

.section .text
.globl _start
_start:
     # put code here
```

#### 4.2 创建简单程序

```
## cpuid.s中使用.globl _start
as -o cpuid.o cpuid.s
ld -o cpuid cpuid.o
```

```
## cpuid.s中使用.globl main
gcc -s cpuid.s -o cpuid
```

#### 4.3 调试程序
#### 4.4 在汇编语言中使用C库函数

```
ld -dynamic-linker /lib/ld-linux.so.* -o PROGRAM -lc PROGRAM.o
```

### 5. 传送数据

#### 5.1 定义数据元素

- .rodata数据段

该段定义的数据元素只能按照只读模式访问.

- .data数据段

在这个段中声明的任何数据元素都保留在内存中, 可以被汇编语言程序中的指令读取和写入.

在数据段中定义数据元素需要两个语句: 一个标签和一个命令. 声明命令后必须定义一个或多个默认值.

命令:

`.ascii`      文本字符串<br/>
`.asciz`      以空字符结尾的文本字符串<br/>
`.byte`       字节值(1B)<br/>
`.short`      2B整数<br/>
`.int`, `.long`  4B整数<br/>
`.quad`       8B整数
`.octa`       16B整数<br/>
`.double`, `.float`, `.single`      （双/单/单）精度浮点数(8B/4B/4B)<br/>


``` asm
.section .data
msg:                                # 标签: 定义内存位置
  .ascii "This is a test message"   # 命令和默认值
factors:
  .double 37.45, 45.33, 12.30
height:
  .int 54
length:
  .int 62, 25, 47
```

静态数据符号(`.equ`)：

``` asm
.section .data
.equ factor, 3
.equ LINUX_SYS_CALL, 0x80

movl $LINUX_SYS_CALL, %eax    # 引用
```

填充(`.fill`)创建指定数量的数据元素, 每个元素一个字节, 且使用零填充:

``` asm
.section .data
buffer:
  .fill 10000
```

- .bss段

该段声明的数据元素不包含在可执行程序中.

`.comm symbol length` 未初始化的数据的通用内存区域<br/>
`.lcomm symbol length` 未初始化的数据的 **本地** 通用内存区域

``` asm
.section .bss
.lcomm buffer, 10000
```

#### 5.2 传送数据元素

``` asm
movx source, destination
```

- `x`: `l` 32位, `w` 16位, `b` 8位;
- `source`, `destination`: 内存地址、存储在内存中的数据值、指令语句中定义的数据值、寄存器.

源操作数与目标操作数的组合:

```
立即操作数 -> 通用寄存器, 内存位置
通用寄存器 -> 另一个通用寄存器, 段寄存器, 控制寄存器, 调试寄存器, 内存位置
段寄存器   -> 通用寄存器, 内存位置
控制寄存器 -> 通用寄存器
调试寄存器 -> 通用寄存器
内存位置   -> 通用寄存器, 段寄存器
```

``` asm
movl $0, %eax             # 立即操作数 -> 通用寄存器
movl $0x80, %ebx
movl $100, height         # 立即操作数 -> 内存位置

movl %eax, %ecx           # 通用寄存器 -> 通用寄存器
movw %ax, %cx
```

在内存和寄存器之间传送数据:


使用内存位置的数据值:

``` asm
.section .data
value:
  .int 1
values:
  .int 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60
output:
  .asciz "The value is %d\n"

movl value, %eax                  # 内存位置 -> 寄存器, 使用标签(1)            

movl $100, %eax
movl %eax, value                  # 寄存器 -> 内存位置

movl $2, %edi
movl values(, %edi, 4), %eax      # 内存位置 -> 寄存器, 使用变址的内存位置(2)

movl $values, %edi                # 将标签引用的内存地址传送到寄存器中
movl %ebx, (%edi)                 # 寄存器 -> 内存位置, 使用寄存器间接寻址(3)
movl %edx, 4(%edi)                # EDI寄存器指向的位置之后4个字节的内存位置
movl %edx, -4(%edi)               # EDI寄存器指向的位置之前4个字节的内存位置
```

(1) 使用标签

(2) 使用变址的内存位置: 变址内存模式(indexed memeory mode)

```
base_address (offset_address, index, size)
```

- `base_address`: 基址;
- `offset_address`: 添加到基址上的偏移地址, 必须是寄存器;
- `index`: 数据元素的索引(变址), 必须是寄存器;
- `size`: 数据元素的长度;
- `offset_address`、`index`、`size`的任何值为零则可以忽略, 但需要保留逗号占位符;
- 获取的数据值的内存位置: `base_address + offset_address + index * size`

(3) 使用寄存器间接寻址(indirect addressing)

指针(pointer): 寄存器保存内存地址.

- 获取数据值的内存位置的地址: `movl $values %edi`;
- 通过指针存储值(将值传送到寄存器中包含的内存位置): `movl %ebx, (%edi)`.

#### 5.3 条件传送指令

``` asm
cmovx source, destination
```

`x`: 表示触发传送操作的条件, 这些条件取决于EFLAGS寄存器的当前值: CF, OF, PF, SF, ZF.

无符号时的`x`:

- A, NBE: 大于               ((CF或ZF)=0)
- AE, NB: 大于等于           (CF=0)
- NC:     无进位             (CF = 0)
- B, AE:  小于               (CF=1)
- C:      进位               (CF=1)
- BE, NA: 小于等于           ((CF或ZF)=1)
- E, Z:   等于, 零           (ZF=1)
- NE, NZ: 不等于, 非零       (ZF=0)
- P, PE:  奇偶校验, 偶校验   (PF=1)
- NP, PO: 非奇偶校验, 奇校验 (PF=0)

有符号时的`x`:

- GE, NL: 大于等于           ((SF异或OF)=0)
- L, NGE: 小于               ((SF异或OF)=1)
- LE, NG: 小于等于           (((SF异或OF)或ZF)=1)
- O:      溢出               (OF=1)
- NO:     未溢出             (OF=0)
- S:      带符号(负)         (SF=1)
- NS:     无符号(非负)       (SF=0)

#### 5.4 交换数据

- XCHG指令

在两个通用寄存器之间或者寄存器与内存位置之间交换数据值.

``` asm
xchg operand1, operand2
```

注意: 当一个操作数是内存位置时, 处理器使用LOCK信号, 比较耗时.

- BSWAP指令

翻转一个32位寄存器中的字节顺序: 0-7位域24-31位交换, 8-15位与16-32w位交换.

``` asm
bswap register
```

- XADD指令

交换两个寄存器或者内存位置与寄存器的值, 将两个值相加的结果存储在目标位置(寄存器或者内存位置).

``` asm
xadd source, destination
```

`source`必须是寄存器. 寄存器可以是8位、16位或32位.

- CMPXCHG指令

``` asm
cmpxchg source, destination
```

比较目标操作数与EAX、AX、AL寄存器中的值:

如果相等, 将源操作数的值加载到目标操作数中;<br/>
如果不相等, 将目标操作符加载到EAX、AX、AL寄存器中.

`destination`可以是8位、16位、32位的寄存器, 或者内存位置; `source`必须是长度和目标操作数匹配的寄存器.

- COMPXCHG8B指令

```
cmpxchg8b destination
```

与CMPXCHG指令类似, 但处理8字节值.

`destination`引用一个内存位置, 其中的8字节值会与`EDX:EAX`的值进行比较:

如果相等, 将`ECX:EBX`的值传送给目标内存位置;<br/>
如果不相等, 将`destination`中的值加载到`EDX:EAX`中.


```
as -gstabs -o test_cmpxchg8b.o test_cmpxchg8b.s
ld -o test_cmpxchg8b test_cmpxchg8b.o
gdb test_cmpxchg8b
```

```
(gdb) break *_start
Breakpoint 1 at 0x4000b0: file test_cmpxchg8b.s, line 8.
(gdb) run
Starting program: /home/zhoujiagen/assembly/example/transfer_data/test_cmpxchg8b

Breakpoint 1, _start () at test_cmpxchg8b.s:8
8	  movl $0x44332211, %eax
(gdb) x/8xb &data
0x6000d8:	0x11	0x22	0x33	0x44	0x55	0x66	0x77	0x88
(gdb) x/2xw &data
0x6000d8:	0x44332211	0x88776655
(gdb) s
9	  movl $0x88776655, %edx
(gdb) s
10	  movl $0x11223344, %ebx
(gdb) s
11	  movl $0x55667788, %ecx
(gdb) s
13	  cmpxchg8b data
(gdb) s
15	  movl $1, %eax
(gdb) x/8xb &data
0x6000d8:	0x44	0x33	0x22	0x11	0x88	0x77	0x66	0x55
(gdb) x/2xw &data
0x6000d8:	0x11223344	0x55667788
```

#### 5.5 堆栈

``` asm
pushx source
popx destination
```

- `x`: `l` 32位, `w` 16位;
- `source`: 16/32位寄存器值, 16/32位内存值, 8/16/32位立即数值
- `destination`: 16/32位寄存器, 16位段寄存器, 16/32位内存位置
- 数据段从最低的内存位置开始, 向更高的内存位置依次存放;
- 堆栈被保留在内存区域的末尾位置, 当数据存放在堆栈中时, 向下增长.

使用ESP寄存器作为内存指针, 手工的把数据存放在堆栈中.

#### 5.6 优化内存访问

### 6. 控制执行流程

#### 6.1 指令指针
#### 6.2 无条件分支

##### 跳转

``` asm
jmp location
```

- `location`: 要跳转到的内存地址, 是程序代码中的标签

##### 调用

``` asm
call address
ret
```

- `address`: 引用程序中的标签

> IA64 Volume 1 - 6.2.5 Stack Behavior in 64-Bit Mode
>
> Registers E(SP), E(IP) and E(BP) are promoted to 64-bits and are re-named RSP, RIP, and RBP respectively. Some forms of segment load instructions are invalid (for example, LDS, POP ES).


##### 中断

Linux `0x80`中断.

#### 6.3 条件分支

条件分支的结果取决于执行分支时EFLAGS寄存器的状态:

- CF
- OF
- PF
- SF
- ZF

条件跳转指令:

``` asm
jxx address
```

> need more details here!!!

比较指令

``` asm
cmp operand1, operand2
```

- 执行operand2-operand1, 设置EFLAGS寄存器.


#### 6.4 循环

``` asm
loop address

loope address
loopz address

loopne address
loopnz address
```

- `address`: 要跳转到的程序代码位置的标签名称;
- `loop`: 循环直到ECX寄存器为0;
- `loope`、`loopz`: 循环直到ECX寄存器为0, 或者没有设置ZF标志;
- `loopne`、`loopnz`: 循环直到ECX寄存器为0, 或者设置了ZF标志;
- 递减ECX寄存器的值, 但不影响EFLAGS寄存器的标志位.

#### 6.5 模仿高级条件分支
#### 6.6 优化分支指令

### 7. 使用数字

#### 7.1 数字数据类型
#### 7.2 整数
#### 7.3 SIMD整数
#### 7.4 二进制编码的十进制
#### 7.5 浮点数
#### 7.6 转换

### 8. 基本数学功能
#### 8.1 整数运算
#### 8.2 移位指令
#### 8.3 十进制运算
#### 8.4 逻辑运算

### 9. 高级数学功能
#### 9.1 FPU环境
#### 9.2 基本浮点运算
#### 9.3 高级浮点运算
#### 9.4 浮点条件分支
#### 9.5 保存和恢复FPU状态
#### 9.6 等待和非等待指令
#### 9.7 优化浮点运算

### 10. 处理字符串
#### 10.1 传送字符串
#### 10.2 存储和加载字符串
#### 10.3 比较字符串
#### 10.4 扫描字符串


### 11. 使用函数
#### 11.1 定义函数

当应用程序汇总需要相同的代码时, 不必多次重新编写代码, 最好创建包含代码的单一函数, 然后在程序中的任意位置调用该函数.

数据从主程序传递给函数, 然后结果返回给主程序.

#### 11.2 汇编函数

在汇编语言中创建函数需要三个步骤:

(1) 定义输入值: 使用寄存器、使用全局变量、使用堆栈.

(2) 定义函数处理: 函数被编写为程序汇总的一般汇编语言代码; GNU汇编器中例:

``` asm
.type func1, @function
.func1:
```

函数的结束由`RET`指令定义. 执行到`RET`指令时, 程序控制返回主程序, 返回的位置是紧跟在`CALL`指令后面的指令.

(3) 定义输出值: 把结果存放在一个或者多个寄存器中、把结果存放在全局变量内存位置中.


访问函数: `CALL`指令用于把控制从主程序传递到函数.

```
call func1
```

函数的放置:

- 不必在主程序中调用函数之前定义函数;
- `CALL`指令会查找函数开始的标签来获取指令指针.

使用寄存器:

- 如果被调用的函数修改主程序使用的寄存器, 则需要在调用函数之前保存寄存器的状态, 并且在函数返回之后恢复寄存器的状态;
- 在调用函数之前, 使用`PUSH`指令单独保存特定寄存器的状态, 使用`PUSHA`指令保存所有寄存器的状态;
- 使用`POP`指令单独的恢复寄存器的原始状态, 使用`POPA`指令恢复所有寄存器的状态;
- 如果函数返回值存放在寄存器中, 在恢复原始寄存器之前, 必须把它传送到安全位置.

使用全局数据:

- 函数可以访问主程序中定义的内存位置(全局变量), 可以将其用于在主程序和函数之间传递数据.

#### 11.3 按照C样式传递数据值

C样式传递数据值:

- 传递输入值给函数: 使用堆栈;
- 返回值到主程序: EAX用于32位结果, EDX:EAX用于64位结果, FPU的ST(0)寄存器用于浮点数.

```
          -------------------                 high address
          |                 |
          |                 |   间接寻址
          -------------------
          |    函数参数3     |   16(%ebp)
          -------------------
          |    函数参数2     |   12(%ebp)
          -------------------
          |    函数参数1     |   8(%ebp)
          -------------------
ESP0  ->  |    返回地址      |    4(%ebp)
          -------------------
ESP1  ->  |    旧的EBP值     |    (%ebp)
          -------------------
          |    局部变量1     |   -4(%ebp)
          -------------------
          |    局部变量2     |   -8(%ebp)
          -------------------
ESP2  ->  |    局部变量3     |   -12(%ebp)
          -------------------                  low address
```

- C样式要求函数参数存放到堆栈中的顺序与函数原型中的顺序相反;
- `ESP0`: 执行`CALL`指令时, 它吧发出调用的程序的返回地址也存放到堆栈顶部;
- 间接寻址: 把值弹出堆栈以获得输入参数, 可能会导致返回地址在处理过程中丢失; 根据ESP寄存器使用间接寻址的方式访问输入参数, 不必把值弹出堆栈;
- `ESP1`: 函数处理中可能包含把数据压入堆栈的操作, 会改变ESP堆栈指针的位置; 为避免该问题, 进入函数时, 将EBP寄存器的值压入堆栈, 把ESP寄存器复制到EBP寄存器;
- `ESP2`: 在堆栈中定义函数中局部变量, 可以根据EBP间接寻址引用它们; 如果函数中将任何数据压入堆栈, 会覆盖这些局部变量; 通过从ESP寄存器减去一个值, 为局部变量保留一定数量的堆栈空间.

``` asm
function:
  pushl %ebp        # ESP1, 将EBP寄存器的值压入堆栈
  movl %esp, %ebp   # 把ESP寄存器复制到EBP寄存器
  subl $12, %esp    # 为局部变量保留12字节
  ...
  movl %ebp, %esp   # 恢复ESP
  popl %ebp         # 弹出EBP寄存器的值
  ret
```

清空堆栈:

- 调用函数之前, 发出调用的函数把所有必须的输入值存放到堆栈中;
- 函数返回时, 这些值仍在堆栈中.
- 如果主程序使用堆栈进行其他操作, 会希望从堆栈中删除旧的输入值, 以便使得堆栈恢复到函数调用之前的状态.
- 可以使用`POP`指令完成; 也可以使用`ADD`指令将ESP堆栈指针移动回函数调用之前的原始位置.

``` asm
pushl %eax
pushl %ebx
call compute
addl $8, %esp   # 将数据清除出堆栈
```


#### 11.4 使用独立的函数文件

在自包含的函数文件中, 必须把函数名称声明为全局标签, 以便其他程序能够访问它, 例:

``` asm
# ares.s

.section .text
.type area, @function
.globl area
area:
  # put codes here
```

#### 11.5 使用命令行参数

程序运行时, Linux将这些信息存放在程序堆栈中:

- 命令行参数的数目;
- 从shell中执行的程序的名称;
- 命令行中包含的任何命令行参数;
- 在程序启动时的所有当前Linux环境变量.


程序堆栈的一般布局:

```
          -------------------------------------- high address
          |    环境变量
          |    命令行参数
          --------------------------------------
          |    指向环境变量的指针
          --------------------------------------
          |    0x00000000
          --------------------------------------
          |    指向命令行参数n的指针
          --------------------------------------
          |    .......
          --------------------------------------
          |    指向命令行参数2的指针
          --------------------------------------
          |    指向命令行参数1的指针
          --------------------------------------
          |    程序名称
          --------------------------------------
ESP  ->   |    参数数目
          -------------------------------------- low address
```

### 12. 使用系统调用
#### 12.1 Linux内核
#### 12.2 系统调用

定义在`/usr/include/asm/unistd.h`中.

#### 12.3 使用系统调用

(1) 复杂的系统调用返回值

在执行`INT`指令之前, 系统调用值被传送到EAX寄存器中, 例:

``` asm
# exit()
movl $1, %eax
int $0x80
```

(2) 系统调用输入值

输入参数的数量小于6时, 期望的输入值顺序:

- EBX: 第1个参数;
- ECX: 第2个参数;
- EDX: 第3个参数;
- ESI: 第4个参数;
- EDI: 第5个参数.

输出参数的数量超过6时, EBX寄存器用于保存指向输入参数的内存位置的指针, 输入参数按照连续的顺序存储.

(3) 系统调用返回值

系统调用的返回值存放在EAX寄存器中.


#### 12.4 复杂的系统调用返回值

有的系统调用返回C样式结构的复杂数据, 可以在内存位置中创建结构.

#### 12.5 跟踪系统调用

使用strace程序.

#### 12.6 系统调用和C库

使用原始Linux系统调用的原因:

- 不需要吧外部库链接到程序中, 创建长度尽可能短、执行尽可能快的代码;
- 链接后的可执行文件独立于任何外部库代码.

### 13. 使用内联汇编
#### 13.1 什么是内联汇编
#### 13.2 基本的内联汇编代码
#### 13.3 扩展asm
#### 13.4 使用内联汇编代码

### 14. 调用汇编库
#### 14.1 创建汇编函数
#### 14.2 编译C和汇编程序
#### 14.3 在C程序中使用汇编函数
#### 14.4 在C++程序中使用汇编函数
#### 14.5 创建静态库
#### 14.6 使用共享库
#### 14.7 调试汇编程序

### 15. 优化例程
#### 15.1 优化编译器代码
#### 15.2 创建优化的代码
#### 15.3 优化技巧

### 16. 使用文件
#### 16.1 文件处理顺序
#### 16.2 打开和关闭文件
#### 16.3 写入文件
#### 16.4 读取文件
#### 16.5 读取、处理和写入数据
#### 16.6 内存映射文件

### 17. 使用高级IA-32特性
#### 17.1 SIMD简介
#### 17.2 检测支持的SIMD操作
#### 17.3 使用MMX指令
#### 17.4 使用SSE指令
#### 17.5 使用SSE2指令
#### 17.6 SSE3指令

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

### Compiling x86 Assembly on x64 Linux

- [Compiling x86 Assembly on x64 Linux](https://denniskubes.com/2017/01/31/compiling-x86-assembly-on-x64-linux/)
- [Linking an assembler program: error "undefined reference to `printf'"](https://stackoverflow.com/questions/34374591/linking-an-assembler-program-error-undefined-reference-to-printf)
- gcc-multilib g++-multilib: [What exactly does gcc-multilib mean on Ubuntu?](https://askubuntu.com/questions/855945/what-exactly-does-gcc-multilib-mean-on-ubuntu)

```
vi cpuid.s
as -o cpuid.o cpuid.s
as --32 -o cpuid.o cpuid.s
ld -o cpuid cpuid.o
ld -m elf_i386 -o cpuid cpuid.o
ld --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -o cpuid -lc cpuid.o
sudo apt-get install gcc-multilib g++-multilib
ld --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -o cpuid -lc cpuid.o
./cpuid

file cpuid
cpuid: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, not stripped
```

``` asm
.section .data
output:
.asciz "The processor Vendor ID is '%s'\n"

.section .bss
.lcomm buffer, 12

.section .text
.globl _start
_start:
  movl $0, %eax
  cpuid

  movl $buffer, %edi
  movl %ebx, (%edi)
  movl %edx, 4(%edi)
  movl %ecx, 8(%edi)

  pushl $buffer
  pushl $output
  call printf

  addl $8, %esp
  pushl $0
  call exit
```

### Get CPU Information on Linux

```
cat /proc/cpuinfo                   
cpuid                               # show x86 CPU
lscpu                               # show CPU architecture info
sudo dmidecode --type processor     # show linux hardware info
inxi -C                             # show linux system information
sudo lshw -C CPU                    # list hardware configuration
hardinfo                            # show hardware info in GTK+ window
hwinfo --cpu                        # show present hardware info
nproc                               # print number of processing units
x86info                             # display x86 CPU diagnostics
```

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

Richard Blum. **Professional Assembly Language**. 2016.

## 其他备注

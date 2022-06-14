# Notes of **The RISC-V Reader: An Open Architecture Atlas**


|时间|内容|
|:---|:---|
|2022-06-13| first skimming.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1 Why RISC-V?
#### 1.1 Introduction
#### 1.2 Modular vs. Incremental ISAs
#### 1.3 ISA Design 101
#### 1.4 An Overview of this Book
#### 1.5 Concluding Remarks
#### 1.6 To Learn More

### 2 RV32I: RISC-V Base Integer ISA
#### 2.1 Introduction
#### 2.2 RV32I Instruction formats
#### 2.3 RV32I Registers

Figure 2.4 The registers of RV32I.

```
x0  zero  // hardwired zero
x1  ra    // return address
x2  sp    // stack pointer
x3  gp    // global pointer
x4  tp    // thread pointer

x5  t0    // temporary 0
x6  t1    // temporary 1
x7  t2    // temporary 2

x8  s0/fp // saved register 0, frame pointer
x9  s1    // saved register 1

x10 a0    // function argument 0, return value 0
x11 a1    // function argument 1, return value 1
x12 a2    // function argument 2
x13 a3    // function argument 3
x14 a4    // function argument 4
x15 a5    // function argument 5
x16 a6    // function argument 6
x17 a7    // function argument 7

x18 s2    // saved register 2
x19 s3    // saved register 3
x20 s4    // saved register 4
x21 s5    // saved register 5
x22 s6    // saved register 6
x23 s7    // saved register 7
x24 s8    // saved register 8
x25 s9    // saved register 9
x26 s10   // saved register 10
x27 s11   // saved register 11

x28 t3    // temporary 3
x29 t4    // temporary 4
x30 t5    // temporary 5
x31 t6    // temporary 6
```

#### 2.4 RV32I Integer Computation

```
add rd, rs1, rs2            // Add
                            // x[rd] = x[rs1] + x[rs2]
addi rd, rs1, immediate     // Add Immediate
                            // x[rd] = x[rs1] + sext(immediate)
sub rd, rs1, rs2            // Subtract
                            // x[rd] = x[rs1] = x[rs2]
and rd, rs1, rs2            // AND
                            // x[rd] = x[rs1] & x[rs2]
andi rd, rs1, immediate     // AND Immediate
                            // x[rd] = x[rs1] & sext(immediate)
or rd, rs1, rs2             // OR
                            // x[rd] = x[rs1] | x[rs2]
ori rd, rs1, immediate      // OR Immediate
                            // x[rd] = x[rs1] | sext(immediate)
xor rd, rs1, rs2            // Exclusive-OR
                            // x[rd] = x[rs1] ^ x[rs2]
xori rd, rs1, immediate     // Exclusive-OR Immediate
                            // x[rd] = x[rs1] ^ sext(immediate)
sll rd, rs1, rs2            // Shift Left Logical
                            // x[rd] = x[rs1] << x[rs2]
slli rd, rs1, shamt         // Shift Left Logical Immediate
                            // x[rd] = x[rs1] << shamt
sra rd, rs1, rs2            // Shift Right Arithmetic
                            // x[rd] = x[rs1] >>s x[rs2]
srai rd, rs1, shamt         // Shift Right Arithmetic Immediate
                            // x[rd] = x[rs1] >>s shamt
srl rd, rs1, rs2            // Shift Right Logical
                            // x[rd] = x[rs1] >>u x[rs2]
srli rd, rs1, shamt         // Shift Right Logical Immediate
                            // x[rd] = x[rs1] >>u shamt
lui rd, immediate           // Load Upper immediate
                            // x[rd] sext(immediate[31:12] << 12)
auipc rd, immediate         // Add Upper Immediate to PC
                            // x[rd] = pc + sext(immediate[31:12] << 12)
slt rd, rs1, rs2            // Set if Less Than
                            // x[rd] = x[rs1] <s x[rs2]
slti rd, rs1, immediate     // Set if Less Than Immediate
                            // x[rd] = x[rs1] <x sext(immediate)
sltiu rd, rs1, immediate    // Set if Less Than Immediate, Unsigned
                            // x[rd] = x[rs1] <u sext(immediate)
sltu rd, rs1, rs2           // Set if Less Than, Unsigned
                            // x[rd] = x[rs1] <u x[rs2]
```

#### 2.5 RV32I Loads and Stores

```
lb rd, offset(rs1)          // Load Byte
                            // x[rd] = sext(M[x[rs1]] + sext(offset)[7:0])
lh rd, offset(rs1)          // Load Halfword
                            // x[rd] = sext(M[x[rs1] + sext(offset)][15:0])
lw rd, offset(rs1)          // Load Word
                            // x[rd] = sext(M[x[rs1] + sext(offset)][31:0])

sb rs2, offset(rs1)         // Store Byte
                            // M[x[rs1] + sext(offset)] = x[rs2][7:0]
sh rs2, offset(rs1)         // Store Halfword
                            // M[x[rs1] + sext(offset)] = x[rs2][15:0]
sw rs2, offset(rs1)         // Store Word
                            // M[x[rs1] + sext(offset)] = x[rs2][31:0]

lbu rd, offset(rs1)         // Load Byte, Unsigned
                            // x[rd] = M[x[rs1] + sext(offset)][7:0]
lhu rd, offset(rs1)         // Load Halfword, Unsigned
                            // x[rd] = M[x[rs1] + sext(offset)][15:0]
```

#### 2.6 RV32I Conditional Branch

```
beq rs1, rs2, offset        // Branch if Equal
                            // if (rs1 == rs2) pc += sext(offset)
bne rs1, rs2, offset        // Branch if Not Equal
                            // if (rs1 != rs2) pc += sext(offset)
bge rs1, rs2, offset        // Branch if Greater Than or Equal
                            // if (rs1 >=s rs2) pc += sext(offset)
bgeu rs1, rs2, offset       // Branch if Greater Than or Equal, Unsigned
                            // if (rs1 >=u rs2) pc += sext(offset)
blt rs1, rs2, offset        // Branch if Less Than
                            // if (rs1 <s rs2) pc += sext(offset)
bltu rs1, rs2, offset       // Branch if Less Than, Unsigned
                            // if (rs1 <u rs2) pc += sext(offset)
```

#### 2.7 RV32I Unconditional Jump

```
jal rd, offset              // Jump and Link
                            // x[rd] = pc+4; pc += sext(offset)
jalr rd, offset(rs1)        // Jumo and Link Register
                            // t=pc+4; pc=(x[rs1]+sext(offset))&~1; x[rd]=t
```

#### 2.8 RV32I Miscellaneous

```
fence pred, succ            // Fence Memory and I/O
                            // Fence(pred, succ)
fence.i                     // Fence Instruction Stream
                            // Fence(Store, Fetch)
ebreak                      // Environment Breakpoint
                            // RaiseException(Breakpoint)
ecall                       // Environment Call
                            // RaiseException(EnvironmentCall)
csrrc rd, csr, rs1          // Control and Status Register Read and Clear
                            // t=CSRs[csr]; CSRs[csr]= t&~x[rs1]; x[rd]=t
csrrci rd, csr, zimm[4:0]   // Control and Status Register Read and Clear Immediate
                            // t=CSRs[csr]; CSRs[csr]= t&~zim; x[rd]=t
csrrs rd, csr, rs1          // Control and Status Register Read and Set
                            // t=CSRs[csr]; CSRs[csr]= t| x[rs1]; x[rd]=t
csrrsi rd, csr, zim[4:0]    // Control and Status Register Read and Set Immediate
                            // t=CSRs[csr]; CSRs[csr]= t | zim; x[rd]=t
csrrw rd, csr, rs1          // Control and Status Register Read and Write
                            // t=CSRs[csr]; CSRs[csr]=x[rs1]; x[rd]=t
csrrwi rd, csr, zimm[4:0]   // Control and Status Register Read and Write Immediate
                            // x[rd]=CSRs[csr]; CSRs[csr]=zim
```

#### 2.9 Comparing RV32I, ARM-32, MIPS-32, and x86-32
#### 2.10 Concluding Remarks
#### 2.11 To Learn More

### 3 RISC-V Assembly Language
#### 3.1 Introduction
#### 3.2 Calling convention
#### 3.3 Assembly
#### 3.4 Linker
#### 3.5 Static vs. Dynamic Linking
#### 3.6 Loader
#### 3.7 Concluding Remarks
#### 3.8 To Learn More

### 4 RV32M: Multiply and Divide
#### 4.1 Introduction

```
mul rd, rs1, rs2            // Multiply
                            // x[rd] = x[rs1] * x[rs2]
mulh rd, rs1, rs2           // Multiply High
                            // x[rd] = (x[rs1] s*s x[rs1]) >>s XLEN
mulhu rd, rs1, rs2          // Multiply Hig Unsigned
                            // x[rd] = (x[rs1] u*u x[rs2]) >>u XLEN
mulhsu rd, rs1, rs2         // Multiply Hign Signed-Unsigned
                            // x[rd] = (x[rs1] s*u x[rs2]) >>s XLEN
div rd, rs1, rs2            // Divide
                            // x[rd] = x[rs1] / x[rs2]
divu rd, rs1, rs2           // Divide, Unsigned
                            // x[rd] = x[rs1] /u x[rs2]
rem rd, rs1, rs2            // Remainder
                            // x[rd] = x[rs1] % x[rs2]
remu rd, rs1, rs2           // Remainder, Unsigned
                            // x[rd] = x[rs1] %u x[rs2]
```

#### 4.2 Concluding Remarks
#### 4.3 To Learn More

### 5 RV32FD: Single/Double Floating Point
#### 5.1 Introduction
#### 5.2 Floating-Point Registers
#### 5.3 Floating-Point Loads, Stores, and Arithmetic

```
flw rd, offset(rs1)         // FP Load Word
                            // f[rd] = M[x[rs1] + sext(offset)][31:0]
fld rd, offset(rs1)         // FP Load Doubleword
                            // f[rd] = M[x[rs1] + sext(offset)][63:0]
fsw rs2, offset(rs1)        // FP Store Word
                            // M[x[rs1] + sext(offset)] = f[rs2][31:0]
fsd rs2, offset(rs1)        // FP Store Doubleword
                            // M[x[rs1] + sext(offset)] = f[rs2][63:0]

fadd.s rd, rs1, rs2         // FP Add, Single-Precision
                            // f[rd] = f[rs1] + f[rs2]
fadd.d rd, rs1, rs2         // FP Add, Double-Precision
                            // f[rd] = f[rs1] + f[rs2]
fsub.s rd, rs1, rs2         // FP Subtract, Single-Precision
                            // f[rd] = f[rs1] - f[rs2]
fsub.d rd, rs1, rs2         // FP Subtract, Double-Precision
                            // f[rd] = f[rs1] - f[rs2]
fmul.s rd, rs1, rs2         // FP Multiply, Single-Precision
                            // f[rd] = f[rs1] * f[rs2]
fmul.d rd, rs1, rs2         // FP Multiply, Double-Precision
                            // f[rd] = f[rs1] * f[rs2]
fdiv.s rd, rs1, rs2         // FP Divide, Single-Precision
                            // f[rd] = f[rs1] / f[rs2]
fdiv.d rd, rs1, rs2         // FP Divide, Double-Precision
                            // f[rd] = f[rs1] / f[rs2]
fsqrt.s rd, rs1, rs2        // FP Square Root, Single-Precision
                            // f[rd] = SQRT(f[rs1])
fsqrt.d rd, rs1, rs2        // FP Square Root, Double-Precision
                            // f[rd] = SQRT(f[rs1])
fmin.s rd, rs1, rs2         // FP Minimum, Single-Precision
                            // f[rd] = min(f[rs1], f[rs2])
fmin.d rd, rs1, rs2         // FP Minimum, Double-Precision
                            // f[rd] = min(f[rs1], f[rs2])
fmax.s rd, rs1, rs2         // FP Maximum, Single-Precision
                            // f[rd] = max(f[rs1], f[rs2])
fmax.d rd, rs1, rs2         // FP Maximum, Double-Precision
                            // f[rd] = max(f[rs1], f[rs2])

fmadd.s rd, rs1, rs2, rs3   // FP Fused Multiply-Add, Single-Precision
                            // f[rd] = f[rs1] * f[rs2] + f[rs3]
fmadd.d rd, rs1, rs2, rs3   // FP Fused Multiply-Add, Double-Precision
                            // f[rd] = f[rs1] * f[rs2] + f[rs3]
fnmadd.s rd, rs1, rs2, rs3  // FP Fused Negative Multiply-Add, Single-Precision
                            // f[rd] = -f[rs1]*f[rs2] - f[rs3]
fnmadd.d rd, rs1, rs2, rs3  // FP Fused Negative Multiply-Add, Double-Precision
                            // f[rd] = -f[rs1]*f[rs2] - f[rs3]
fmsub.s rd, rs1, rs2, rs3   // FP Fused Multiply-Subtract, Single-Precision
                            // f[rd] = f[rs1] * f[rs2] - f[rs3]
fmsub.d rd, rs1, rs2, rs3   // FP Fused Multiply-Subtract, Double-Precision
                            // f[rd] = f[rs1] * f[rs2] - f[rs3]
fnmsub.s rd, rs1, rs2, rs3  // FP Fused Negative Multiply-Subtract, Single-Precision
                            // f[rd] = -f[rs1]*f[rs2]+f[rs3]
fnmsub.d rd, rs1, rs2, rs3  // FP Fused Negative Multiply-Subtract, Double-Precision
                            // f[rd] = -f[rs1]*f[rs2]+f[rs3]

feq.s rd, rs1, rs2          // FP Equals, Single-Precision
                            // x[rd] = f[rs1] == f[rs2]
feq.d rd, rs1, rs2          // FP Equals, Double-Precision
                            // x[rd] = f[rs1] == f[rs2]
flt.s rd, rs1, rs2          // FP Less Than, Single-Precision
                            // x[rd] = f[rs1] < f[rs2]
flt.d rd, rs1, rs2          // FP Less Than, Double-Precision
                            // x[rd] = f[rs1] < f[rs2]
fle.s rd, rs1, rs2          // FP Less Than or Equal, Single-Precision
                            // x[rd] = f[rs1] <= f[rs2]
fle.d rd, rs1, rs2          // FP Less Than or Equal, Double-Precision
                            // x[rd] = f[rs1] <= f[rs2]
```

#### 5.4 Floating-Point Moves and Converts

```
fmv.w.x rd, rs1, rs2        // FP Move Word from Integer
                            // f[rd] = x[rs1][31:0]
fmv.x.w rd, rs1, rs2        // FP Move Word to Integer
                            // x[rd] = sext(f[rs1][31:0])

fcvt.s.w rd, rs1, rs2       // FP Convert to Single from Word
                            // f[rd] = f32_s32(x[rs1])
fcvt.s.wu rd, rs1, rs2      // FP Convert to Single from Unsigned Word
                            // f[rd] = f32_u32(x[rs1])
fcvt.d.w rd, rs1, rs2       // FP Convert to Double from Word
                            // f[rd] = f64_s32(x[rs1])
fcvt.d.wu rd, rs1, rs2      // FP Convert to Double from Unsigned Word
                            // f[rd] = f64_u32(x[rs1])

fcvt.s.d rd, rs1, rs2       // FP Convert to Single from Double
                            // f[rd] = f32_f64(f[rs1])
fcvt.d.s rd, rs1, rs2       // FP Convert to Double from Single
                            // f[rd] = f64_f32(f[rs1])
```

#### 5.5 Miscellaneous Floating-Point Instructions

```
fsgnj.s rd, rs1, rs2        // FP Sign Inject, Single-Precision
                            // f[rd] = {f[rs2][31], f[rs1][30:0]}
fsgnj.d rd, rs1, rs2        // FP Sign Inject, Double-Precision
                            // f[rd] = {f[rs2][63], f[rs1][62:0]}
fsgnjn.s rd, rs1, rs2       // FP Sign Inject-Negate, Single-Precision
                            // f[rd] = {~f[rs2][31], f[rs1][30:0]}
fsgnjn.d rd, rs1, rs2       // FP Sign Inject-Negate, Double-Precision
                            // f[rd] = {~f[rs2][63], f[rs1][62:0]}
fsgnjx.s rd, rs1, rs2       // FP Sign Inject-XOR, Single-Precision
                            // f[rd] = {f[rs1][31] ^ f[rs2][31], f[rs1][30:0]}
fsgnjx.d rd, rs1, rs2       // FP Sign Inject-XOR, Double-Precision
                            // f[rd] = {f[rs1][63] ^ f[rs2][63], f[rs1][62:0]}

fclass.s rd, rs1, rs2       // FP Classify, Single-Precision
                            // x[rd] = classify_s(f[rs1])
fclass.d rd, rs1, rs2       // FP Classify, Double-Precision
                            // x[rd] = classify_d(f[rs1])
```


#### 5.6 Comparing RV32FD, ARM-32, MIPS-32, and x86-32 using DAXPY
#### 5.7 Concluding Remarks
#### 5.8 To Learn More

### 6 RV32A: Atomic
#### 6.1 Introduction

```
amoadd.w rd, rs2, (rs1)     // AMO: Add Word
                            // x[rd] = AMO32(M[x[rs1]] + x[rs2])
amoand.w rd, rs2, (rs1)     // AMO: AND Word
                            // x[rd] = AMO32(M[x[rs1]] & x[rs2])
amoor.w rd, rs2, (rs1)      // AMO: OR Word
                            // x[rd] = AMO32(M[x[rs1]] | x[rs2])
amoswap.w rd, rs2, (rs1)    // AMO: Swap Word
                            // x[rd] = AMO32(M[x[rs1]] SWAP x[rs2])
amoxor.w rd, rs2, (rs1)     // AMO: XOR Word
                            // x[rd] = AMO32(M[x[rs1]] ^ x[rs2])
amomax.w rd, rs2, (rs1)     // AMO: Maximum Word
                            // x[rd] = AMO32(M[x[rs1]] MAX x[rs2])
amomaxu.w rd, rs2, (rs1)    // AMO: Maximum Word, Unsigned
                            // x[rd] = AMO32(M[x[rs1]] MAXU x[rs2])
amomin.w rd, rs2, (rs1)     // AMO: Minimum Word
                            // x[rd] = AMO32(M[x[rs1]] MIN x[rs2])
amominu.w rd, rs2, (rs1)    // AMO: Minimum Word, Unsigned
                            // x[rd] = AMO32(M[x[rs1]] MINU x[rs2])

lr.w rd, (rs1)              // Load-Reserved Word
                            // x[rd] = LoadReserved32(M[x[rs1]])
sc.w rd, rs2, (rs1)         // Store-Conditional Word
                            // x[rd] = StoreConditional32(M[x[rs1], x[rs2])
```

#### 6.2 Concluding Remarks
#### 6.3 To Learn More

### 7 RV32C: Compressed Instructions
#### 7.1 Introduction
#### 7.2 Comparing RV32GC, Thumb-2, microMIPS, and x86-32
#### 7.3 Concluding Remarks
#### 7.4 To Learn More

### 8 RV32V: Vector

> Based on **The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Version 2.2. May 2017.**, a rather old version.

#### 8.1 Introduction
#### 8.2 Vector Computation Instructions

#### 8.3 Vector Registers and Dynamic Typing

RV32V adds *32 vector registers*, whose name start with `v`, but the number of elements per vector register varies.

To keep the number of elements flexible in a vector ISA, a vector procesor calculates the **maximum vector length (mvl)** that programs use to run properly on processors with differing amounts of memory for vector registers.

The **vector length register (vl)** sets the number of elements in a vector for a particular operation, which helps programs when a dimension of an array is not a multiple of **mvl**.

RV32V takes the novel approach of *associating the data type and length with the vector registers* rather than with the instruction opcodes. A program tags the vector registers with their data type and width before executing the vector computation instructions.


#### 8.4 Vector Loads and Stores

#### 8.5 Parallelism During Vector Execution
#### 8.6 Conditional Execution of Vector Operations

8 **predicate registers (vpi)**.

#### 8.7 Miscellaneous Vector Instructions

#### 8.8 Vector Example: DAXPY in RV32V
#### 8.9 Comparing RV32V, MIPS-32 MSA SIMD, and x86-32 AVX SIMD
#### 8.10 Concluding Remarks
#### 8.11 To Learn More

### 9 RV64: 64-bit Address Instructions
#### 9.1 Introduction
#### 9.2 Comparison to Other 64-bit ISAs using Insertion Sort
#### 9.3 Program size
#### 9.4 Concluding Remarks
#### 9.5 To Learn More

### 10 RV32/64 Privileged Architecture
#### 10.1 Introduction

modes:

- user mode: where application code usually runs. **U-mode**.
- machine mode: privileged, which runs the most trusted code. **M-mode**.
- supervisor mode: privileged, which provides support for operating systems. **S-mode**.

Processors typically spend most of their execution time in their least-privileged mode; interrupts and exceptions transfer control to more-privileged modes.

#### 10.2 Machine Mode for Simple Embedded Systems

Machine mode (M-mode) is the most privileged mode that a RISC-V hart (hardware thread) can execute in. Harts running in M-mode have full access to memory, I/O, and low-level system features necessary to boot and configure the system.

RISC-V classifies exceptions(unusual runtime events) into two categories:

- synchronous exceptions: arise as a result of instruction exceution, as when accessing an invalid memory address or executing an instruction with an invalid opcode.
- interrupts: are external events that are asynchronous iwth the instruction stream, like a mouse button click.

Exceptions in RISV-V are precise: all instructions prior to the exception completely execute, and none of the subsequent instructions apprear to have begun execution.


|Exception Category|Exception Code|Descrition|
|:---|:---|:---|
|1   |1   |Supervisor software interrupt|
|1   |3   |Machine software interrupt|
|1   |5   |Supervisor timer interrupt|
|1   |7   |Machine timer interrupt|
|1   |9   |Supervisor external interrupt|
|1   |11  |Machine external interrupt|
|0   |0   |Instruction address misaligned|
|0   |1   |Instruction access fault|
|0   |2   |Illegal instruction|
|0   |3   |Breakpoint|
|0   |4   |Load address misaligned|
|0   |5   |Load access fault|
|0   |6   |Store address misaligned|
|0   |7   |Store address fault|
|0   |8   |Environment call from U-mode|
|0   |9   |Environment call from S-mode|
|0   |11  |Environment call from M-mode|
|0   |12  |Instruction page fault|
|0   |13  |Load page fault|
|0   |15  |Store page fault|

#### 10.3 Machine-Mode Exception Handling

8 **control and status registers (CSRs)** are integral to machine-code exception handling:

- `mtvec`, Machine Trap Vector: holds the address the processor jumps to when an exception occurs.
- `mepc`, Machine Exception PC: points to the instruction where the exception occurred.
- `mcause`, Machine Exception Cause: indicates which exception occurred.
- `mie`, Machine Interrupt Enable: lists which interrupts the processor can take and which it must ignore.
- `mip`, Machine Interrupt Pending: lists the interrupts currently pending.
- `mtval`, Machine Trap Value: holds additional trap information, including the faulting adrress for address exceptions, the instruction itself for illegal instruction exceptions, and zero for other exception.
- `mscratch`, Machine Stratch: holds one word of data for temporary storage.
- `mstatus`, Machine Status: holds the global interrupt rnable, along with a plethora of other state.

When a hart takes an exception, the hardware atomically undergoes several state transitions:

> TBD.

#### 10.4 User Mode and Process Isolation in Embedded Systems

User mode (U-mode) must be forbidden from executin privileged instructions, like `mret` and accessing privileged CSRs, like `mstatus`, an illegal instruction exception is generated when attempting to use an M-mode instruction or CSR.

M-mode software can enter U-mode by setting `mstatus.MPP` to `U`, then executing an `mret` instruction. If an exception occurs in U-mode, control is returned to M-mode.

Processors that implement M and U modes have a feature called **Physocal Memory Protection (PMP)**, which allows M-mode to specify which memory addresses U-mode can access.

#### 10.5 Supervisor Mode for Modern Operating Systems

Since PMP supports only a fixed number of memory regions, and these regions must be contiguous in physical memory, the system can suffer from memory fragmentation. And PMP does not efficiently support paging to secondary storage.

**Page-based virtual memory** forms the core of supervisor mode (S-mode).

By default, all exceptions, regardless of privilege mode, transfer control to the M-mode exception handler.
The M-mode exception handler coule re-route exceptions to S-mode, but this extra code would slow down the handling of most exception.
RISC-V provides an **exception delegation mechanism**, by which interrupts and synchronous exceptions can be delegated to S-mode selectively, bypassing M-mode software altogether.

If a hart taks an exception and it is delegated to S-mode, the hardware atomically undergoes several similar state transitions, using S-mode CSRs instead of M-mode ones:

> TBD.

#### 10.6 Page-Based Virtual Memory

S-mode provides a conventional virtual memory system that divides memory into fixed-size pages for the purposes of address translation and memory protection.

Vortia; address are translated to physical address by traversing a high-radix tree known as **the page table**. A leaf node in the page table indicates whether the virtual address maps to a physical page, and if so, which privilege modes and access types have permission to access the page.

RISC-V paging schemes are named **SvX**, where `X` is the size of a virtual address in bits, for example `Sv32`, `Sv39`, `Sv48`.

When paging is enabled in the `satp` register, S-mode and U-mode virtual addresses are translated into physical addreess by traversing the page table, starting at the root.

> TBD.

#### 10.7 Concluding Remarks
#### 10.8 To Learn More

### 11 Future RISC-V Optional Extensions
#### 11.1 “B” Standard Extension for Bit Manipulation
#### 11.2 “E” Standard Extension for Embedded
#### 11.3 “H” Privileged Architecture Extension for Hypervisor Support
#### 11.4 “J” Standard Extension for Dynamically Translated Languages
#### 11.5 “L” Standard Extension for Decimal Floating-Point
#### 11.6 “N” Standard Extension for User-Level Interrupts
#### 11.7 “P” Standard Extension for Packed-SIMD Instructions
#### 11.8 “Q” Standard Extension for Quad-Precision Floating-Point
#### 11.9 Concluding Remarks

### A RISC-V Instruction Listings


## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- David Patterson, Andrew Waterman.**The RISC-V Reader: An Open Architecture Atlas**. Strawberry Canyon: 2017.

## 其他备注

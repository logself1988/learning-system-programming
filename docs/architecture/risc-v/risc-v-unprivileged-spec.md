# Notes of **The RISC-V Instruction Set Manual Volume I: Unprivileged ISA**


|时间|内容|
|:---|:---|
|2022-05-14| kick off. |

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- RISC-V module status: Ratified 批准的, Draft 草案, Frozen 冻结的.
- hart:
- EEI: Execution Environment Interface, 执行环境接口.

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

学习RISC-V用户级别指令集架构, 作为编译器目标机器示例.

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### Preface

The document contians the following versions of the RISC-V ISA modules:

|Base   |Version|Status   |Description                  |
|:---   |:---   |:---     |:---                         |
|RVWMO  |2.0    |Ratified |RISC-V Weak Memory Ordering  |
|RV32I  |2.1    |Ratified |Base Integer Instruction Set, XLEN=32 |
|RV64I  |2.1    |Ratified |Base Integer Instruction Set |
|RV32E  |1.9    |Draft    |Base Integer Instruction Set |
|RV128I |1.7    |Draft    |Base Integer Instruction Set |

|Extension|Version|Status   |Description                                    |
|:---     |:---   |:---     |:---                                           |
|M        |2.0    |Ratified |Integer Multilication and Division             |
|A        |2.1    |Ratified |Atomic Instructions                            |
|F        |2.2    |Ratified |Single-Precision Floating-Point                |
|D        |2.2    |Ratified |Double-Precision Floating-Point                |
|Q        |2.2    |Ratified |Quad-Precision Floating-Point                  |
|C        |2.0    |Ratified |Compressed Instructions                        |
|Counters |2.0    |Draft    |Counters                                       |
|L        |0.0    |Draft    |Decimal Floating-Point                         |
|B        |0.0    |Draft    |Bit Manipulation                               |
|J        |0.0    |Draft    |Dynamically Translated Languages               |
|T        |0.0    |Draft    |Transactional Memory                           |
|P        |0.2    |Draft    |Packed-SIMD Instructions                       |
|V        |0.7    |Draft    |Vector Operations                              |
|Zicsr    |2.0    |Ratified |Control and Status Register (CSR) Instructions |
|Zifencei |2.0    |Ratified |Instruction-Fetech Fence                       |
|Zam      |0.1    |Draft    |Misaligned Atomics                             |
|Ztso     |0.1    |Frozen   |Total Store Ordering                           |

### 1. Introduction

> The RISC-V ISA is defined avoiding implementation details as much as possible and should be read as the software-visible interface to a wide variety of implementations rather than as the design of a particular hardware artifact.

#### 1.1 RISC-V Hardware Platform Terminology

- core: a component contains an independent instruction fetch unit.
- harts: hardware threads.
- coprocessor: refer to a unit that is attached to a RISC-V core and is mostly sequenced by a RISC-V instruction stream, but which contains additional architecture state and instruction-set extensions, and possibly some limited autonomy relative to the primary RISC-V instruction stream.
- accelerator: refer to either a non-programmable fixed-funciton unit or a core that can operate autonomously but is specialized for certain tasks.

#### 1.2 RISC-V Software Execution Environments and Harts

- EEI: Execution Environment Interface.

> From the perspective of software running in a given execution environment, a **hart** is a resource that autonomously fetches and executes RISC-V instructions within that execution environment.


#### 1.3 RISC-V ISA Overview

> A RISC-V ISA is defined as a base integer ISA, which must be present in any implementation, plus optional extensions to the base ISA.


- RV32I, RV64I
- XLEN: refer ti the width of an integer register in bits.
- RV32E
- RV128I

> RISC-V has been designed to support extensive customization and specification.

- "I": base integer ISA, prefixed by RV32, RV64.
- "M": standard integer multiplication and division extension.
- "A": standard atomic instruction extension.
- "F": standard single-precision floating-point extension.
- "D": standard double-precision floating-point extension.
- "C": standard compressed instruction extension.

#### 1.4 Memory

> The default memory consistency model for RISC-V is the RISC-V Weak Memory Ordering(RVWMO).

#### 1.5 Base Instruction-Length Encoding

- IALIGN: refer to the instruction-address alignment constraint the implementation enforces, measured in bits.
- ILEN: refer to the maximum instruction length supported by an implementation, which is always a multiple of IALIGN, measured in bits.


Figure 1.1: RISC-V instruction length encoding.


```
                        +----------------+
                        |xxxxxxxxxxxxxxaa| 16-bit (aa != 11)
                        +----------------+

       +----------------+----------------+
       |xxxxxxxxxxxxxxxx|xxxxxxxxxxxbbb11| 32-bit (bbb != 111)
       +----------------+----------------+

-------+----------------+----------------+
...xxxx|xxxxxxxxxxxxxxxx|xxxxxxxxxx011111| 48-bit
-------+----------------+----------------+

-------+----------------+----------------+
...xxxx|xxxxxxxxxxxxxxxx|xxxxxxxxx0111111| 64-bit
-------+----------------+----------------+

-------+----------------+----------------+
...xxxx|xxxxxxxxxxxxxxxx|xnnnxxxxx1111111| (80+16*nnn)-bit, n != 111
-------+----------------+----------------+

-------+----------------+----------------+
...xxxx|xxxxxxxxxxxxxxxx|x111xxxxx1111111| Reserved for >= 192-bits
-------+----------------+----------------+

 base+4           base+2             base  Byte Address
```

> Instructions are stored in memory as a sequence of 16-bit little-endian parcels, regardless of memory system endianness.

#### 1.6 Exceptions, Traps, and Interrupts

- exception: refer to an unusual condition occurring at run time associated with an instruction in the current RISC-V hart.
- interrupt: refer to an external asynchronous event that may cause a RISC-V hart to experience an unexpected transfer of control.
- trap: refer to the transfer of control to a trap handler caused by either an exception or an interrupt.

#### 1.7 UNSPECIFIED Behaviors and Values

- UNSPECIFIED: refer to a behavior or value that is intentionally unconstrained.

### 2. RV32I Base Integer Instruction Set, Version 2.1
#### 2.1 Programmers' Model for Base Integer ISA

XLEN=32

Figure 2.1: RISC-V base unpriviledge integer register state.

```
 XLEN-1         0
+----------------+
|      x0/zero   |
+----------------+
|      x1        |
+----------------+
|      ...       |
+----------------+
|      x31       |
+----------------+
       XLEN

 XLEN-1         0
+----------------+
|      pc        | program counter
+----------------+
       XLEN
```

#### 2.2 Base Instruction Formats

The RISC-V ISA keeps the source (`rs1` aand `rs2`) and destination (`rd`) registers at the same position in all formats to simplify decoding.

Except for the 5-bit immediates used in CSR instructions, immediates are always sign-extended, and are generally packed towards the left most available bits in the instruction and have been allocated to reduce hardware complexity. The sign bit for all immediates is always in bit 31 of the instruction.

4 core instruction formats (R/I/S/U):

Figure 2.2: RISC-V base instruction formats. Each immediate subfield is labeled with the bit position (`imm[x]`) in the immediate value being produced.

```
 31             25 24      20 19      15 14  12 11             7 6            0
+-----------------+----------+----------+------+----------------+--------------+
|funct7           |rs2       |rs1       |funct3|rd              |opcode        | R-type
+-----------------+----------+----------+------+----------------+--------------+
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
+-----------------+----------+----------+------+----------------+--------------+
|imm[11:5]        |rs2       |rs1       |funct3|imm[4:0]        |opcode        | S-type
+-----------------+----------+----------+------+----------------+--------------+
+----------------------------------------------+----------------+--------------+
|imm[31:12]                                    |rd              |opcode        | U-type
+----------------------------------------------+----------------+--------------+

R: register-register ALU instructions
rd: destination register
rs1: first source register
rs2: second source register

I: ALU immediates load
rd: destination register
rs1: first source base register
imm: value displacement

S: store, compare and branch
rs1: base register first source
rs2: data source to store second source
imm: displacement offset

U: jump and link, jump and link register
rd: register destination for return PC
imm: target address for jump and link
```

#### 2.3 Immediate Encoding Variants

2 variants of the instruction formats (B/J) based on the handling of immediates:

```
 31             25 24      20 19      15 14  12 11             7 6            0
+-----------------+----------+----------+------+----------------+--------------+
|funct7           |rs2       |rs1       |funct3|rd              |opcode        | R-type
+-----------------+----------+----------+------+----------------+--------------+
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
+-----------------+----------+----------+------+----------------+--------------+
|imm[11:5]        |rs2       |rs1       |funct3|imm[4:0]        |opcode        | S-type
+-----------------+----------+----------+------+----------------+--------------+
+-------+---------+----------+----------+------+--------+-------+--------------+
|imm[12]|imm[10:5]|rs2       |rs1       |funct3|imm[4:1]|imm[11]|opcode        | B-type *
+-------+---------+----------+----------+------+--------+-------+--------------+
+----------------------------------------------+----------------+--------------+
|imm[31:12]                                    |rd              |opcode        | U-type
+----------------------------------------------+----------------+--------------+
+-------+------------+-------+-----------------+----------------+--------------+
|imm[20]|imm[10:1]   |imm[11]|imm[19:12]       |rd              |opcode        | J-type *
+-------+------------+-------+-----------------+----------------+--------------+
```

Figure 2.4: Types of immediate produced by RISC-V instructions.


```
 31 30             20 19       12       11 10        5 4             1        0
+-----------------------------------------+-----------+---------------+--------+
|-inst[31]-                               |inst[30:25]|inst[24:21]    |inst[20]| I-immediate
+-----------------------------------------+-----------+---------------+--------+
+-----------------------------------------+----+----------------+-----+--------+
|-inst[31]-                               |inst[30:25]|inst[11:8]     |inst[7] | S-immediate
+-----------------------------------------+----+----------------+-----+--------+
+--------------------------------+--------+----+--------+-------+-----+--------+
|-inst[31]-                      |inst[7] |inst[30:25]|inst[11:8]     |0       | B-immediate
+--------------------------------+--------+----+--------+-------+-----+--------+
+--------+-----------+-----------+---------------------------------------------+
|inst[31]|inst[30:20]|inst[19:12]|-0-                                          | U-immediate
+--------+-----------+-----------+---------------------------------------------+
+--------------------+-----------+--------+----+------+---------------+--------+
|-inst[31]-          |inst[19:12]|inst[20]|inst[30:25]|inst[24:21]    |0       | J-immediate
+--------------------+-----------+--------+----+------+---------------+--------+
```

#### 2.4 Integer Computational Instructions

Integer computational instructions are either encoded as register-immediate operations using the **I-type** format or as register-register operations using the **R-type** format.

##### Integer Register-Immediate Instructions

- ADDI, SLTI[U], ANDI, ORI, XORI

```
 31             25 24      20 19      15 14  12 11             7 6            0
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
 12                           5          3      5                7
 I-immediate[11:0]            src        ADDI   dest             OP-IMM
                                         SLTI[U]
                                         ANDI
                                         ORI
                                         XORI
```

- SLLI, SRLI, SRAI


```
 31             25 24      20 19      15 14  12 11             7 6            0
+-----------------+----------+----------+------+----------------+--------------+
|funct7           |rs2       |rs1       |funct3|rd              |opcode        | R-type
+-----------------+----------+----------+------+----------------+--------------+
 7                 5          5          3      5                7
 0000000           shamt[4:0] src        SLLI   dest             OP-IMM
 0000000           shamt[4:0] src        SRLI   dest             OP-IMM
 0100000           shamt[4:0] src        SRAI   dest             OP-IMM
```

- LUI, AUIPC

```
 31                                          12 11             7 6            0
+----------------------------------------------+----------------+--------------+
|imm[31:12]                                    |rd              |opcode        | U-type
+----------------------------------------------+----------------+--------------+
 20                                             5                7
 U-immediate[31:12]                             dest             LUI
                                                                 AUIPC
```

##### Integer Register-Register Operations

- ADD/SLT/SLTU, AND/OR/XOR, SLL/SRL, SUB/SRA

```
 31             25 24      20 19      15 14  12 11             7 6            0
+-----------------+----------+----------+------+----------------+--------------+
|funct7           |rs2       |rs1       |funct3|rd              |opcode        | R-type
+-----------------+----------+----------+------+----------------+--------------+
 7                 5          5          3      5                7
 0000000           src2       src1       ADD    dest             OP
                                         SLT
                                         SLTU
                                         AND
                                         OR
                                         XOR
 0100000           src2       src1       SUB    dest             OP
                                         SRA
```

##### NOP Instruction

```
 31             25 24      20 19      15 14  12 11             7 6            0
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
 12                           5          3      5                7
 0                            0          ADDI   0                OP-IMM
```

#### 2.5 Control Transfer Instructions

##### Unconditional Jumps

- JAL

```
 31             25 24      20 19      15 14  12 11             7 6            0
+-------+------------+-------+-----------------+----------------+--------------+
|imm[20]|imm[10:1]   |imm[11]|imm[19:12]       |rd              |opcode        | J-type
+-------+------------+-------+-----------------+----------------+--------------+
 1       10           1       8                 5                7
 offset[20:1]                                   dest             JAL
```

- JALR

```
 31                        20 19      15 14  12 11             7 6            0
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
 12                           5          3      5                7
 offset[11:0]                 base       0      dest             JALR
```

##### Conditional Branches

- BEQ/BNE, BLT[U], BGE[U]

```
31             25 24      20 19      15 14  12 11             7 6            0
+-------+---------+----------+----------+------+--------+-------+--------------+
|imm[12]|imm[10:5]|rs2       |rs1       |funct3|imm[4:1]|imm[11]|opcode        | B-type
+-------+---------+----------+----------+------+--------+-------+--------------+
 1       6         5          5          3      4        1       7
 offset[12|10:5]   src2       src1       BEQ    offset[11|4:1]   BRANCH
                                         BNE
                                         BLT[U]
                                         BGE[U]
```

#### 2.6 Load and Store Instructions

- LOAD, STORE

```
 31                        20 19      15 14  12 11             7 6            0
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
 12                           5          3      5                7
 offset[11:0]                 base       width  dest             LOAD

31             25 24      20 19      15 14  12 11             7 6            0
+-----------------+----------+----------+------+----------------+--------------+
|imm[11:5]        |rs2       |rs1       |funct3|imm[4:0]        |opcode        | S-type
+-----------------+----------+----------+------+----------------+--------------+
 7                 5          5          3      5                7
 offset[11:5]      src        base       width  offset[4:0]      STORE
```

#### 2.7 Memory Ordering Instructions

- FENCE

```
 31 28 27 26 25 24 23 22 21 20 19      15 14  12 11             7 6            0
+-----+--+--+--+--+--+--+--+--+----------+------+----------------+--------------+
|fm   |PI|PO|PR|PW|SI|SO|SR|SW|rs1       |funct3|imm[4:0]        |opcode        |
+-----+--+--+--+--+--+--+--+--+----------+------+----------------+--------------+
 4     1  1  1  1  1  1  1  1  5          3      5                7
 FM    predecessor successor   0          FENCE  0                MISC-MEM
```

#### 2.8 Environment Call and Breakpoints

- ECALL, EBREAK

```
 31                        20 19      15 14  12 11             7 6            0
+----------------------------+----------+------+----------------+--------------+
|imm[11:0]                   |rs1       |funct3|imm[4:0]        |opcode        | I-type
+----------------------------+----------+------+----------------+--------------+
 12                           5          3      5                7
 ECALL                        0          PRIV   0                SYSTEM
 EBREAK
```

#### 2.9 HINT Instructions

### 3. "Zifencei" Instruction-Fetch Fence, Version 2.0

### 4. RV32E Base Integer Instruction Set, Version 1.9
#### 4.1 RV32E Programmers' Model
#### 4.2 RV32E Instruction Set

### 5. RV64I Base Integer Instruction Set, Version 2.1
#### 5.1 Register State
#### 5.2 Integer Computational Instructions
#### 5.3 Load and Store Instructions
#### 5.4 HINT Instructions

### 6. RV128I Base Integer Instruction Set, Version 1.7

### 7. "M" Standard Extension for Integer Multiplication and Division, Version 2.0
#### 7.1 Multiplication Operations
#### 7.2 Division Operations

### 8. "A" Standard Extension for Atomic Instructions, Version 2.1
#### 8.1 Specifying Ordering of Atomic Instructions
#### 8.2 Load-Reserved/Store-Conditional Instructions
#### 8.3 Eventual Success of Store-Conditional Instructions
#### 8.4 Atomic Memory Operations

### 9. "Zicsr", Control and Status Register (CSR) Instructions, Version 2.0
#### 9.1 CSR Instructions

### 10. Counters
#### 10.1 Base Counters and Timers
#### 10.2 Hardware Performance Counters

### 11. "F" Standard Extension for Single-Precision Floating-Point, Version 2.2
#### 11.1 F Register State
#### 11.2 Floating-Point Control and Status Register
#### 11.3 NaN Generation and Propagation
#### 11.4 Subnormal Arithmetic
#### 11.5 Single-Precision Load and Store Instructions
#### 11.6 Single-Precision Floating-Point Computational Instructions
#### 11.7 Single-Precision Floating-Point Conversion and Move Instructions
#### 11.8 Single-Precision Floating-Point Compare Instructions
#### 11.9 Single-Precision Floating-Point Classify Instruction


### 12. "D" Standard Extension for Double-Precision Floating-Point, Version 2.2
#### 12.1 D Register State
#### 12.2 NaN Boxing of Narrower Values
#### 12.3 Double-Precision Load and Store Instructions
#### 12.4 Double-Precision Floating-Point Computational Instructions
#### 12.5 Double-Precision Floating-Point Conversion and Move Instructions
#### 12.6 Double-Precision Floating-Point Compare Instructions
#### 12.7 Double-Precision Floating-Point Classify Instruction


### 13. "Q" Standard Extension for Quad-Precision Floating-Point, Version 2.2
#### 13.1 Quad-Precision Load and Store Instructions
#### 13.2 Quad-Precision Computational Instructions
#### 13.3 Quad-Precision Convert and Move Instructions
#### 13.4 Quad-Precision Floating-Point Compare Instructions
#### 13.5 Quad-Precision Floating-Point Classify Instruction

### 14. RVWMO Memory Consistency Model, Version 0.1
#### 14.1 Definition of the RVWMO Memory Model
#### 14.2 CSR Dependency Tracking Granularity
#### 14.3 Source and Destination Register Listings

### 15. "L" Standard Extension for Decimal Floating-Point, Version 0.0
#### 15.1 Decimal Floating-Point Registers

### 16. "C" Standard Extension for Compressed Instructions, Version 2.0
#### 16.1 Overview
#### 16.2 Compressed Instruction Formats
#### 16.3 Load and Store Instructions
#### 16.4 Control Transfer Instructions
#### 16.5 Integer Computational Instructions
#### 16.6 Usage of C Instructions in LR/SC Sequences
#### 16.7 HINT Instructions
#### 16.8 RVC Instruction Set Listings

### 17. "B" Standard Extension for Bit Manipulation, Version 0.0

### 18. "J" Standard Extension for Dynamically Translated Languages, Version 0.0

### 19. "T" Standard Extension for Transactional Memory, Version 0.0

### 20. "P" Standard Extension for Packed-SIMD Instructions, Version 0.2

### 21. "V" Standard Extension for Vector Operations, Version 0.7

### 22. "Zam" Standard Extension for Misaligned Atomics, v0.1

### 23. "Ztso" Standard Extension for Total Store Ordering, v0.1

### 24. RV32/64G Instruction Set Listings

### 25. RISC-V Assembly Programmer's Handbook

### 26. Extending RISC-V
#### 26.1 Extension Terminology
#### 26.2 RISC-V Extension Design Philosophy
#### 26.3 Extensions within fixed-width 32-bit instruction format
#### 26.4 Adding aligned 64-bit instruction extensions
#### 26.5 Supporting VLIW encodings

### 27. ISA Extension Naming Conventions
#### 27.1 Case Sensitivity
#### 27.2 Base Integer ISA
#### 27.3 Instruction-Set Extension Names
#### 27.4 Version Numbers
#### 27.5 Underscores
#### 27.6 Additional Standard Extension Names
#### 27.7 Supervisor-level Instruction-Set Extensions
#### 27.8 Hypervisor-level Instruction-Set Extensions
#### 27.9 Machine-level Instruction-Set Extensions
#### 27.10 Non-Standard Extension Names
#### 27.11 Subset Naming Convention

### 28. History and Acknowledgments
#### 28.1 "Why Develop a new ISA?" Rationale from Berkeley Group
#### 28.2 History from Revision 1.0 of ISA manual
#### 28.3 History from Revision 2.0 of ISA manual
#### 28.4 History from Revision 2.1
#### 28.5 History from Revision 2.2
#### 28.6 History for Revision 2.3
#### 28.7 Funding

### Appendix A. RVWMO Explanatory Material, Version 0.1
#### A.1 Why RVWMO?
#### A.2 Litmus Tests
#### A.3 Explaining the RVWMO Rules
##### A.3.1 Preserved Program Order and Global Memory Order
##### A.3.2 Load Value Axiom
##### A.3.3 Atomicity Axiom
##### A.3.4 Progress Axiom
##### A.3.5 Overlapping-Address Orderings (Rules 1–3)
##### A.3.6 Fences (Rule 4)
##### A.3.7 Explicit Synchronization (Rules 5–8)
##### A.3.8 Syntactic Dependencies (Rules 9–11)
##### A.3.9 Pipeline Dependencies (Rules 12–13)
#### A.4 Beyond Main Memory
##### A.4.1 Coherence and Cacheability
##### A.4.2 I/O Ordering
#### A.5 Code Porting and Mapping Guidelines
#### A.6 Implementation Guidelines
##### A.6.1 Possible Future Extensions
#### A.7 Known Issues
##### A.7.1 Mixed-size RSW

### Appendix B. Formal Memory Model Specifications, Version 0.1
#### B.1 Formal Axiomatic Specification in Alloy
#### B.2 Formal Axiomatic Specification in Herd
#### B.3 An Operational Memory Model
##### B.3.1 Intra-instruction Pseudocode Execution
##### B.3.2 Instruction Instance State
##### B.3.3 Hart State
##### B.3.4 Shared Memory State
##### B.3.5 Transitions
##### B.3.6 Limitations

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- RISC-V ISA Specification, [Volume 1, Unprivileged Spec v. 20191213](https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf).

## 其他备注

# Notes of **Computer Architecture: A Quantitative Approach**


## Appendix A. Instruction Set Principles
### A.1 Introduction

4 topics:

1. present a taxonomy of instruction set alternatives, and give some qualitative assessment of the advantages and disadvantages of various approaches;
2. present and analyze some instruction set measurements that are largely independent of a specific instruction set;
3. address the issue of languages and compilers and their bearing on instruction set architecture;
4. show how these ideas are reflected in the RISC-V instruction set in the "Putting It All Together" section.

### A.2 Classifying Instruction Set Architectures

differentiation on the type of internal storage in a processor:

- **stack architecture**: operands are implicitly on the top of the stack;
- **accumulator architecture**: one operand is implicitly the accumulator;
- **general-purpose register architecture**: only explicit operands, either registers or memory locations.

classes of register computers:

- **register-memory architecture**: can access memory as part of any instruction;
- **load-store architecture**: can access memory only with load and store instructions;
- **memory-memory architecture**: keeps all operands in memory, not found in computers shipping today.

Figure A.2 The code sequence for C = A + B for four classes of instruction sets.

```
// 1. stack
Push A
Push B
Add
Pop C

// 2. accumulator
Load A
Add B
Store C

// 3. register-memory
Load R1, A
Add R3, R1, B
Store R3, C

// 4. load-store
Load R1, A
Load R2, B
Add R3, R1, R2
Store R3, C
```

2 major instruction set characteristics divide GPR(general-purpose register) architectures: on the nature of operands for a typical ALU(arithmetic or logical) instruction

1. whether an ALU instruction has 2 or 3 operands;
2. how many of the operands may be memory addresses in ALU instructions.

Figure A.3 Typical combinations of memory operands and total operands per typical ALU instruction with examples of computers.

> (m, n): m memory operands and n total operands.


|(m,n)|Type of Architecture |Examples|
|:--- |:---                 |:---|
|(0,3)|load-store           |Alpha, ARM, MIPS, PowerPC, SPARC, SuperH, RISC-V, TM32|
|(1,2)|register-memory      |IBM 360.370, Intel 80x86, Motorola 68000, TI TMS320C54x|
|(2,2)|memory-memory        |VAX|
|(3,3)|memory-memory        |VAX|

Figure A.4 Advantages and disadvantages of the three most common types of GPR computers.


(1) register-register (0,3)

advantages:

- simple, fixed-length instruction encoding,
- simple code generation model,
- instructions take similar numbers of clocks to execute.

disadvantages:

- higher instruction count that architectures with memory references in instructions,
- more instructions and lower instruction density lead to larger programs, which may have some instruction cache effects.

(2) register-memory (1,2)

advantages:

- data can be accessed without a separate load instruction first,
- instruction format tends to be easy to encode and yields good density.

disadvantages:

- operands are not equivalent because a source operand in a binary operation is destroyed,
- encoding a register number and a memory address in reach instruction may restrict the number of registers,
- clocks per instruction vary by operand location.

(3) memory-memory (2,2), (3,3)

advantages:

- most compact,
- does not waste registers for temporaries.

disadvantages:

- large variation in instruction size, especially for three-operand instructions,
- large variation in work per instruction,
- memory accesses create memory bottleneck. (not used today.)

### A.3 Memory Addressing

interpreting memory addresses:

- endianess: ordering the bytes within a larger object,
- alignment: an access to an object of size s bytes at byte address A is aligned if A mod s = 0.

addressing modes:

- how architecture specify the address of an object they will access,
- specify constants and registers in addition to locations in memory.

**PC-relative addressing**: specify code addresses in control transfer instructions.

Figure A.6 Selection of addressing modes with examples, meaning, and usage.

==Notations==

- `d`: in autoincrement/-decrement and scaled addressing modes, variable *d* designates the size of the data item being accessed.
- `R1`, `R2`, `R3`, `R4`: registers.
- `Regs`: the name for registers, an array.
- `Regs[R1]`: the content of register R1.
- `Mem`: the name for main memory, an array.
- `Mem[Regs[R1]]`: the content of the memory location whose address is given by the content of register R1.
- `#3`: constant 3.
- `(R1)`: register indirect.
- `@(R3)`: memory indirect.
- `(R2)+`: autoincrement.
- `-(R2)`: autodecrement.
- `[R3]`: scaled.
- `<-`: for assignment.

**Addressing modes (for data)**:

(1) register

```
Add R4, R3

Regs[R4] <- Regs[R4] + Regs[R3]
```

**used**: when a value is in a register.

(2) immediate

```
Add R4, #3

Regs[R4] <- Regs[R4] + 3
```

**used**: for constants.

(3) register indirect

```
Add R4, (R1)

Regs[R4] <- Regs[R4] + Mem[Regs[R1]]
```

**used**: accessing using a pointer or a computed address.

(4) indexed

```
Add R3, (R1 + R2)

Regs[R3] <- Regs[R3] + Mem[Regs[R1] + Regs[R2]]
```

**used**: useful in array addressing: R1 = base of array, R2 = index amount.

(5) direct or absolute

```
Add R1, (1001)

Regs[R1] <- Regs[R1] + Mem[1001]
```

**used**: useful for accessing static data.

(6) displacement

```
Add R4, 100(R1)

Regs[R4] <- Regs[R4] + Mem[100 + Regs[R1]]
```

**used**: accessing local variables.

(7) memory indirect

```
Add R1, @(R3)

Regs[R1] <- Regs[R1] + Mem[Mem[Regs[R3]]]
```

**used**: if R3 is the address of a pointer p, then mode yields *p.

(8) autoincrement

```
Add R1, (R2)+

Regs[R1] <- Regs[R1] + Mem[Regs[R2]]
Regs[R2] <- Regs[R2] + d
```

**used**: useful for stepping through arrays within a loop. R2 = base of array, each reference increments R2 by d.

(9) autodecrement

```
Add R1, -(R2)

Regs[R2] <- Regs[R2] - d
Regs[R1] <- Regs[R1] + Mem[Regs[R2]]
```

**used**: same as autoincrement. autoincrement/-decrement can also act as push/pop to implement a stack.

(10) scaled

```
Add R1, 100(R2)[R3]

Regs[R1] <- Regs[R1] + Mem[100 + Regs[R2] + Regs[R3] * d]
```

**used**: to index arrays.

### A.4 Type and Size of Operands

normally, encoding in the opcode designates the type of an operand.

common operand types:

- character: 8 bits,
- half word: 16 bits,
- word: 32 bits,
- signle-precision floating point: 1 word,
- double-precision floating point: 2 words.

representation:

- integer: 2's complement binary numbers,
- floating point: IEEE standard 754,
- character strings,
- packed decimal/binary-codes decimal format: 4 bits to encode 0 to 9, and 2 decimal digits are packed into each byte,
- unpacked decimal: numeric character string.

### A.5 Operations in the Instruction Set

Figure A.12 Categories of instruction operators and example of each.

- **arithmetic and logical**: integer arithmetic and logical operations add, subtract, and, or, multiply, divide.
- **data transfer**: load-stores.
- **control**: branch, jump, procedure call and return, traps.
- **system**: operating system call, virtual memory management instructions.
- **floating point**: floating-point instructions add, multiply, divide, compare.
- **decimal**: decimal add, decimal multiply, decimal-to-character conversions.
- **string**: string move, string compare, string search.
- **graphics**: pixel and vertex operation, compression/decompression operations.

### A.6 Instructions for Control Flow

4 types of control flow change:

- conditional branches,
- jumps,
- procedure calls,
- procedure returns.

**addressing modes for control flow instructions**:

- **PC-relative**: specify the destination address a control flow instruction by supplying a displacement that is added to the PC(program counter).
- **dynamic address**: (to implement returns and indirect jumps when the target is not known at compile time) specify the target dynamically. naming a register that contains the target address; the jump may permit any addressing mode to be used to supply the target address.

register indirect jumps are useful for 4 important features:

- case or switch statements,
- virtual functions or methods in object-oriented language,
- high-order functions or function pointers,
- dynamically shared libraries.

**conditional branch options**:

Figure A.16 The major methods for evaluating branch conditions, their advantages, and their disadvantages.

- condition code (CC)

*Example*: 80x86, ARM, PowerPC, SPARC, SuperH

*How condition is tested*: test special bits set by ALU operations, possibly under program control.

*adv*: sometimes condition is set for free.

*disadv*: CC is extra state. CC constrains the ordering of instructions because they pass information from on instruction to a branch.


- condition register/limited comparison

*Example*: Alpha, MIPS

*How condition is tested*: test arbitrary register with the result of a simple comparison (equality or zere tests).

*adv*: simple.

*disadv*: limited compare may affect critical path or require extra comparison for general condition.

- compare and branch

*Example*: PA-RISC, VAX, RISC-V

*How condition is tested*: compare is part of the branch. fairly general compares are allowed (greater than, less then).

*adv*: one instruction rather than two for a branch.

*disadv*: may set critical path for branch instructions.


**procedure invocation options**:

procedure calls and returns include control transfer and possibly some state saving; at a minimum the return address must be saved somewhere, sometimes in a special in a link register or just a GPR.

2 basic conventions in use to save registers:

- **caller saving**: the calling procedure must save the registers that is wants preserved for access after the call, and thus the called procedure need not worry about registers.
- **callee saving**: the called procedure must save the registers it wants to use, leving the caller unrestrained.

most real systems tody use a combinations of the 2 mechanisms, this convention is specified in an **application binary interface(ABI)**, that sets down the basic rules as to which registers should be caller saved and which should be callee saved.

### A.7 Encoding an Instruction Set

the instructions are encoded into a binary representation for execution by the processor:

- the operation is typically specified in one filed called the **opcode**,
- the important decision is how to encode the addressing modes with the operations: depends on the range of addressing modes and the degree of independence between opcodes and modes.

Figure A.18 3 basic variations in instruction encoding: variable length, fixed length, and hybrid.

- address specifier: tells what addressing mode is used to access the operand.

(a) variable: Intel 80x86, VAX

```
+---------------+------------+--------+-----+------------+--------+
|Operation and  | Address    | Address| ... | Address    | Address|
|no. of operands| specifier 1| field 1| ... | Specifier n| field n|
+---------------+------------+--------+-----+------------+--------+
```

(b) fixed: Alpha, ARM, MIPS, RISC-V, PowerPC, SPARC, SuperH

```
+---------+--------+--------+--------+
|Operation| Address| Address| Address|
|         | field 1| field 2| field 3|
+---------+--------+--------+--------+
```

(c) hybrid: IBM 460/370, microMIPS, Arm Thumb2, RISC-V Compressed(RV32IC)


```
+---------+------------+------------+
|Operation| Address    | Address    |
|         | specifier  | field      |
+---------+------------+------------+

+---------+------------+------------+------------+
|Operation| Address    | Address    | Address    |
|         | specifier 1| specifier 2| field      |
+---------+------------+------------+------------+

+---------+------------+------------+------------+
|Operation| Address    | Address    | Address    |
|         | specifier  | field 1    | field 2    |
+---------+------------+------------+------------+
```

### A.8 Cross-Cutting Issues: The Role of Compilers

A compiler writer's first goal is **correctness**, all valid programs must be compiled correctly.
The second goal is usually speed of the compiled code.
typically, a whole set of other goals follows these two.

The complexity of writing a correct compiler is a major limitation on the amount of optimization that can be done.

optimizations performed by modern compiler can be classified b the style of the transformations:

- **high-level optimizations**: are often done on the source with output fed to later optimization passes.

*Example*:

procedure integration (replace procedure call by procedure body).


- **local optimizations**: optimize code only within a straight-line code fragment(a basic block).

*Example*:

common subexpression elimination (replace tow instances of the same computation by single copy),

constant propagation (replace all instances of a variable that is assigned a constant with the constant),

stack height reduction (rearrange expression tree to minimize resource needed for expression evaluation).

- **global optimizations**: extend the local optimizations across branches and introduce a set of transformations aimed at optimizing loops.

*Example*:

global common subexpression elimination,

copy propagation (replace all instances of a variable A that has has been assigned X with X),

code motion (remove code from a loop that computes same value each iteration of the loop),

induction variable elimination (simplify/eliminate array addressing calculations within loops).

- **register allocation**: associates registers with operands.

register allocation algorithms today are based on a technique called **graph coloring** (NP-complete).

there are heuristic algorithms that work well in practice, yielding close allocations that run in near-linear time.

> Grpah coloring works best when there at least 16 (and preferably more) GPR available for global allocation for integer variables and additional registers for floating points.

- **processor-dependent optimizations**: attempt to take advantage of specific architectural knowledge.

*Example*:

strength reduction (replace multiply by a constant with adds and shifts),

pipeline scheduling (reorder instructions to improve pipeline performance),

branch offset optimization (choose the shortest branch displacement that reaches target).


**How the architect can help the compiler writer**:

some instruction set properties help the compiler wirter:

- **provide regularity**: whenever it makes sense, the 3 primary components of an instruction set (the operations, the data types, the addressing modes) should be orthogonal.
- **provide primitives, not solutions**.
- **simplify trade-offs among alternatives**.
- **provide instructions that bind the quantities known at compile time as constants**.

### A.9 Putting It All Together: The RISC-V Architecture

#### RISC-V Instruction Set Organization

The RISC-V instruction set is organized as:

- 3 base instruction sets that support 32-bit or 64-bit integers,
- a variety of optional extensions to one of the base instruction sets.

Figure A.22 RISC-V has 3 base instruction sets (and a reserved spot for a future fourth); all the extensions extend one of the base instruction sets.

|Name  | Functionality|
|:---  |:---|
|RV32I | base **32-bit integer instruction set** with 32 registers. |
|RV32E | base **32-bit instruction set** but with only 16 registers; intended for very low-end **embedded applications**. |
|RV64I | base **64-bit instruction set**; all registers are 64-bits, and instructions to move 64-bit from/to the registers (LD, SD) are added. |
|M     | add **integer multiply and divide** instructions. |
|A     | add **atomic** instructions needed for concurrent processing. |
|F     | add single precision (32-bit) IEEE **floating point**, includes 32 32-bit floating pointer registers, instructions to load and store those registers and operate on them. |
|D     | extends floating point to **double precision**, 64-bit, making the registers 64-bits, adding instructions to load, store, and operate on the registers. |
|Q     | further extends floating point to add support for **quad precision**, add 128-bit operations. |
|L     | add support for 64- and 128-bit **decimal floating point** for the IEEE standard. |
|C     | define a **compressed** version of the instruction set intended for small-memory-sized embbedded applications. define 16-bit versions of common RV32I instructions. |
|V     | a future extension to support **vector operations**. |
|B     | a future extension to support **operations on bit fields**. |
|T     | a future extension to support **transactional memory**. |
|P     | a future extension to support **packed SIMD instructions**. |
|RV128I| a future base instruction set providing **a 128-bit address space**. |

**RV64G**: the abbreviated name of RISC-V64IMAFD.


#### Registers for RISC-V

RV64G has:

- 32 64-bit integer registers (general-purpose registers, GPRs): x0, x1, ..., x31. The value of x0 is always 0.
- 32 floating-point registers(FPRs): f0, f1, ..., f31; can hold 32 single-precision (32-bit) values or 32 double-precision (64-bit) values.
- a few special registers can be transferred from/to GPRs: for example the floating-point status register.

#### Data Types for RISC-V

the data types are:

- 8-bit bytes,
- 16-bit half words,
- 32-bit words,
- 64-bit double words,
- 32-bit single precision floating point,
- 64-bit double precision floating point.

the RV64G operations work on 64-bit integers and 32- or 64-bit floating points: bytes, half words, words are loaded into GPRs with either zero or the sign bit replicated to fill the 64 bits of GPRs.

#### Addressing Modes for RISC-V Data Transfers

only 2 addressing modes are supported: immediate, displacement, both with 12-bit fields.

RV64G memory is byte addressable with 64-bit address and uses Little Endian byte numbering.

RV64G is a load-store architecture. memory accesses need not be aligned.

#### RISC-V Instruction Format

all instructions are 32 bits with a 7-bit primary opcode.

Figure A.23 The RISC-V insruction layout.

```
 31          25 24      20 19      15 14  12 11       7 6             0
+--------------+----------+----------+------+----------+--------------+
|funct7        |rs2       |rs1       |funct3|rd        |opcode        | R-type
+--------------+----------+----------+------+----------+--------------+

register-register ALU instructions
rd: destination
rs1: first source
rs2: second source

+-------------------------+----------+------+----------+--------------+
|imm[11:0]                |rs1       |funct3|imm[4:0]  |opcode        | I-type
+-------------------------+----------+------+----------+--------------+

ALU immediates load
rd: destination
rs1: first source base register
imm: value displacement

+--------------+----------+----------+------+----------+--------------+
|imm[11:5]     |rs2       |rs1       |funct3|imm[4:0]  |opcode        | S-type
+--------------+----------+----------+------+----------+--------------+

store, compare and branch
rs1: base register first source
rs2: data source to store second source
imm: displacement offset

+-------------------------------------------+----------+--------------+
|imm[31:12]                                 |rd        |opcode        | U-type
+-------------------------------------------+----------+--------------+

jump and link, jump and link register
rd: register destination for return PC
imm: target address for jump and link
```

#### RISC-V Operations

4 broad classes of instructions:

- loads and stores,
- ALU operations,
- branches and jumps,
- floating-point operations.

==Extended Notation==

- $\leftarrow_{n}$ `<-_n`: transfer an n-bit quantity.
- `x,y <- z`: z should be tranferred to x and y.
- $Regs[x4]_{0}$ `Regs[x4]_0`: the sign bit of x4. (bits are labeled from the most-significant bit starting at 0)
- $Regs[x3]_{56..63}$ `Regs[x3]_56..63`: yields the least-significant byte of x3.
- $0^{48}$ `0^48`: yields a field of zeros of length 48 bits.
- `##`: used to concatenate two fields and may appear on either side of a data transfer.
- `<<`, `>>`: shift the first operand left or right by the amount of the second operand.
- `;`: line style comments.

Figure A.25 The load and store instructions in RISC-V.

```
ld  x1, 80(x2)  ; load doubleword
Regs[x1] <- Mem[80+Regs[x2]]

lw  x1, 60(x2)  ; load word
Regs[x1] <-_64 (Mem[60+Regs[X2]]_0)^32 ## Mem[60+Regs[x2]]

lwu x1, 60(x2)  ; load word unsigned
Regs[x1] <-_64 0^32 ## Mem[60+Regs[x2]]

lb  x1, 40(x3)  ; load byte
Regs[x1] <-_64 (Mem[40+Regs[x3]]_0)^56 ## Mem[40+Regs[x3]]

lbu x1, 40(x3)  ; load byte unsigned
Regs[x1] <-_64 0^56 ## Mem[40+Regs[x3]]

lh  x1, 40(x3)  ; load half word
Regs[x1] <-_64 (Mem[40+Regs[x3]]_0)^48 ## Mem[40+Regs[x3]]

flw f0, 50(x3)  ; load FP single
Regs[f0] <-_64 Mem[50+Regs[x3]] ## 0^32

fld f0, 50(x2)  ; load FP double
Regs[f0] <-_64 Mem[50+Regs[x2]]


sd  x2, 400(x3) ; store doubleword
Mem[400+Regs[x3]] <-_64 Regs[x2]

sw  x3, 500(x4) ; store word
Mem[500+Regs[x4]] <-_32 Regs[x4]_32..63

fsw f0, 40(x3)  ; store FP single
Mem[40+Regs[x3]] <-_32 Regs[f0]_0..31

fsd f0, 40(x3)  ; store FP double
Mem[40+Regs[x3]] <-_64 Regs[f0]

sh  x3, 502(x2) ; store half
Mem[502+Regs[x2]] <-_16 Regs[x3]_48..63

sb  x2, 41(x3)  ; store byte
Mem[41+Regs[x3]] <-_8 Regs[x2]_56..63

```

Figure A.26 The basic ALU instructions in RISC-V are available both with register-register operands and with one immediate operand.

```
add  x1,x2,x3 ; add
Regs[x1] <- Regs[x2] + Regs[x3]

addi x1,x2,3  ; add immediate unsigned
Regs[x1] <- Regs[x2] + 3

lui  x1,42    ; load upper immediate, U-type 20-bit imm
Regs[x1] <- 0^32 ## 42 ## 0^12

sll  x1,x2,5  ; shift left logical
Regs[x1] <- Regs[x2] << 5

slt  x1,x2,x3 ; set less than
if (Regs[x2] < Regs[x3])
  Regs[x1] <- 1
else
  Regs[x1] <- 0
```

#### RISC-V Control Flow Instructions

Figure A.27 Typical control flow instructions in RISC-V.

```
jal  x1,offset    ; jump and link
Regs[x1] <- PC+4
PC <- PC + (offset << 1)

jalr x1,x2,offset ; jump and link register
Regs[x1] <- PC+4
PC <- Regs[x2]+offset

beq  x3,x4,offset ; branch equal zero
if (Regs[x3] == Regs[x4])
  PC <- PC + (offset << 1)

bgt  x3,x4,offset ; branch not equal zero
if (Regs[x3] > Regs[x4])
  PC <- PC + (offset << 1)
```

#### RISC-V Floating-Point Operations

Figure A.28 A list of the vast majority of instructions in RV64G.

- **data transfer**: move data between registers and memory, or between the integer and FP; only memory address mode is 12-bit displacement+contents of a GPR.

```
lb, lbu, sb ; load byte, load byte unsigned, store byte.

lh, lhu, sh ; load half word, load half word unsigned, store half word.

lw, lwu, sw ; load word, load word unsigned, store word.

ld, sd      ; load doubleword, store doubleword.
```

- **arithmetic/logical**: operations on data in GPRs. word versions ignore upper 32 bits.

```
add, addi, addw, addiw,         ; add and substract, with both word and immediate version.
sub, subi, subw, subiw

slt, sltu, slti, sltiu          ; set-less-than with signed and unsigned, and immediate.

and, or, xor,                   ; and, or, xor, both register-register and register-immediate.
andi, ori, xori

lui                             ; load upper immediate: load bits 31..12 of a register with the immediate value. Upper 32 bits are set to 0.

auipc                           ; sum an immediate and the upper 20-bits of the PC into a register.

sll, slli, sllw, slliw,         ; logical shift left and right, arithmetic shift right, both immediate and word version.
srl, srli, srlw, srliw,
sra, srai, sraw, sraiw

mul, mulw, mulh, mulhsu, mulhu  ; integer multiply, divide, and remainder, signed/unsigned/word versions.
div, divw, divu,
rem, remu, remw, remuw
```

- **control**: conditinal branches and jumps; PC-relative or through register.

```
beq, bne, blt, bge, bltu, bgeu ; branch based on compare of two registers, equal, not equal, less than, greater or equal , signed/unsigned versions.

jal, jalr                      ; jump and link address relative to a register or the PC.
```

- **floating point**: All FP operation appear in double precision (`.d`) and single (`.s`).

```
flw, fld, fsw, fsd              ; load, store word(single precision), doubleword(double precision).

fadd, fsub, fmul, fdiv, fsqrt,  ; add, subtract, multiply, divide, square root,
fmadd, fmsub, fnmadd, fnmsub    ; multiply-add, multiply-subtract, negate multiply-add, multiply-subtract,
fmin, fmax, fsgn, fsngj, fsjnx  ; minimum, maximum, instructions to replace the sign bit.
                                ; fadd.s for single precision, fadd.d for double precision.

feq, flt, fle                   ; compare two floating point registers, result is 0 or 1 stored in a GRP.

fmv.x.*, fmv.*.x                ; move between the FP and GPR. * is s or d.

fcvt.*.l, fcvt.l.*,             ; convert between a FP register and integer register. * is S or D.
fcvt.*.lu, fcvt.lu.*,           ; signed/unsigned, word, doubleword versions.
fcvt.*.w, fcvt.w.*,
fcvt.*.wu, fcvt.wu.*,
```

#### RISC-V Instruction Set Usage

Figure A.29 RISC-V dynamic instruction mix for the SPECint2006 programs.

### A.10 Fallacies and Pitfalls

> skip.

### A.11 Concluding Remarks

> skip.

### A.12 Historical Perspective and References

> skip.

## Appendix B. Review of Memory Hierarchy
### B.1 Introduction
### B.2 Cache Performance
### B.3 Six Basic Cache Optimizations
### B.4 Virtual Memory
### B.5 Protection and Examples of Virtual Memory
### B.6 Fallacies and Pitfalls
### B.7 Concluding Remarks
### B.8 Historical Perspective and References

## Appendix C. Pipelining: Basic and Intermediate Concepts
### C.1 Introduction
### C.2 The Major Hurdle of Pipelining—Pipeline Hazards
### C.3 How Is Pipelining Implemented?
### C.4 What Makes Pipelining Hard to Implement?
### C.5 Extending the RISC V Integer Pipeline to Handle Multicycle Operations
### C.6 Putting It All Together: The MIPS R4000 Pipeline
### C.7 Cross-Cutting Issues
### C.8 Fallacies and Pitfalls
### C.9 Concluding Remarks
### C.10 Historical Perspective and References


## Appendix D. Storage Systems

## Appendix E. Embedded Systems

## Appendix F. Interconnection Networks

## Appendix G. Vector Processors in More Depth

## Appendix H. Hardware and Software for VLIW and EPIC

## Appendix I. Large-Scale Multiprocessors and Scientific Applications

## Appendix J. Computer Arithmetic

## Appendix K. Survey of Instruction Set Architectures

## Appendix L. Advanced Concepts on Address Translation

## Appendix M. Historical Perspectives and References

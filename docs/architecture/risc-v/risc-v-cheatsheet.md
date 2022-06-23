# RISC-V Cheatsheet

|时间|内容|
|:---|:---|
|2022-06-19| add **Resources** and **User-Level ISA**. |
|2022-06-20| add **General Registers** and **Floating Point Registers (RV32F)** |

## Resources

### [RISC-V Specifications](https://github.com/riscv)

- [1. RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual): This repository contains the LaTeX source for the draft RISC-V Instruction Set Manual.

!!! info ""

    - 1.1 Volume I: User-Level ISA (version 20191213),
    - 1.2 Volume II: Privileged Architecture (version 20211203).

- [2. RISC-V Opcodes](https://github.com/riscv/riscv-opcodes): This repo enumerates standard RISC-V instruction opcodes and control and status registers. It also contains a script to convert them into several formats (C, Scala, LaTeX). (Accessed at 20220615)

### [RISC-V Non-ISA Specifications](https://github.com/riscv-non-isa)

- [RISC-V ELF psABI Document](https://github.com/riscv-non-isa/riscv-elf-psabi-doc): Processor-specific application binary interface document for RISC-V.

!!! info ""

    *ps* for Processor-Specific.

    Including:

    - [3. RISC-V Calling Conventions](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-cc.adoc),
    - [4. RISC-V ELF Specification](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-elf.adoc), and
    - [5. RISC-V DWARF Specification](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-dwarf.adoc).


- [6. RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md): Document for pseudoinstructions and assembly directives.
- [7. RISC-V C API](https://github.com/riscv-non-isa/riscv-c-api-doc/blob/master/riscv-c-api.md): Documentation of the RISC-V C API.
- [8. RISC-V Toolchain Conventions](https://github.com/riscv-non-isa/riscv-toolchain-conventions): Documenting the expected behaviour and supported command-line switches for GNU and LLVM based RISC-V toolchains.

### Other

- [9. GCC RISC-V Options](https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html)

## Registers

### General Registers

> *Saver*: role in the first standard calling convention.

|Register |ABI Name |Description                       |Saver      |
|:---     |:---     |:---                              |:---       |
|x0       |zero     |Hard-wired zero                   |-          |
|x1       |ra       |Return address                    |Caller     |
|x2       |sp       |Stack pointer                     |**Callee** |
|x3       |gp       |Global pointer                    |-          |
|x4       |tp       |Thread pointer                    |-          |
|x5       |t0       |Temporary/alternate link register |Caller     |
|x6-7     |t1-2     |Temporaries                       |Caller     |
|x8       |s0/fp    |Saved register/frame pointer      |**Callee** |
|x9       |s1       |Saved register                    |**Callee** |
|x10-11   |a0-1     |Function arguments/return values  |Caller     |
|x12-17   |a2-7     |Function arguments                |Caller     |
|x18-27   |s2-11    |Saved registers                   |**Callee** |
|x28-31   |t3-6     |Temporaries                       |Caller     |
|pc       |pc       |Program counter                   |-          |

### Floating Point Registers (RV32F)

> *Saver*: role in the first standard calling convention.

|Register |ABI Name |Description                       |Saver      |
|:---     |:---     |:---                              |:---       |
|f0-7     |ft0-7    |FP temporaries                    |Caller     |
|f8-9     |fs0-1    |FP saved registers                |**Callee** |
|f10-11   |fa0-1    |FP arguments/return values        |Caller     |
|f12-17   |fa2-7    |FP arguments                      |Caller     |
|f18-27   |fs2-11   |FP saved registers                |**Callee** |

### Control and Status Registers (CSRs)

> TBD.

### Vector Registers (RV32V)

> TBD.

## Instructions

!!! info ""

  	Abbreviation **G** for **IMAFDZicsr_Zifencei** combination of instruction-set extensions.

  	View instruction count: 
		
    ``` shell
    $ for ff in `ls`; do echo "$ff: `grep "???" $ff | wc -l`"; done
    ```

### User-Level ISA

!!! info ""

    Use [1.1] and [2] to generate, and notation is taken from *The RISC-V Reader: An Open Architecture Atlas*.

- `rs`: for source register
- `rd`: for destination register.
- `x[]`: for integer registers.
- `f[]`: for floating-point registers.
- `M[]`: for memory.
- `imm`: for immediate.
- `sext()`: for sign-extended.
- `AMO64()`, `AMO32()`: for Atomic Memory Operation.
- `>s`: treating the values as two's complement numbers.
- `>u`: treating the values as unsigned numbers.
- `CSRs[]`: for Control and Status Register.
- `RaiseException`: raise exceptions.
- `Fence`
- `frm`: for Floating-point Round Mode.
- `LoadReserved64`
- `LoadReserved32`
- `ExceptionReturn`
- `StoreConditional64`
- `StoreConditional32`
- `GOT`: Global Offset Table.

#### a

--8<--
architecture/risc-v/isa/a
--8<--

#### b

--8<--
architecture/risc-v/isa/b
--8<--

#### c

--8<--
architecture/risc-v/isa/c
--8<--

#### d

--8<--
architecture/risc-v/isa/d
--8<--


#### e

--8<--
architecture/risc-v/isa/e
--8<--

#### f

--8<--
architecture/risc-v/isa/f
--8<--

#### g

--8<--
architecture/risc-v/isa/g
--8<--

#### h

--8<--
architecture/risc-v/isa/h
--8<--

#### i

--8<--
architecture/risc-v/isa/i
--8<--

#### j

--8<--
architecture/risc-v/isa/j
--8<--

#### k

--8<--
architecture/risc-v/isa/k
--8<--

#### l

--8<--
architecture/risc-v/isa/l
--8<--

#### m

--8<--
architecture/risc-v/isa/m
--8<--

#### n

--8<--
architecture/risc-v/isa/n
--8<--

#### o

--8<--
architecture/risc-v/isa/o
--8<--

#### p

--8<--
architecture/risc-v/isa/p
--8<--

#### r

--8<--
architecture/risc-v/isa/r
--8<--

#### s

--8<--
architecture/risc-v/isa/s
--8<--

#### t

--8<--
architecture/risc-v/isa/t
--8<--


#### u

--8<--
architecture/risc-v/isa/u
--8<--

#### v

--8<--
architecture/risc-v/isa/v
--8<--

#### w

--8<--
architecture/risc-v/isa/w
--8<--

#### x

--8<--
architecture/risc-v/isa/x
--8<--

#### z

--8<--
architecture/risc-v/isa/z
--8<--

### Privileged Architecture

# RISC-V Cheatsheet

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

> TBD.

### General Registers
### Control and Status Registers (CSRs)
### Floating Point Registers (RV32F)
### Vector Registers (RV32V)


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

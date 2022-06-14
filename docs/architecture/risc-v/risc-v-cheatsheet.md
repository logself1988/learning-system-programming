# RISC-V Cheatsheet

## Resources

### [RISC-V Specifications](https://github.com/riscv)

- [1. RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual): This repository contains the LaTeX source for the draft RISC-V Instruction Set Manual.

!!! info ""

    - 1.1 Volume I: User-Level ISA,
    - 1.2 Volume II: Privileged Architecture.

- [2. RISC-V Opcodes](https://github.com/riscv/riscv-opcodes): This repo enumerates standard RISC-V instruction opcodes and control and status registers. It also contains a script to convert them into several formats (C, Scala, LaTeX).

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

### User-Level ISA

<!-- ISA Module Labels:
\fbox{RV32I}
\fbox{RV64I}
\fbox{Zifencei}
\fbox{Zicsr}
\fbox{RV32M}
\fbox{RV64M}
\fbox{RV32A}
\fbox{RV64A}
\fbox{RV32F}
\fbox{RV64F}
\fbox{RV32D}
\fbox{RV64D}
\fbox{RV32Q}
\fbox{RV64Q}
\fbox{Pseudo}
-->


??? summary "add rd, rs1, rs2 <br/>Add. $\fbox{RV32I} \ \fbox{RV64I}$"


    x[rd] = x[rs1] + x[rs2]

    Add register x[rs2] to register x[rs1] and writes the result to x[rd].

    Arithmetic overflow is ignored.


> TBD: use https://github.com/riscv/riscv-opcodes to generate instruction list. and use [1.1] to add pseudoinstructions.

### Privileged Architecture

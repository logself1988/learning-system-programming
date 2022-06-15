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

#### pseudoinstruction

??? question "la rd, symbol (non-PIC ) (Load absolute address, where delta = symbol − pc). $\fbox{pseudo}$"

    auipc rd, delta[31 : 12] + delta[11]
    addi rd, rd, delta[11:0]

??? question "la rd, symbol (PIC ) (Load absolute address, where delta = GOT[symbol] − pc). $\fbox{pseudo}$"

    auipc rd, delta[31 : 12] + delta[11]
    l{w|d} rd, rd, delta[11:0]

??? question "lla rd, symbol (Load local address, where delta = symbol − pc). $\fbox{pseudo}$"

    auipc rd, delta[31 : 12] + delta[11]
    addi rd, rd, delta[11:0]

??? question "l{b|h|w|d} rd, symbol (Load global). $\fbox{pseudo}$"

    auipc rd, delta[31 : 12] + delta[11]
    l{b|h|w|d} rd, delta[11:0](rd)

??? question "s{b|h|w|d} rd, symbol, rt (Store global). $\fbox{pseudo}$"

    auipc rt, delta[31 : 12] + delta[11]
    s{b|h|w|d} rd, delta[11:0](rt)

??? question "fl{w|d} rd, symbol, rt (Floating-point load global). $\fbox{pseudo}$"

    auipc rt, delta[31 : 12] + delta[11]
    fl{w|d} rd, delta[11:0](rt)

??? question "fs{w|d} rd, symbol, rt (Floating-point store global). $\fbox{pseudo}$"

    auipc rt, delta[31 : 12] + delta[11]
    fs{w|d} rd, delta[11:0](rt)

??? question "nop (No operation). $\fbox{pseudo}$"

    addi x0, x0, 0

??? question "li rd, immediate (Load immediate). $\fbox{pseudo}$"

		Myriad sequences


??? question "mv rd, rs (Copy register). $\fbox{pseudo}$"

		addi rd, rs, 0


??? question "not rd, rs (One’s complement). $\fbox{pseudo}$"

		xori rd, rs, -1


??? question "neg rd, rs (Two’s complement). $\fbox{pseudo}$"

		sub rd, x0, rs


??? question "negw rd, rs (Two’s complement word). $\fbox{pseudo}$"

		subw rd, x0, rs


??? question "sext.w rd, rs (Sign extend word). $\fbox{pseudo}$"

		addiw rd, rs, 0


??? question "seqz rd, rs (Set if = zero). $\fbox{pseudo}$"

		sltiu rd, rs, 1


??? question "snez rd, rs (Set if ̸= zero). $\fbox{pseudo}$"

		sltu rd, x0, rs


??? question "sltz rd, rs (Set if < zero). $\fbox{pseudo}$"

		slt rd, rs, x0


??? question "sgtz rd, rs (Set if > zero). $\fbox{pseudo}$"

		slt rd, x0, rs


??? question "fmv.s rd, rs (Copy single-precision register). $\fbox{pseudo}$"

		fsgnj.s rd, rs, rs



??? question "fneg.s rd, rs (Single-precision negate). $\fbox{pseudo}$"

		fsgnjn.s rd, rs, rs


??? question "fmv.d rd, rs (Copy double-precision register). $\fbox{pseudo}$"

		fsgnj.d rd, rs, rs




??? question "fneg.d rd, rs (Double-precision negate). $\fbox{pseudo}$"

		fsgnjn.d rd, rs, rs




??? question "bltz rs, offset (Branch if < zero). $\fbox{pseudo}$"

		blt rs, x0, offset




??? question "j offset (Jump). $\fbox{pseudo}$"

		jal x0, offset

??? question "jal offset (Jump and link). $\fbox{pseudo}$"

		jal x1, offset

??? question "jr rs (Jump register). $\fbox{pseudo}$"

		jalr x0, 0(rs)

??? question "jalr rs (Jump and link register). $\fbox{pseudo}$"

		jalr x1, 0(rs)

??? question "ret (Return from subroutine). $\fbox{pseudo}$"

		jalr x0, 0(x1)

??? question "tail offset (Tail call far-away subroutine). $\fbox{pseudo}$"

		auipc x6, offset[31 : 12] + offset[11]
    jalr x0, offset[11:0](x6)

??? question "fence (Fence on all memory and I/O). $\fbox{pseudo}$"

		fence iorw, iorw

??? question "rdinstret[h] rd (Read instructions-retired counter). $\fbox{pseudo}$"

		csrrs rd, instret[h], x0

??? question "rdcycle[h] rd (Read cycle counter). $\fbox{pseudo}$"

		csrrs rd, cycle[h], x0

??? question "rdtime[h] rd (Read real-time clock). $\fbox{pseudo}$"

		csrrs rd, time[h], x0

??? question "frcsr rd (Read FP control/status register). $\fbox{pseudo}$"

		csrrs rd, fcsr, x0

??? question "fscsr rd, rs (Swap FP control/status register). $\fbox{pseudo}$"

		csrrw rd, fcsr, rs

??? question "fscsr rs (Write FP control/status register). $\fbox{pseudo}$"

		csrrw x0, fcsr, rs

??? question "frrm rd (Read FP rounding mode). $\fbox{pseudo}$"

		csrrs rd, frm, x0

??? question "fsrm rd, rs (Swap FP rounding mode). $\fbox{pseudo}$"

		csrrw rd, frm, rs

??? question "fsrm rs (Write FP rounding mode). $\fbox{pseudo}$"

		csrrw x0, frm, rs

??? question "frflags rd (Read FP exception flags). $\fbox{pseudo}$"

		csrrs rd, fflags, x0

??? question "fsflags rd, rs (Swap FP exception flags). $\fbox{pseudo}$"

		csrrw rd, fflags, rs

??? question "fsflags rs (Write FP exception flags). $\fbox{pseudo}$"

		csrrw x0, fflags, rs


### Privileged Architecture

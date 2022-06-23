GCC = riscv64-unknown-elf-gcc
GAS = riscv64-unknown-elf-as
GDB = riscv64-unknown-elf-gdb
LD = riscv64-unknown-elf-ld
SIM = spike pk
SIMDASM = spike-dasm

CFLAGS = -Wall -g -Og -march=rv64g  #-v
ARCH_RV64G = -march=rv64g
ARCH_RV32I = -mabi=ilp32 -march=rv32i
LDFLAGS = 
LD_ARCH_RV32I = -m elf32lriscv

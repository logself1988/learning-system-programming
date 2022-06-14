GCC = riscv64-unknown-elf-gcc
GAS = riscv64-unknown-elf-as
GDB = riscv64-unknown-elf-gdb
SIM = spike pk
SIMDASM = spike-dasm

CFLAGS = -Wall -g -Og -march=rv64g  #-v
CFLAGS_RAW = -march=rv64g
LDFLAGS = 


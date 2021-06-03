AS_FLAG = -gstabs --32
LD_FLAG = -e _start -m elf_i386
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_syscall_write
TARGET = ex02_syscall_rtn
TARGET = ex03_syscall_sysinfo
TARGET = ex04_syscall_nanosleep
C32_TARGET = ex05_syscall_libc

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

$(C32_TARGET): $(C32_TARGET).o
	ld $(LD_C32_FLAG) -o $@ $<

$(C32_TARGET).o: $(C32_TARGET).s
	as $(AS_FLAG) -o $@ $<

clean:
	$(RM) *.o $(TARGET) $(C32_TARGET)

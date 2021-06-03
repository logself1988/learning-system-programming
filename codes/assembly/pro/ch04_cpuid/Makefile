AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C64_FLAG = -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = cpuid
TARGET = edianness
C64_TARGET = cpuid_64_c
C32_TARGET = cpuid_32_c

all: $(TARGET) $(C64_TARGET) $(C32_TARGET)
	@echo done

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

$(C64_TARGET): $(C64_TARGET).o
	ld $(LD_C64_FLAG) -o $@ $<

$(C64_TARGET).o: $(C64_TARGET).s
	as $(AS_FLAG) -o $@ $<

$(C32_TARGET): $(C32_TARGET).o
	ld $(LD_C32_FLAG) -o $@ $<

$(C32_TARGET).o: $(C32_TARGET).s
	as $(AS_32_FLAG) -o $@ $<

clean:
	$(RM) *.o $(TARGET) $(C64_TARGET) $(C32_TARGET)

# AS_FLAG = 
AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_jmp
TARGET = ex03_cmp
TARGET = ex04_flag_ZF
TARGET = ex04_flag_OF
TARGET = ex04_flag_PF
TARGET = ex04_flag_CF

TARGET_32 = 

C32_TARGET = ex02_call
C32_TARGET = ex04_flag_SF
C32_TARGET = ex05_loop
C32_TARGET = ex06_better_loop

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

$(TARGET_32): $(TARGET_32).o
	ld $(LD_C32_FLAG) -o $@ $<

$(TARGET_32).o: $(TARGET_32).s
	as $(AS_32_FLAG) -o $@ $<

$(C32_TARGET): $(C32_TARGET).o
	ld $(LD_C32_FLAG) -o $@ $<

$(C32_TARGET).o: $(C32_TARGET).s
	as $(AS_32_FLAG) -o $@ $<

clean:
	$(RM) *.o $(TARGET) $(TARGET_32) $(C32_TARGET)

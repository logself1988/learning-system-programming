AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_add
TARGET = ex01_add2
TARGET = ex01_add3
TARGET = ex03_sub
TARGET = ex03_sub2
TARGET = ex06_imul
TARGET = ex06_imul2
TARGET = ex08_sal

TARGET_32 = ex09_aaa
TARGET_32 = ex10_das

C32_TARGET = ex01_add4
C32_TARGET = ex02_adc
C32_TARGET = ex03_sub3
C32_TARGET = ex04_sbb
C32_TARGET = ex05_mul
C32_TARGET = ex07_div

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

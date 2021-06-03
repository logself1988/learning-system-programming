AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_movs
TARGET =  ex01_movs2
TARGET = ex01_movs3
TARGET = ex02_rep
TARGET = ex02_rep2
TARGET = ex02_rep3
TARGET = ex03_stos
TARGET = ex05_cmps
TARGET = ex05_cmps2
TARGET = ex06_strcomp
TARGET = ex07_scas
TARGET = ex08_str_size

TARGET_32 = none

C32_TARGET = ex04_convert

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

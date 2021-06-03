# AS_FLAG = 
AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_size1
TARGET = ex01_size2
TARGET = ex01_size3
TARGET = ex02_mem_to_reg
TARGET = ex03_reg_to_mem
TARGET = ex05_indirect_addressing
TARGET = ex07_bswap
TARGET = ex08_cmpxchg
TARGET = ex09_cmpxchg8b
TARGET = ex10_bubble

TARGET_32 = ex11_push_pop

C32_TARGET = ex04_indexed_mem_loc
C32_TARGET = ex06_cmov

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

AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = ex01_get_status
TARGET = ex02_set_prec
TARGET = ex03_fpu_stack
TARGET = ex05_fpu_math2
TARGET = ex06_frndint
TARGET = ex07_fprem1
TARGET = ex08_trig
TARGET = ex08_trig2
TARGET = ex09_fscale
TARGET = ex10_log
TARGET = ex11_fcom
TARGET = ex12_fcomi
TARGET = ex13_fcomv
TARGET = ex14_fpu_env
TARGET = ex15_fpu_save

TARGET_32 = none

C32_TARGET = ex04_fpu_math1

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

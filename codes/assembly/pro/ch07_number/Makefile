AS_FLAG = -gstabs
LD_FLAG = -e _start

TARGET = ex01_signed_int
TARGET = ex02_movzx
TARGET = ex03_movsx
TARGET = ex03_movsx2
TARGET = ex04_quad
TARGET = ex05_mmx
TARGET = ex06_sse
TARGET = ex07_bcd
TARGET = ex08_float
TARGET = ex09_fpu_values
TARGET = ex10_sse_float
TARGET = ex11_sse2_float
TARGET = ex12_conv

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

clean:
	$(RM) *.o $(TARGET)

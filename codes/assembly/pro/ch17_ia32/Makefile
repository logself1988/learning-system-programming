AS_FLAG = -gstabs
AS_32_FLAG = --32 -gstabs
LD_FLAG = -e _start
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

TARGET = mmx_add
TARGET = mmx_cmp
TARGET = sse_math
TARGET = sse_cmp
TARGET = sse2_math
C32_TARGET = features

# all: $(TARGET) $(C32_TARGET)
# 	@echo done

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

$(C32_TARGET): $(C32_TARGET).o
	ld $(LD_C32_FLAG) -o $@ $<

$(C32_TARGET).o: $(C32_TARGET).s
	as $(AS_32_FLAG) -o $@ $<

clean:
	$(RM) *.o $(TARGET) $(C32_TARGET)

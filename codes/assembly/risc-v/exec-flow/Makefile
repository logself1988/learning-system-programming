include ../common.mk

TARGET = array_largest.s

all: $(TARGET)

array_largest.s: array_largest.c
	$(GCC) $(ARCH_RV32I) -S -o $@ $<

clean:
	$(RM) $(TARGET)
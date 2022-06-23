include ../common.mk

TARGET = main.x

all: $(TARGET)

main.x: main.c func.c
	$(GCC) $(ARCH_RV32I) -S main.c -o main.s
	$(GCC) $(ARCH_RV32I) -S func.c -o func.s
	$(GAS) $(ARCH_RV32I) main.s -o main.o
	$(GAS) $(ARCH_RV32I) func.s -o func.o
	$(LD) $(LD_ARCH_RV32I) main.o func.o -o $@

clean:
	$(RM) $(TARGET) main.s func.s main.o func.o
include ../common.mk

TARGET = hello hello.s myhello func.s

all: $(TARGET)

hello: hello.c
	$(GCC) $(CFLAGS) -o $@ $<

hello.s: hello.c
	$(GCC) $(ARCH_RV64G) -S -o $@ $<

func.s: func.c
	$(GCC) $(ARCH_RV64G) -S -o $@ $<

run: hello
	$(SIM) $<

run2: hello.s
	$(GCC) $(ARCH_RV64G) -o hello $<
	$(SIM) hello

myhello: myhello.s
	$(GCC) $(ARCH_RV64G) -o $@ $<
	$(SIM) $@

clean:
	$(RM) $(TARGET)
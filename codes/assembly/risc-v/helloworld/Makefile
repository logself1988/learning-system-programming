include ../common.mk

TARGET = hello hello.s myhello func.s

all: $(TARGET)

hello: hello.c
	$(GCC) $(CFLAGS) -o $@ $<

hello.s: hello.c
	$(GCC) $(CFLAGS_RAW) -S -o $@ $<

func.s: func.c
	$(GCC) $(CFLAGS_RAW) -S -o $@ $<

run: hello
	$(SIM) $<

run2: hello.s
	$(GCC) $(CFLAGS_RAW) -o hello $<
	$(SIM) hello

myhello: myhello.s
	$(GCC) $(CFLAGS_RAW) -o $@ $<
	$(SIM) $@

clean:
	$(RM) $(TARGET)
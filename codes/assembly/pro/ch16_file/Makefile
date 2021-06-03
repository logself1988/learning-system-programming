AS_FLAG = -gstabs --32
LD_FLAG = -e _start -m elf_i386

TARGET = ex01_cpuidfile
TARGET = ex02_read
TARGET = ex02_read2
TARGET = ex02_read3

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

fileconvert: fileconvert.s sizefunc.s convert.s
	as $(AS_FLAG) -o sizefunc.o sizefunc.s
	as $(AS_FLAG) -o convert.o convert.s
	as $(AS_FLAG) -o fileconvert.o fileconvert.s
	ld $(LD_FLAG) -o $@ fileconvert.o sizefunc.o convert.o

clean:
	$(RM) *.o $(TARGET) fileconvert

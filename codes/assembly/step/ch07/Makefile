# 64
NASM_FLAG = -f elf64 -g -F stabs
LD_FLAG = -m elf_x86_64
# 32
NASM_FLAG = -f elf32 -g -F stabs
LD_FLAG = -m elf_i386

TARGET = sandbox

$(TARGET): $(TARGET).asm
	nasm $(NASM_FLAG) $< -o $(TARGET).o
	ld $(LD_FLAG) -o $@ $(TARGET).o

clean:
	rm -rf *.o $(TARGET)

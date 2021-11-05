#NASM_FLAG = -f elf64 -g -F stabs
NASM_FLAG = -f elf64 -g -F dwarf
LD_FLAG = -m elf_x86_64

# library
#LIBS = ../lib/lib.o
LIBS = 

# target in subdirectory
TARGET = 

# %: %.asm
# 	nasm $(NASM_FLAG) $< -o $@.o
# 	ld $(LD_FLAG) -o $@ $@.o

%.o: %.asm
	nasm $(NASM_FLAG) $< -o $@

%: %.o
	ld $(LD_FLAG) -o $@ $< $(LIBS)

clean:
	$(RM) *.o $(TARGET)
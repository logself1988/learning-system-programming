# distinguish platform
PLATFORM=$(shell ../systype.sh)

ifeq "$(PLATFORM)" "linux"
#NASM_FLAG = -f elf64 -g -F stabs
NASM_FLAG = -f elf64 -g -F dwarf
LD_FLAG = -m elf_x86_64
endif
ifeq "$(PLATFORM)" "macos"
NASM_FLAG = -g -f macho64 -DMACOS
#LD_FLAG = -macosx_version_min 10.15.7 -lSystem -e _start
LD_FLAG = -lSystem -e _start
endif

# library
#LIBS = ../lib/lib.o
LIBS = 

# target in subdirectory
TARGET = 

# %: %.asm
# 	nasm $(NASM_FLAG) $< -o $@.o
# 	ld $(LD_FLAG) -o $@ $@.o

# NOT remove intermediate file in chained rules
.SECONDARY:

%.o: %.asm
	nasm $(NASM_FLAG) $< -o $@

%: %.o
	ld $(LD_FLAG) -o $@ $< $(LIBS)

clean:
	$(RM) *.o $(TARGET)
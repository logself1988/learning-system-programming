AS_FLAG = -gstabs --32
LD_FLAG = -e _start -m elf_i386
LD_C32_FLAG = --dynamic-linker /lib/ld-linux.so.2 -m elf_i386 -lc

# TARGET = ex01_area_test
# TARGET = ex02_area_test
# TARGET = ex03_area_test
# TARGET = area
# C32_TARGET = ex05_cmd_args
# C32_TARGET = ex06_env_vars
C32_TARGET = ex07_use_cmd_args

$(TARGET): $(TARGET).o
	ld $(LD_FLAG) -o $@ $<

$(TARGET).o: $(TARGET).s
	as $(AS_FLAG) -o $@ $<

$(C32_TARGET): $(C32_TARGET).o
	ld $(LD_C32_FLAG) -o $@ $<

$(C32_TARGET).o: $(C32_TARGET).s
	as $(AS_FLAG) -o $@ $<

area: ex04_area_test.s area.s
	as $(AS_FLAG) -o area.o area.s
	as $(AS_FLAG) -o ex04_area_test.o ex04_area_test.s
	ld $(LD_FLAG) -o $@ ex04_area_test.o area.o

areaclean:
	$(RM) *.o area

clean:
	$(RM) *.o $(TARGET) $(C32_TARGET)

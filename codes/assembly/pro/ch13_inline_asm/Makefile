C_FLAG = -m32

C_TARGET = ex01_asm
C_TARGET = ex02_global
C_TARGET = ex03_reg
C_TARGET = ex04_movs
C_TARGET = ex05_reg
C_TARGET = ex06_reg
C_TARGET = ex07_alt
C_TARGET = ex08_changed
C_TARGET = ex09_mem
C_TARGET = ex10_sincos
C_TARGET = ex11_area
C_TARGET = ex12_jump
C_TARGET = ex12_jump2
C_TARGET = ex13_macro

$(C_TARGET): $(C_TARGET).c
	gcc $(C_FLAG) -o $@ $<

clean:
	$(RM) *.o $(C_TARGET) $(C_TARGET).s

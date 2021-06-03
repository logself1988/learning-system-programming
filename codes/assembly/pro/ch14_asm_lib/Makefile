AS_FLAG = -gstabs --32
C_FLAG = -Wall -m32 -g
CPP_FLAG = -Wall -m32 -g

TARGETS = mainprog \
	square_main \
	cpuid_main \
	area_main \
	greater_main \
	goodprog \
	fpumath_main \
	extern_main

all: $(TARGETS)
	@echo done

mainprog: mainprog.c asmfunc.s
	# gcc -m32 -o mainprog mainprog.c asmfunc.s
	as $(AS_FLAG) -o asmfunc.o asmfunc.s
	gcc $(C_FLAG) -o $@ mainprog.c asmfunc.o

square_main: square_main.c square.s
	as $(AS_FLAG) -o square.o square.s
	gcc $(C_FLAG) -o $@ square_main.c square.o

cpuid_main: cpuid_main.c cpuidfunc.s
	as $(AS_FLAG) -o cpuidfunc.o cpuidfunc.s
	gcc $(C_FLAG) -o $@ cpuid_main.c cpuidfunc.o

area_main: area_main.c areafunc.s
	as $(AS_FLAG) -o areafunc.o areafunc.s
	gcc $(C_FLAG) -o $@ area_main.c areafunc.o

greater_main: greater_main.c greater.s
	as $(AS_FLAG) -o greater.o greater.s
	gcc $(C_FLAG) -o $@ greater_main.c greater.o

goodprog: goodprog.c testfunc.s
	as $(AS_FLAG) -o testfunc.o testfunc.s
	gcc $(C_FLAG) -o $@ goodprog.c testfunc.o

fpumath_main: fpumath_main.c fpumathfunc.s
	as $(AS_FLAG) -o fpumathfunc.o fpumathfunc.s
	gcc $(C_FLAG) -o $@ fpumath_main.c fpumathfunc.o

extern_main: extern_main.cpp square.s areafunc.s cpuidfunc.s
	as $(AS_FLAG) -o square.o square.s
	as $(AS_FLAG) -o areafunc.o areafunc.s
	as $(AS_FLAG) -o cpuidfunc.o cpuidfunc.s
	g++ $(CPP_FLAG) -o $@ extern_main.cpp square.o areafunc.o cpuidfunc.o

libch14: square_main cpuid_main area_main greater_main fpumath_main
	ar r $@.a square.o cpuidfunc.o areafunc.o greater.o fpumathfunc.o

fpumath_main_withlib: libch14
	gcc $(C_FLAG) -o $@ fpumath_main.c libch14.a

libsch14: square_main cpuid_main area_main greater_main fpumath_main
	gcc -shared $(C_FLAG) -o $@.so square.o cpuidfunc.o areafunc.o greater.o fpumathfunc.o

fpumath_main_withlibs: libsch14
	gcc $(C_FLAG) -o $@ fpumath_main.c -L . -lsch14 

clean:
	$(RM) *.o $(TARGETS) *.a *.so fpumath_main_withlib fpumath_main_withlibs

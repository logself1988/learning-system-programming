// clang sum.c -emit-llvm -c -o sum.bc

// # generate assembly code
// llc sum.bc -o sum.s

// # generate object code
// llc sum.bc -filetype=obj -o sum.o

// # view llc supported architecture
// llc -version

// # generate MIPS object code
// llc -march=mips -filetype=obj sum.bc -o sum.o

int sum(int a, int b)
{
    return a + b;
}
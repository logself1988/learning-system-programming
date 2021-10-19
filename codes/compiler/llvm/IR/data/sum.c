// clang sum.c -emit-llvm -c -o sum.bc
// clang sum.c -emit-llvm -S -c -o sum.ll
// llvm-as sum.ll -o sum.bc
// llvm-dis sum.bc -o sum.ll
// llvm-extract -func=sum sum.bc -o sum-fn.bc

int sum(int a, int b)
{
    return a + b;
}
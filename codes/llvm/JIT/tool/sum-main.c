// $ clang -emit-llvm -c sum-main.c -o sum-main.bc
// $ lli sum-main.bc
// sum: 12
// $ lli -force-interpreter sum-main.bc
// sum: 12

#include <stdio.h>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    printf("sum: %d\n", sum(2, 3) + sum(3, 4));
    return 0;
}
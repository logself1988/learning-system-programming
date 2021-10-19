// $ clang -Xclang -ast-dump hello.c
// $ clang -cc1 -ast-dump hello.c
// $ clang -cc1 --help

// $ clang hello.c -###


#include <stdio.h>

int main()
{
    printf("Hello, World!\n");
    return 0;
}
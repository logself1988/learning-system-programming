/* An example of setting registers in the changed registers list*/
#include <stdio.h>

int main(int argc, char **argv)
{
    int data1 = 10;
    int result = 20;

    asm("movl %1, %%eax\n\t"
        "addl %%eax, %0"
        : "=r"(result)
        : "r"(data1), "0"(result)
        : "%eax");
    
    printf("The result is %d\n", result);
    return 0;
}

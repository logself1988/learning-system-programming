/* An example of using jumps in inline assembly */
#include <stdio.h>

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    int result;

    asm("cmp %1, %2\n\t"
        "jge greater\n\t"
        "movl %1, %0\n\t"
        "jmp end\n"
        "greater:\n\t"
        "movl %2, %0\n"
        "end:"
        : "=r"(result)
        : "r"(a), "r"(b));
    printf("The larger value is %d\n", result);
    return 0;
}

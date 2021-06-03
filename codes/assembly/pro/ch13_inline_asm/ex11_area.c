/* An example of using floating point registers */
#include <stdio.h>

int main(int argc, char **argv)
{
    int radius = 10;
    float area;

    asm("fild %1\n\t"
        "fimul %1\n\t"
        "fldpi\n\t"
        "fmul %%st(1), %%st(0)"
        : "=t"(area)
        : "m"(radius)
        : "%st(1)");
    printf("The area is %f\n", area);
    return 0;
}

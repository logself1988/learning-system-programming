/* An example of returing a string value */
#include <stdio.h>

char *cpuidfunc(void);

int main(int argc, char **argv)
{
    char *spValue;
    spValue = cpuidfunc();
    printf("The CPUID is: '%s'\n", spValue);
    return 0;
}

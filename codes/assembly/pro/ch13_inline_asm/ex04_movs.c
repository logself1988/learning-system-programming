/* An example of instructions with only input values */
#include <stdio.h>

int main(int argc, char **argv)
{
    char input[30] = "This is a test message.\n";
    char output[30];
    int length = 25;

    asm volatile ("cld\n\t"
        "rep movsb"
        :
        : "S"(input), "D"(output), "c"(length));
    printf("%s\n", output);
    return 0;
}

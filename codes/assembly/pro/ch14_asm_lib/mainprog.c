/* An example of calling an assembly function*/
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("This is a test.\n");
    asmfunc();
    printf("Now for the second time.\n");
    asmfunc();
    printf("This completes the test.\n");
    return 0;
}

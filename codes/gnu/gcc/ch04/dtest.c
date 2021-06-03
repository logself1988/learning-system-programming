#include <stdio.h>

int main(int argc, char **argv)
{
#ifdef TEST
    printf("Test mode\n");
#endif
    printf("Running...\n");
    return 0;
}
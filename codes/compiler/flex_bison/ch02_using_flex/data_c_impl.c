/* data implementation file */

#include "data_c_header.h"

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char **argv)
{
    printf("%d\n", add(1,2));
    printf("%d\n", sub(2,1));

    return 0;
}

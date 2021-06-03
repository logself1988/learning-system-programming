/* An example of using multiple input values*/
#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 10;
    int j = 20;
    int k = greater(i, j);
    printf("The larger value is %d\n", k);
    return 0;
}

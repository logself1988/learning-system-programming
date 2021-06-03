/* An example of passing input values in the proper order */
#include <stdio.h>

double testfunc(double, int);

int main(int argc, char **argv)
{
    double data1 = 3.14159;
    int data2 = 10;
    double result;

    result = testfunc(data1, data2);
    printf("The result is %f\n", result);
    return 0;
}

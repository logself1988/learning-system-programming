/* An example of using floating point return value */
#include <stdio.h>

float areafunc(int);

int main(int argc, char **argv)
{
    int radius = 10;
    float result;
    result = areafunc(radius);
    printf("The result is %f\n", result);

    result = areafunc(2);
    printf("The result is %f\n", result);

    return 0;
}

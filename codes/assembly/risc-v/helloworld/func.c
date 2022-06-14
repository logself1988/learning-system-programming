#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main(int argc, char const *argv[])
{
    int a = sum(3, 4);
    printf("result=%d\n", a);
    return 0;
}

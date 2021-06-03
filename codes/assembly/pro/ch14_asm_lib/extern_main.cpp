#include <iostream>

extern "C" {
    int square(int);
    float areafunc(int);
    char *cpuidfunc(void);
}

int main(int argc, char **argv)
{
    using namespace std;

    int radius = 10;
    int radsquare = square(radius);
    cout << "The radius square is " << radsquare << endl;

    float result;
    result = areafunc(radius);
    cout << "The area is " << result << endl;

    cout << "The CPUID is " << cpuidfunc() << endl;
    return 0;
}
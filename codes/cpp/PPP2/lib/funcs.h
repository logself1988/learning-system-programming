#ifndef LIB_FUNCS
#define LIB_FUNCS

#include <cmath>

double
one (double)
{
  return 1;
}

double
slope (double x)
{
  return x / 2;
}

double
square (double x)
{
  return x * x;
}

double
sloping_cos (double x)
{
  return cos (x) + slope (x);
}

//! n!
int
fac (int n)
{
  int r = 1;
  while (n > 1)
    {
      r *= n;
      --n;
    }
  return r;
}

//! nth term of series of e^x
double
term (double x, int n)
{
  return pow (x, n) / fac (n);
}

double
expe (double x, int n)
{
  double sum = 0;
  for (int i = 0; i < n; i++)
    sum += term (x, i);
  return sum;
}

#endif /* LIB_FUNCS */

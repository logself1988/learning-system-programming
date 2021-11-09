#include <stdio.h>

#define x1 "Hello"
#define x2 " World"

#define str(i) x##i

int
main (int argc, char const *argv[])
{
  puts (str (1));
  puts (str (2));
  return 0;
}

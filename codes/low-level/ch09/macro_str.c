#include <stdio.h>

// #define mystr hello
// #define res #mystr
#define res(token) #token

int
main (int argc, char const *argv[])
{
  // puts (res);
  puts (res (hello));
  return 0;
}

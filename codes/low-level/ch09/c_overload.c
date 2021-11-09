#include <stdio.h>

// c11 macro _Generic: expand on the argument type
#define print_fmt(x) (_Generic((x), int : "%d", double : "%f", default : "%x"))

#define print(x)                                                              \
  printf (print_fmt (x), x);                                                  \
  puts ("")

int
main (int argc, char const *argv[])
{
  int x = 101;
  double y = 42.42;

  print (x);
  print (y);
  return 0;
}

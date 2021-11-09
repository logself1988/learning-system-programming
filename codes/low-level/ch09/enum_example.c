#include <stdio.h>

enum light
{
  RED,
  RED_AND_YELLOW,
  YELLOW,
  GREEN,
  NOTHING
};

int
main (int argc, char const *argv[])
{
  enum light l = NOTHING;
  printf ("%d\n", l);

  return 0;
}

#include <stdio.h>

union dword
{
  int integer;
  short shorts[2];
};

int
main (int argc, char const *argv[])
{
  union dword test;
  test.integer = 0xAABBCCDD;

  printf ("%x, %x %x\n", test.integer, test.shorts[0], test.shorts[1]);

  return 0;
}

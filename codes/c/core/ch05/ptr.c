#include <stdio.h>

int _strlen (char[]); // array

int
main (int argc, char *argv[])
{
  printf ("_strlen(\"hello, world\")=%d\n", _strlen ("hello, world"));

  return 0;
}

int
_strlen (char *s) // pointer
{
  char *p = s;

  while (*p != '\0')
    p++;

  return p - s; // pointer arithmetic
}
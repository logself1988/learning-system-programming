#include <stdio.h>

void swap (int *, int *);

int
main (int argc, char *argv[])
{
  int a, b;

  a = 1;
  b = 2;
  printf ("before: a=%d, b=%d\n", a, b);

  swap (&a, &b);

  printf ("after: a=%d, b=%d\n", a, b);

  return 0;
}

void
swap (int *px, int *py)
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}

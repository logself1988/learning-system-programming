#include <stdio.h>

#define forever for (;;)
#define max(A, B) ((A) > (B) ? (A) : (B))
#define dprint(expr) printf (#expr " = %g\n", expr)
#define paste(front, back) front##back

int
main (int argc, char *argv[])
{
  printf ("MAX((1+1),3)=%d\n", max ((1 + 1), 3));
  double x = 1.0, y = 2.0;
  dprint (x + y);

  int paste (x, y) = 1234; // new name
  printf ("%d\n", paste (x, y));

  return 0;
}

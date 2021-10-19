#include <stdio.h>

#define MAXVAL 100         // stack max size
static int sp = 0;         // next free pos in stack
static double val[MAXVAL]; // value stack

void
_push (double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf ("error: statck full, cannot push %g\n", f);
}

double
_pop (void)
{
  if (sp > 0)
    return val[--sp];
  else
    {
      printf ("error: stack empty\n");
      return 0.0;
    }
}
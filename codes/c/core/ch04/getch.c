#include <stdio.h>

#define BUFSIZE 100
static char buf[BUFSIZE]; // buffer for _ungetch(int)
static int bufp = 0;      // next free pos in buf

int
_getch (void)
{
  return (bufp > 0) ? buf[--bufp] : getchar ();
}

void
_ungetch (int c)
{
  if (bufp >= BUFSIZE)
    printf ("_ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
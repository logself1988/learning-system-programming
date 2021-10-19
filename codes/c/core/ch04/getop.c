#include "calc.h"
#include <ctype.h>
#include <stdio.h>

int
_getop (char s[])
{
  int i, c;
  while ((s[0] = c = _getch ()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit (c) && c != '.') // not a num
    return c;

  i = 0;
  if (isdigit (c))
    {
      while (isdigit (s[++i] = c = _getch ()))
        ;
    }
  if (c == '.') // decimal fraction
    {
      while (isdigit (s[++i] = c = _getch ()))
        ;
    }
  s[i] = '\0';
  if (c != EOF)
    _ungetch (c);
  return NUMBER;
}
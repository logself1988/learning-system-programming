
#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 // max length for op and num

// 逆波兰计算器
int
main (int argc, char *argv[])
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = _getop (s)) != EOF)
    {
      switch (type)
        {
        case NUMBER:
          _push (atof (s));
          break;
        case '+':
          _push (_pop () + _pop ());
          break;
        case '*':
          _push (_pop () * _pop ());
          break;
        case '-':
          op2 = _pop ();
          _push (_pop () - op2);
          break;
        case '/':
          op2 = _pop ();
          if (op2 == 0.0)
            printf ("error: zero divisor\n");
          else
            _push (_pop () / op2);
          break;
        case '\n':
          printf ("\t%.8g\n", _pop ()); // line evaluator
          break;
        default:
          printf ("error: unknown command %s\n", s);
          break;
        }
    }

  return 0;
}
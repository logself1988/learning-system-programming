#include <stdarg.h> // 变长参数表
#include <stdio.h>

void print (char *fmt, ...);

int
main (int argc, char *argv[])
{

  print ("%d %f %s\n", 1, 2.0, "hello, world");
  return 0;
}

void
print (char *fmt, ...)
{
  va_list ap; // point to varargs
  char *p, *sval;
  int ival;
  double dval;

  va_start (ap, fmt); // ap point to first vararg
  for (p = fmt; *p; p++)
    {
      if (*p != '%')
        {
          putchar (*p);
          continue;
        }

      switch (*++p)
        {
        case 'd':
          ival = va_arg (ap, int); // got typed value
          printf ("%d", ival);
          break;
        case 'f':
          dval = va_arg (ap, double);
          printf ("%f", dval);
          break;
        case 's':
          for (sval = va_arg (ap, char *); *sval; sval++)
            putchar (*sval);
          putchar ('\0');
          break;
        default:
          putchar (*p);
          break;
        }
    }

  va_end (ap); // clean up
}
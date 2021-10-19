#include <float.h>
#include <limits.h>
#include <stdio.h>

// 字符
#define VTAB '\013'
#define VBELL '\007'
#define VTAB2 '\xb'
#define VBELL2 '\x7'

// 枚举
enum boolean
{
  false,
  true
};

enum escapes
{
  BELL = '\a',
  BACKSPACE = '\b',
  TAB = '\t',
  NEWLINE = '\n',
  VVTAB = '\v',
  RETURN = '\r'
};

enum months
{
  JAN = 1,
  FEB,
  MAR,
  APR,
  MAY,
  JUN,
  JUL,
  AUG,
  SEP,
  OCT,
  NOV,
  DEC
};

// sizeof 对象
// sizeof(类型)

int
main (int argc, char *argv[])
{
  // 字符型char, 整型int, 单精度浮点型float, 双精度浮点型double
  // 限定整型: short[ int], long[ int]
  // 限定字符型和整型: singned, unsigned
  // 高精度的浮点型: long double
  printf ("sizeof(char)=%lu\n", sizeof (char));
  printf ("sizeof(int)=%lu\n", sizeof (int));
  printf ("sizeof(float)=%lu\n", sizeof (float));
  printf ("sizeof(double)=%lu\n", sizeof (double));
  printf ("sizeof(short int)=%lu\n", sizeof (short int));
  printf ("sizeof(long int)=%lu\n", sizeof (long int));
  printf ("sizeof(signed int)=%lu\n", sizeof (signed int));
  printf ("sizeof(unsigned int)=%lu\n", sizeof (unsigned int));
  printf ("sizeof(long double)=%lu\n", sizeof (long double));

  printf ("INT_MIN=%d, INT_MAX=%d\n", INT_MIN, INT_MAX);

  printf ("%d \n", 1234);
  printf ("%ld \n", 1234L);
  printf ("%d %d %ld %ld\n", 1234u, 1234U, 1234ul, 1234UL);
  printf ("%f %f %f %f %Lf %Lf\n", //
          123.4, 1e-2, 123.4f, 123.4F, 123.4l, 123.4L);
  printf ("%d %d %d %d %ld %ld\n", 31, 037, 0x1f, 0x1F, 0x1FL, 0x1FUL);

  printf ("%c %c %c %c %c\n", '0', 'a', 'z', 'A', 'Z');
  printf ("%c %c %c %c\n", VTAB, VTAB2, VBELL, VBELL2);

  printf ("%s %s\n", "I am a string",
          "hello,"
          " world");

  printf ("%d %d %d\n", true, BELL, JAN);

  const double e = 2.71828182845905;
  const char msg[] = "warning: ";
  // msg[1] = 'c'; // ERROR: expression must be a modifiable lvalueC/C++(137)
  printf ("%f %s\n", e, msg);

  return 0;
}

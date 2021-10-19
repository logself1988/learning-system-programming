#include <stdio.h>
#include <string.h>

// 控制流
// 1. if[[-else if]-else]
// 2. switch
// 3. while
// 4. for
// 5. do-while
// 6. break, continue
// 7. goto and label

// search x in v[0]<=v[1]<=...<=v[n-1]
int binsearch (int x, int v[], int n);
int same_element (int a[], int as, int b[], int bs);
void _itoa (int n, char s[]);

int
main (int argc, char *argv[])
{
  const int nn = 9;
  int v[nn] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  printf ("binsearch(2, v, %d)=%d\n", nn, binsearch (2, v, nn));

  const int m = 5, n = 5;
  int a[m] = { 1, 2, 3, 4, 5 };
  int b[n] = { 9, 8, 7, 6, 5 };
  printf ("same_element(a,b)=%d\n", same_element (a, m, b, n));

  int nv = -1234;
  char s[6];
  _itoa (nv, s);
  printf ("s=%s\n", s);

  // 2. switch
  // 4. for
  // 6. break, continue
  int c, i, nwhite, nother, ndigits[10];
  nwhite = nother = 0;

  printf ("v > 5 =");
  for (i = 0; i < nn; i++)
    {
      if (v[i] <= 5)
        continue;

      printf (" %d", v[i]);
    }
  printf ("\n");

  for (i = 0; i < 10; i++)
    ndigits[i] = 0;
  while ((c = getchar ()) != EOF)
    {
      switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          ndigits[c - '0']++;
          break;
        case ' ':
        case '\n':
        case '\t':
          nwhite++;
          break;
        default:
          nother++;
          break;
        }
    }
  printf ("digits =");
  for (i = 0; i < 10; i++)
    printf (" %d", ndigits[i]);
  printf (", white space = %d, other = %d\n", nwhite, nother);

  return 0;
}

// 1. if[[-else if]-else]
// 3. while
int
binsearch (int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high)
    {
      mid = (low + high) / 2;
      if (x < v[mid])
        high = mid - 1;
      else if (x > v[mid])
        low = mid + 1;
      else
        return mid;
    }

  return -1;
}

// 7. goto and label
int
same_element (int a[], int as, int b[], int bs)
{
  int i, j;
  for (i = 0; i < as; i++)
    for (j = 0; j < bs; j++)
      if (a[i] == b[j])
        goto found;
  return 0;

found:
  printf ("Found same element: %d (a[%d]==b[%d])\n", a[i], i, j);
  return 1;
}

void
reverse (char s[])
{
  int c, i, j;

  for (i = 0, j = strlen (s) - 1; i < j; i++, j--)
    {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
}

// 5. do-while
void
_itoa (int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0)
    n = -n;

  i = 0;
  do
    {
      s[i++] = n % 10 + '0';
    }
  while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse (s);
}
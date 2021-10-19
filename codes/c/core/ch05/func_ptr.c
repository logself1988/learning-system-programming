#include <stdio.h>

void _qsort (int v[], int left, int right,
             int (*cmp) (int, int)); // function pointer
void _swap (int v[], int i, int j);
int _numcmp (int, int);
void _print_array (char *s, int a[], int n);

int
main (int argc, char *argv[])
{
  int a[6] = { 1, 6, 4, 8, 3, 2 };

  _print_array ("before", a, 6);
  _qsort (a, 0, 5, _numcmp); // pass function name
  _print_array ("after", a, 6);

  return 0;
}

void
_qsort (int v[], int left, int right, int (*cmp) (int, int))
{
  int i, last;
  if (left >= right)
    return;

  _swap (v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*cmp) (v[i], v[left]) < 0)
      _swap (v, ++last, i);

  _swap (v, left, last);

  _qsort (v, left, last - 1, cmp);
  _qsort (v, last + 1, right, cmp);
}

void
_swap (int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int
_numcmp (int m, int n)
{
  if (m < n)
    return -1;
  else if (m > n)
    return 1;
  else
    return 0;
}

void
_print_array (char *s, int a[], int n)
{
  printf ("%s: ", s);
  int i;
  for (i = 0; i < n - 1; i++)
    printf ("%d ", a[i]);
  printf ("%d\n", a[i]);
}

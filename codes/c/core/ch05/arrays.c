#include <stdio.h>

// 2-dim array
static char daytab[2][13] = {
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

int _leap (int year);
int _day_of_year (int year, int month, int day);
void _month_day (int year, int yearday, int *pmonth, int *pday);

int
main (int argc, char *argv[])
{
  int year, month, day, yearday;
  year = 2021;
  month = 10;
  day = 19;
  yearday = _day_of_year (year, month, day);
  printf ("_day_of_year(%d,%d,%d)=%d\n", year, month, day, yearday);

  int pmonth, pday;
  _month_day (year, yearday, &pmonth, &pday);
  printf ("month=%d, day=%d\n", pmonth, pday);

  return 0;
}

int
_leap (int year)
{
  return year % 4 == 8 && year % 100 != 0 || year % 400 == 0;
}

int
_day_of_year (int year, int month, int day)
{
  int i, leap;
  leap = _leap (year);
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

void
_month_day (int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  leap = _leap (year);
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
#include "Chrono.h"

namespace Chrono
{
const int max_days_in_month[]
    = { 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool
leapyear (int y)
{
  // ref: https://en.wikipedia.org/wiki/Leap_year

  if (y % 4 != 0)
    {
      return false;
    }
  else if (y % 100 != 0)
    {
      return true;
    }
  else if (y % 400 != 0)
    {
      return false;
    }
  else
    {
      return true;
    }
}

int
max_day_in_month (int y, Month m)
{
  if (Month::feb == m)
    {
      bool is_leap_year = leapyear (y);
      if (leapyear (y))
        return 29;
      else
        return 28;
    }
  else
    {
      return max_days_in_month[int (m) - 1];
    }
}

/// member function definitions
Date::Date (int yy, Month mm, int dd) : y{ yy }, m{ mm }, d{ dd }
{
  if (!is_date (yy, mm, dd))
    throw Invalid{};
}

const Date &
default_date ()
{
  static Date dd{ 2001, Month::jan, 1 };
  return dd;
}

Date::Date ()
    : y{ default_date ().year () }, m{ default_date ().month () }, d{
        default_date ().day ()
      }
{
}

void
Date::add_day (int n)
{
  int max_day = max_day_in_month (y, m);
  int dd = d + n;
  if (dd > max_day)
    {
      while (dd > max_day)
        {
          dd -= max_day;
          add_month (1);
          max_day = max_day_in_month (y, m);
        }
    }

  d = dd;
}

void
Date::add_month (int n)
{
  int mm = int (m) + n;
  if (mm > 12)
    {
      while (mm > 12)
        {
          mm -= 12;
          add_year (1);
        }
    }
  m = Month (mm);
}

void
Date::add_year (int n)
{
  if (m == Month::feb && d == 29 && !leapyear (y + n))
    {
      m = Month::mar;
      d = 1;
    }
  y += n;
}

/// helper function definitions

bool
is_date (int y, Month m, int d)
{
  if (d <= 0)
    return false;
  if (m < Month::jan || Month::dec < m)
    return false;

  int days_in_month = max_day_in_month (y, m);
  if (days_in_month < d)
    return false;

  return true;
}

bool
operator== (const Date &a, const Date &b)
{
  return a.year () == b.year () && a.month () == b.month ()
         && a.day () == b.day ();
}

bool
operator!= (const Date &a, const Date &b)
{
  return !(a == b);
}

ostream &
operator<< (ostream &os, const Date &d)
{
  return os << '(' << d.year () << ',' << int (d.month ()) << ',' << d.day ()
            << ')';
}

istream &
operator>> (istream &is, Date &dd)
{
  int y, m, d;
  char ch1, ch2, ch3, ch4;
  is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
  if (!is)
    return is;
  if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
    {
      is.clear (ios_base::failbit);
      return is;
    }

  dd = Date (y, Month (m), d);
  return is;
}

WeekDay
day_of_week (const Date &d)
{
  // ref: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
  // Gauss's algorithm: R(D+m+5R(A-1,4)+4R(A-1,100)+6R(A-1,400),7)

  // Jan	Feb	Mar	Apr	May	Jun	Jul	Aug	Sep
  // Oct Nov Dec
  const int common_year_month_offset[]
      = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
  const int leap_year_mont_offset[] = { 0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 };
  const int A = d.year ();
  const int D = d.day ();
  int d1 = (1 + 5 * ((A - 1) % 4) + 4 * ((A - 1) % 100) + 6 * ((A - 1) % 400))
           % 7;
  bool is_leap = leapyear (A);
  int m;
  if (is_leap)
    {
      m = leap_year_mont_offset[int (d.month ()) - 1];
    }
  else
    {
      m = common_year_month_offset[int (d.month ()) - 1];
    }
  return WeekDay (
      (D + m + 5 * ((A - 1) % 4) + 4 * ((A - 1) % 100) + 6 * ((A - 1) % 400))
      % 7);
}
}
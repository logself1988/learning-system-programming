#include "Chrono.h"

int
main (int argc, char const *argv[])
{
  using namespace Chrono;
  Date d{ 2022, Month::jan, 13 };
  // Date d{ 1777, Month::apr, 30 };
  // Date d{ 1855, Month::feb, 23 };
  cout << d << '\n';
  cout << int (day_of_week (d)) << '\n\n';

  Date dd{ 2022, Month::jan, 30 };
  cout << dd << '\n';
  dd.add_day (2);
  cout << dd << '\n';
  dd.add_month (13);
  cout << dd << '\n';

  Date d2;
  cin >> d2;
  cout << d2 << '\n';
  return 0;
}

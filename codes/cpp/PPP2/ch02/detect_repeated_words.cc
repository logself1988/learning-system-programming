#include "std_lib_facilities.h"

int
main (int argc, char const *argv[])
{
  string previous = " ";
  string current;
  while (cin >> current)
    {
      if (previous == current)
        cout << "repeated word: " << current << '\n';
      previous = current;
    }
  return 0;
}

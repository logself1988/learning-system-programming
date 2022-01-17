#include "std_lib_facilities.h"

void
skip_to_int ()
{
  if (cin.fail ())
    {
      cin.clear ();
      for (char ch; cin >> ch;)
        {
          if (isdigit (ch) || ch == '-')
            {
              cin.unget ();
              return;
            }
        }
    }

  error ("no input");
}

int
get_int ()
{
  int n = 0;
  while (true)
    {
      if (cin >> n)
        return n;
      cout << "Sorry, that was not a number; please try again\n";
      skip_to_int ();
    }
}

int
get_int (int low, int high, const string &greeting, const string &sorry)
{
  cout << greeting << ": [" << low << ":" << high << "]\n";
  while (true)
    {
      int n = get_int ();
      if (low <= n && n <= high)
        return n;

      cout << sorry << ": [" << low << ":" << high << "]\n";
    }
}

int
main (int argc, char const *argv[])
{
  int n = 0;

  try
    {
      n = get_int (1, 10, "enter strength", "Not in range, try again");
      cout << "n=" << n << '\n';
    }
  catch (exception &e)
    {
      cerr << e.what () << '\n';
      return 1;
    }
  catch (...)
    {
      cerr << "exception \n";
      return 2;
    }

  return 0;
}

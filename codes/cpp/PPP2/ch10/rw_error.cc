#include "std_lib_facilities.h"

void
fill_vector (istream &ist, vector<int> &v, char terminator)
{
  for (int i; ist >> i;)
    v.push_back (i);

  if (ist.eof ())
    return;

  ist.clear ();
  char c;
  ist >> c;
  if (c != terminator)
    {
      ist.unget (); // put back
      ist.clear (ios_base::failbit);
    }
}

int
main (int argc, char const *argv[])
{
  // throw exception when bad
  cin.exceptions (cin.exceptions () | ios_base::badbit);
  cout << cin.exceptions () << '\n';

  vector<int> v;
  try
    {
      fill_vector (cin, v, '*');
      for (int i = 0; i < v.size (); i++)
        cout << v[i] << '\n';
    }
  catch (exception &e)
    {
      cerr << e.what () << '\n';
      keep_window_open ();
      return 1;
    }
  catch (...)
    {
      cerr << "exception \n";
      keep_window_open ();
      return 2;
    }

  return 0;
}

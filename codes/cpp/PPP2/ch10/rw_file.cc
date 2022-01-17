#include "std_lib_facilities.h"

//! a temperature reading
struct Reading
{
  int hour;
  double temperature;
};

int
main (int argc, char const *argv[])
{
  try
    {
    }
  catch (exception &e)
    {
      cout << "Please enter input file name: ";
      string iname;
      cin >> iname;
      ifstream ist{ iname };
      if (!ist)
        error ("can't open input file ", iname);

      string oname;
      cout << "Please enter name of output file:";
      cin >> oname;
      ofstream ost{ oname };
      if (!ost)
        error ("can't open output file ", oname);

      vector<Reading> temps;
      int hour;
      double temperature;
      while (ist >> hour >> temperature)
        {
          if (hour < 0 || hour > 23)
            error ("hour out of range");

          temps.push_back (Reading{ hour, temperature });
        }

      for (int i = 0; i < temps.size (); i++)
        ost << "(" << temps[i].hour << "," << temps[i].temperature << ")\n";
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

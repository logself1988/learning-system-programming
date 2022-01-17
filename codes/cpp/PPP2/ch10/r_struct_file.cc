#include "std_lib_facilities.h"

const int not_a_reading = -7777;
const int not_a_month = -1;

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

vector<string> month_input_tbl = { "jan", "feb", "mar", "apr", "may", "jun",
                                   "jul", "aug", "sep", "oct", "nov", "dec" };

int
month_to_int (string s)
{
  for (int i = 0; i < month_input_tbl.size (); i++)
    if (month_input_tbl[i] == s)
      return i;

  return not_a_month;
}

void
end_of_loop (istream &ist, char teminator, const string &msg)
{
  if (ist.fail ())
    {
      ist.clear ();
      char ch;
      if (ist >> ch && ch == teminator)
        return;
      error (msg);
    }
}

struct Reading
{
  int day;
  int hour;
  double temperature;
};

bool
is_valid (const Reading &r)
{
  if (r.day < 1 || 31 < r.day)
    return false;
  if (r.hour < 0 || 23 < r.hour)
    return false;
  if (r.temperature < implausible_min || implausible_max < r.temperature)
    return false;

  return true;
}

istream &
operator>> (istream &is, Reading &r)
{
  char ch1;
  if (is >> ch1 && ch1 != '(') // a Reading?
    {
      is.unget ();
      is.clear (ios_base::failbit);
      return is;
    }

  char ch2;
  int d, h;
  double t;
  is >> d >> h >> t >> ch2;
  cout << ch1 << "d=" << d << ", h=" << h << ", t=" << t << ch2 << '\n';
  if (!is || ch2 != ')')
    error ("bad reading");

  r.day = d;
  r.hour = h;
  r.temperature = t;
  return is;
}

struct Day
{
  vector<double> hour{ vector<double> (24, not_a_reading) };
};

void
print_day (ostream &os, const Day &d, int day)
{
  for (int i = 0; i < d.hour.size (); i++)
    {
      if (d.hour[i] != not_a_reading)
        os << " (" << day << ' ' << i + 1 << ' ' << d.hour[i] << ')';
    }
}

struct Month
{
  int month{ not_a_month }; //!< [0:11]
  vector<Day> day{ 32 };    //!< [1:31]
};

istream &
operator>> (istream &is, Month &m)
{
  char ch = 0;
  if (is >> ch && ch != '{')
    {
      is.unget ();
      is.clear (ios_base::failbit);
      return is;
    }

  string month_marker;
  string mm;
  is >> month_marker >> mm;
  if (!is || month_marker != "month")
    error ("bad start of month");

  m.month = month_to_int (mm);
  int duplicates = 0;
  int invalids = 0;

  for (Reading r; is >> r;)
    {
      if (is_valid (r))
        {
          if (m.day[r.day].hour[r.hour] != not_a_reading)
            ++duplicates;
          m.day[r.day].hour[r.hour] = r.temperature;
        }
      else
        ++invalids;
    }

  if (invalids)
    error ("invalid readings in month ", invalids);
  if (duplicates)
    error ("duplicate readings in month ", duplicates);
  end_of_loop (is, '}', "bad end of month");
  return is;
}

void
print_month (ostream &os, const Month &m)
{
  if (m.month == not_a_month)
    return;

  os << " { month " << month_input_tbl[m.month];
  for (int i = 0; i < m.day.size (); i++)
    {
      print_day (os, m.day[i], i);
    }
  os << "}";
}

struct Year
{
  int year;
  vector<Month> month{ 12 }; //!< [0:11]
};

istream &
operator>> (istream &is, Year &y)
{
  char ch;
  is >> ch;
  if (ch != '{')
    {
      is.unget ();
      is.clear (ios_base::failbit);
      return is;
    }

  string year_marker;
  int yy;
  is >> year_marker >> yy;
  if (!is || year_marker != "year")
    error ("bad start of year");
  y.year = yy;

  while (true)
    {
      Month m;
      if (!(is >> m))
        break;
      y.month[m.month] = m;
    }

  end_of_loop (is, '}', "bad end of year");
  return is;
}

void
print_year (ostream &os, const Year &y)
{
  os << "{year " << y.year;
  for (const Month &m : y.month)
    print_month (os, m);
  os << "}\n";
}

int
main (int argc, char const *argv[])
{
  cout << "Please enter input file name\n";
  string iname;
  cin >> iname;
  ifstream ist{ iname };
  if (!ist)
    error ("can't open input file ", iname);

  ist.exceptions (ist.exceptions () | ios_base::badbit);

  cout << "Please enter output file name\n";
  string oname;
  cin >> oname;
  ofstream ost{ oname };
  if (!ost)
    error ("can't open output file ", oname);

  vector<Year> ys;
  while (true)
    {
      Year y;
      if (!(ist >> y))
        break;
      ys.push_back (y);
    }
  cout << "read " << ys.size () << " years of readings\n";

  for (const Year &y : ys)
    print_year (ost, y);

  return 0;
}

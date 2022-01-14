#ifndef CH09_CHRONO
#define CH09_CHRONO

#include "std_lib_facilities.h"

namespace Chrono
{
enum class Month
{
  jan = 1,
  feb,
  mar,
  apr,
  may,
  jun,
  jul,
  aug,
  sep,
  oct,
  nov,
  dec
};

//! ISO 8601
enum class WeekDay
{
  sunday,    //<! 0
  monday,    //<! 1
  tuesday,   //<! 2
  wednesday, //<! 3
  thursday,  //<! 4
  friday,    //<! 5
  satuarday  //<! 6
};

class Date
{
public:
  //! to throw as exception
  class Invalid
  {
  };

  Date (int y, Month m, int d);
  Date ();

  /// nonmodifying operations

  int
  day () const
  {
    return d;
  }
  Month
  month () const
  {
    return m;
  }
  int
  year () const
  {
    return y;
  }

  /// modifying operations

  void add_day (int n);
  void add_month (int n);
  void add_year (int n);

private:
  int y;   //!< year
  Month m; //!< month
  int d;   //!< day
};

/// helper functions

bool is_date (int y, Month m, int day);
bool leapyear (int y);
WeekDay day_of_week (const Date &d);
bool operator== (const Date &a, const Date &b);
bool operator!= (const Date &a, const Date &b);

ostream &operator<< (ostream &os, const Date &d);
istream &operator>> (istream &is, Date &d);
}

#endif /* CH09_CHRONO */

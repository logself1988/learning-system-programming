#include "Graph.h"
#include "Simple_window.h" // "Next" button
#include "funcs.h"
#include "std_lib_facilities.h"

struct Distribution
{
  int year, young, middle, old;
};

//! assume format: (year: yound middle old)
istream &
operator>> (istream &is, Distribution &d)
{
  char ch1 = 0;
  char ch2 = 0;
  char ch3 = 0;
  Distribution dd;

  if (is >> ch1 >> dd.year >> ch2 >> dd.young >> dd.middle >> dd.old >> ch3)
    {
      if (ch1 != '(' || ch2 != ':' || ch3 != ')')
        {
          is.clear (ios_base::failbit);
          return is;
        }
    }
  else
    return is;

  d = dd;
  return is;
}

class Scale
{
public:
  Scale (int b, int vb, double s) : cbase{ b }, vbase{ vb }, scale{ s } {}

  int
  operator() (int v) const
  {
    return cbase + (v - vbase) * scale;
  }

private:
  int cbase; //!< coordinate base
  int vbase; //!< base of values
  double scale;
};

using namespace Graph_lib;

int
main (int argc, char const *argv[])
{
  try
    {
      constexpr int base_year = 1960;
      constexpr int end_year = 2040;

      // 1. reading a file
      string file_name = "japanese-age-data.txt";
      ifstream ifs{ file_name };
      if (!ifs)
        error ("can't open ", file_name);

      // 2. scaling data to fit the window
      constexpr int xmax = 800;
      constexpr int ymax = 600;
      constexpr int xoffset = 100;
      constexpr int yoffset = 60;
      constexpr int xspace = 40;
      constexpr int yspace = 40;
      constexpr int xlength = xmax - xoffset - xspace;
      constexpr int ylength = ymax - yoffset - yspace;

      constexpr double xscale = double (xlength) / (end_year - base_year);
      constexpr double yscale = double (ylength) / 100;

      Scale xs{ xoffset, base_year, xscale };
      Scale ys{ ymax - yoffset, 0, -yscale };

      // 3.displaying the data
      Point tl{ 100, 100 };
      Simple_window win{ tl, xmax, ymax, "Aging" };
      win.set_bg_color (Color::white);

      Point graph_orig{ xoffset, ymax - yoffset };
      vector<string> notch_labels;
      for (int i = base_year; i <= end_year; i += 10)
        {
          notch_labels.push_back (std::to_string (i));
        }
      Axis x{ Axis::x, graph_orig, xlength, (end_year - base_year) / 10 + 1,
              "year" };
      x.set_notch_labels (notch_labels);
      x.label.move (-200, 0);

      Axis y{ Axis::y, Point{ xoffset, ymax - yoffset }, ylength, 10,
              "% of population" };
      win.attach (x);
      win.attach (y);

      Line current_year{ Point{ xs (2008), ys (0) },
                         Point{ xs (2008), ys (100) } };
      current_year.set_style (Line_style::dash);
      win.attach (current_year);

      Open_polyline children;
      Open_polyline adults;
      Open_polyline aged;
      for (Distribution d; ifs >> d;)
        {
          if (d.year < base_year || end_year < d.year)
            error ("year out of range");
          if (d.young + d.middle + d.old != 100)
            error ("percentages don't add up");
          const int x = xs (d.year);
          children.add (Point{ x, ys (d.young) });
          adults.add (Point{ x, ys (d.middle) });
          aged.add (Point{ x, ys (d.old) });
        }

      win.attach (children);
      win.attach (adults);
      win.attach (aged);

      // 4. labeling the graph
      Text children_label{ Point{ 20, children.point (0).y }, "age 0-14" };
      children.set_color (Color::red);
      children_label.set_color (Color::red);
      Text adults_lablel{ Point{ 20, adults.point (0).y }, "age 15-64" };
      adults.set_color (Color::blue);
      adults_lablel.set_color (Color::blue);
      Text aged_label{ Point{ 20, aged.point (0).y }, "age 65+" };
      aged.set_color (Color::dark_green);
      aged_label.set_color (Color::dark_green);

      win.attach (children_label);
      win.attach (adults_lablel);
      win.attach (aged_label);

      constexpr int x_orig = xmax / 2;
      constexpr int y_orig = ymax / 2;
      Point orig{ x_orig, y_orig }; // (0,0)

      constexpr int r_min = -10; // range: [-10, 11)
      constexpr int r_max = 11;
      constexpr int n_points = 200; // number of points in range

      constexpr int x_scale = 30; // scaling factors
      constexpr int y_scale = 30;

      win.wait_for_button (); // display
    }
  catch (const std::exception &e)
    {
      cerr << e.what () << '\n';
      return 1;
    }
  catch (...)
    {
      cerr << "exception\n";
      return 1;
    }

  return 0;
}

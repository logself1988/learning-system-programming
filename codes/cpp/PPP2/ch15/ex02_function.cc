#include "Graph.h"
#include "Simple_window.h" // "Next" button
#include "funcs.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int
main (int argc, char const *argv[])
{
  try
    {
      constexpr int xmax = 800;
      constexpr int ymax = 600;
      constexpr int x_orig = xmax / 2;
      constexpr int y_orig = ymax / 2;
      Point orig{ x_orig, y_orig }; // (0,0)

      constexpr int r_min = -10; // range: [-10, 11)
      constexpr int r_max = 11;
      constexpr int n_points = 400; // number of points in range

      constexpr int x_scale = 30; // scaling factors
      constexpr int y_scale = 30;

      // window
      Point tl{ 100, 100 };
      Simple_window win{ tl, xmax, ymax, "Function graphing" };
      win.set_bg_color (Color::white);

      // functon
      Function s{ one, r_min, r_max, orig, n_points, x_scale, y_scale };
      Function s2{ slope, r_min, r_max, orig, n_points, x_scale, y_scale };
      Function s3{ square, r_min, r_max, orig, n_points, x_scale, y_scale };
      Function s4{ cos, r_min, r_max, orig, n_points, x_scale, y_scale };
      s4.set_color (Color::blue);
      Function s5{
        sloping_cos, r_min, r_max, orig, n_points, x_scale, y_scale
      };

      win.attach (s);
      win.attach (s2);
      win.attach (s3);
      win.attach (s4);
      win.attach (s5);

      // more functions
      Function f1{ log, 0.000001, r_max, orig, n_points, x_scale, y_scale };
      Function f2{ sin, r_min, r_max, orig, n_points, x_scale, y_scale };
      f2.set_color (Color::blue);
      Function f3{ cos, r_min, r_max, orig, n_points, x_scale, y_scale };
      Function f4{ exp, r_min, r_max, orig, n_points, x_scale, y_scale };
      f4.set_color (Color::green);
      win.attach (f1);
      win.attach (f2);
      win.attach (f3);
      win.attach (f4);

      // lambda expression
      Function f5{ [] (double x) -> double { return cos (x) + slope (x) + 1; },
                   r_min,
                   r_max,
                   orig,
                   n_points,
                   x_scale,
                   y_scale };
      f5.set_color (Color::red);
      win.attach (f5);

      // text
      Text ts{ Point{ 100, y_orig - 40 }, "one" };
      Text ts2{ Point{ 100, y_orig + y_orig / 2 - 20 }, "x/2" };
      Text ts3{ Point{ x_orig - 100, 20 }, "x*x" };
      win.attach (ts);
      win.attach (ts2);
      win.attach (ts3);

      // axis
      constexpr int xlength = xmax - 40;
      constexpr int ylength = ymax - 40;
      Axis x{ Axis::x, Point{ 20, y_orig }, xlength, xlength / x_scale,
              "one notch == 1" };
      Axis y{ Axis::y, Point{ x_orig, ylength + 20 }, ylength,
              ylength / y_scale, "one notch == 1" };
      x.set_color (Color::red);
      x.label.move (-160, 0);
      x.notches.set_color (Color::dark_red);
      y.set_color (Color::red);
      win.attach (x);
      win.attach (y);

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

#include "Graph.h"
#include "Simple_window.h" // "Next" button
#include "std_lib_facilities.h"

using namespace Graph_lib;

int
main (int argc, char const *argv[])
{
  try
    {
      // window
      Point tl{ 100, 100 };
      Simple_window win{ tl, 800, 600, "Canvas" };
      win.set_bg_color (Color::white);

      int x_size = win.x_max ();
      int y_size = win.y_max ();
      int x_grid = 40;
      int y_grid = 30;

      Lines grid;
      for (int x = x_grid; x < x_size; x += x_grid)
        grid.add (Point{ x, 0 }, Point{ x, y_size }); // vertical line
      for (int y = y_grid; y < y_size; y += y_grid)
        grid.add (Point{ 0, y }, Point{ x_size, y }); // horizontal line

      // color
      grid.set_color (Color::red);

      // line style
      grid.set_style (Line_style::dot);

      win.attach (grid);

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
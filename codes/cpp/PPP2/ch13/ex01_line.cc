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
      Simple_window win{ tl, 800, 600, "two lines" };
      win.set_bg_color (Color::white);

      // draw two lines
      Point x{ 100, 100 };
      Line horizontal{ x, Point{ 200, 100 } };
      Line vertical{ Point{ 150, 50 }, Point{ 150, 150 } };
      win.attach (horizontal);
      win.attach (vertical);

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

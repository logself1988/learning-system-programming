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

      // ellipse
      Ellipse e1{ Point{ 200, 200 }, 50, 50 };
      Ellipse e2{ Point{ 200, 200 }, 100, 50 };
      Ellipse e3{ Point{ 200, 200 }, 100, 150 };
      win.attach (e1);
      win.attach (e2);
      win.attach (e3);

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

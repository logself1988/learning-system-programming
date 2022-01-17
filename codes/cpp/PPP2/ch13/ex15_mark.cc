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

      // circle
      Circle c1{ Point{ 100, 200 }, 50 };
      Circle c2{ Point{ 150, 200 }, 100 };
      Circle c3{ Point{ 200, 200 }, 150 };

      // mark
      Mark m1{ Point{ 100, 200 }, 'x' };
      Mark m2{ Point{ 150, 200 }, 'y' };
      Mark m3{ Point{ 200, 200 }, 'z' };

      c1.set_color (Color::blue);
      c2.set_color (Color::red);
      c3.set_color (Color::green);

      win.attach (c1);
      win.attach (c2);
      win.attach (c3);

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

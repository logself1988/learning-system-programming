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

      // marked polyline
      Marked_polyline mpl{ "1234" };
      mpl.add (Point{ 100, 100 });
      mpl.add (Point{ 150, 200 });
      mpl.add (Point{ 250, 250 });
      mpl.add (Point{ 300, 200 });
      win.attach (mpl);

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

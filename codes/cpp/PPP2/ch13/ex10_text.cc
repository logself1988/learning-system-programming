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

      // closed polyline
      Closed_polyline cpl
          = { { 100, 100 }, { 150, 200 }, { 250, 250 }, { 300, 200 } };
      win.attach (cpl);

      // text
      Text t{ Point{ 200, 200 }, "A closed polyline that isn't a polygon" };
      t.set_color (Color::blue);
      win.attach (t);

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

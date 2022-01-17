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

      // image
      Image rita{ Point{ 0, 0 }, "rita.jpg" };
      Image path{ Point{ 0, 0 }, "rita_path.gif" };
      path.set_mask (Point{ 50, 250 }, 600, 400);

      win.attach (rita);
      win.attach (path);
      win.put_on_top (rita);

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

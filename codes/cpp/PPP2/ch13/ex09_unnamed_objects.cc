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

      // unnamed objects
      Vector_ref<Rectangle> vr;

      for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
          {
            vr.push_back (
                new Rectangle{ Point{ i * 20, j * 20 }, 20, 20 }); // unamed
            vr[vr.size () - 1].set_fill_color (Color{ i * 16 + j });
            win.attach (vr[vr.size () - 1]);
          }

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
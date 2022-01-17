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
      // win.set_bg_color (Color::white);

      // rectangle
      Rectangle rect00{ Point{ 150, 100 }, 200, 100 };
      Rectangle rect11{ Point{ 50, 50 }, Point{ 250, 150 } };
      Rectangle rect12{ Point{ 50, 150 }, Point{ 250, 250 } };
      Rectangle rect21{ Point{ 250, 50 }, 200, 100 };
      Rectangle rect22{ Point{ 250, 150 }, 200, 100 };

      // fill colr
      rect00.set_fill_color (Color::yellow);
      rect11.set_fill_color (Color::blue);
      rect12.set_fill_color (Color::red);
      rect21.set_fill_color (Color::green);

      // move
      rect11.move (400, 0);
      rect11.set_fill_color (Color::white);

      // line color
      rect00.set_color (Color::invisible);
      rect11.set_color (Color::invisible);
      rect12.set_color (Color::invisible);
      rect21.set_color (Color::invisible);
      rect22.set_color (Color::invisible);

      win.attach (rect00);
      win.attach (rect11);
      win.attach (rect12);
      win.attach (rect21);
      win.attach (rect22);

      // reorder shapes
      win.put_on_top (rect00);

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
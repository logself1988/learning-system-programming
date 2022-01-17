#include "std_lib_facilities.h"
// #include "Window.h"
#include "Graph.h"
#include "Simple_window.h" // "Next" button

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

      // axis
      Axis xa{ Axis::x, Point{ 20, 300 }, 280, 10, "x" };
      win.attach (xa);
      Axis ya{ Axis::y, Point{ 20, 300 }, 280, 10, "y" };
      ya.set_color (Color::blue);
      ya.label.set_color (Color::blue);
      win.attach (ya);

      // function
      Function sine{ sin, 0, 100, Point{ 20, 150 }, 1000, 50, 50 };
      win.attach (sine);
      sine.set_color (Color::green);

      // polygon
      Polygon poly;
      poly.add (Point{ 300, 200 });
      poly.add (Point{ 350, 100 });
      poly.add (Point{ 400, 200 });
      poly.set_color (Color::red);
      poly.set_style (Line_style{ Line_style::dash, 4 });
      win.attach (poly);

      // rectangle
      Rectangle r{ Point{ 200, 200 }, 100, 50 };
      r.set_fill_color (Color::yellow);
      win.attach (r);

      // closed polyline
      Closed_polyline poly_rect;
      poly_rect.add (Point{ 100, 50 });
      poly_rect.add (Point{ 200, 50 });
      poly_rect.add (Point{ 200, 100 });
      poly_rect.add (Point{ 100, 100 });
      poly_rect.add (Point{ 50, 75 });
      poly_rect.set_style (Line_style{ Line_style::dash, 2 });
      poly_rect.set_fill_color (Color::green);
      win.attach (poly_rect);

      // text
      Text t{ Point{ 150, 150 }, "Hello, graphical world!" };
      t.set_font (Font::times_bold);
      t.set_font_size (20);
      win.attach (t);

      // image
      Image img{ Point{ 100, 50 }, "image.jpg", Suffix::jpg }; // 400x200
      img.move (100, 300);
      win.attach (img);

      // more
      Circle c{ Point{ 100, 200 }, 50 };
      win.attach (c);
      Ellipse e{ Point{ 100, 200 }, 75, 25 };
      e.set_color (Color::dark_red);
      win.attach (e);
      Mark m{ Point{ 100, 200 }, 'x' };
      win.attach (m);

      ostringstream oss;
      oss << "screent size" << x_max () << "*" << y_max ()
          << "; window size: " << win.x_max () << "*" << win.y_max ();
      Text sizes{ Point{ 100, 20 }, oss.str () };
      win.attach (sizes);

      Image cal{ Point{ 225, 225 }, "snow_cpp.gif" }; // 320x240
      cal.set_mask (Point{ 40, 40 }, 200, 150);
      win.attach (cal);

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

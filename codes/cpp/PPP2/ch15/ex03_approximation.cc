#include "Graph.h"
#include "Simple_window.h" // "Next" button
#include "funcs.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main(int argc, char const *argv[]) {
  try {
    constexpr int xmax = 800;
    constexpr int ymax = 600;
    constexpr int x_orig = xmax / 2;
    constexpr int y_orig = ymax / 2;
    Point orig{x_orig, y_orig}; // (0,0)

    constexpr int r_min = -10; // range: [-10, 11)
    constexpr int r_max = 11;
    constexpr int n_points = 200; // number of points in range

    constexpr int x_scale = 30; // scaling factors
    constexpr int y_scale = 30;

    // window
    Point tl{100, 100};
    Simple_window win{tl, xmax, ymax, "Function graphing"};
    win.set_bg_color(Color::white);

    // function
    Function real_exp{exp, r_min, r_max, orig, n_points, x_scale, y_scale};
    real_exp.set_color(Color::blue);
    win.attach(real_exp);

    for (int n = 0; n < 50; n++) {
      ostringstream ss;
      ss << "exp approximation; n==" << n;
      win.set_label(ss.str());
      // get next approximation
      // we cannot convert lambda expression to function pointer when it
      // captures
      auto f = [n](double x) -> double { return expe(x, n); };
      Function e{f, r_min, r_max, orig, n_points, x_scale, y_scale};
      e.set_color(Color::red);
      win.attach(e);
      win.wait_for_button();
      win.detach(e);
    }

    win.wait_for_button(); // display
  } catch (const std::exception &e) {
    cerr << e.what() << '\n';
    return 1;
  } catch (...) {
    cerr << "exception\n";
    return 1;
  }

  return 0;
}

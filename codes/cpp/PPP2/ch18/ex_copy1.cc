#include "std_lib_facilities.h"

class _vector {
  int sz;
  double *elem;

public:
  _vector(int s) : sz{s}, elem{new double[s]} {
    for (int i = 0; i < sz; i++)
      elem[i] = 0.0;
  }
  ~_vector() { delete[] elem; }
  int size() const { return sz; }
  double get(int n) const { return elem[n]; }
  void set(int n, double v) { elem[n] = v; }
};

int main(int argc, char const *argv[]) {
  _vector v(3);
  v.set(2, 2.2);

  // default copying for a class: copy all the data members
  _vector v2 = v;

  v.set(1, 99);
  v2.set(0, 88);
  cout << v.get(0) << ' ' << v2.get(1); // 88 99

  return 0;
}

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

  _vector(const _vector &);            //!< copy constructor
  _vector &operator=(const _vector &); //!< copy assignment

  int size() const { return sz; }
  double get(int n) const { return elem[n]; }
  void set(int n, double v) { elem[n] = v; }
};

_vector::_vector(const _vector &arg) : sz{arg.sz}, elem{new double[arg.sz]} {
  copy(arg.elem, arg.elem + sz, elem); // use std::copy()
  // for (int i = 0; i < sz; i++) {
  // elem[i] = arg.get(i);
  // }
}

_vector &_vector::operator=(const _vector &arg) {
  double *p = new double[arg.sz];          // allocate new space
  copy(arg.elem, arg.elem + arg.sz, elem); // copy elements using std::copy()

  delete[] elem; // deallocate old space

  elem = p; // reset elem
  sz = arg.sz;
  return *this; // return a self reference
}

void print_vector(const _vector &v) {
  cout << "{ ";
  for (int i = 0; i < v.size(); i++) {
    cout << v.get(i) << ' ';
  }
  cout << "}\n";
}

int main(int argc, char const *argv[]) {
  _vector v(3);
  v.set(2, 2.2);

  _vector v2 = v; // call copy constructor

  v.set(1, 99);
  v2.set(0, 88);
  cout << v.get(0) << ' ' << v2.get(1) << '\n'; // 0 0

  _vector v3(4);
  v3 = v; // call copy assignment
  print_vector(v);
  print_vector(v3);

  return 0;
}

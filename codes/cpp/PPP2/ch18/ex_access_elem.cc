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

  _vector(_vector &&a);           //!< move constructor
  _vector &operator=(_vector &&); //!< move assignment

  double &operator[](int n) { //!< operator[], return reference
    return elem[n];
  }

  double operator[](int n) const { //!< for const vectors
    return elem[n];
  }

  int size() const { return sz; }
  double get(int n) const { return elem[n]; }
  void set(int n, double v) { elem[n] = v; }
};

_vector::_vector(const _vector &arg) : sz{arg.sz}, elem{new double[arg.sz]} {
  cout << "_vector::_vector(const _vector &) called\n";

  copy(arg.elem, arg.elem + sz, elem); // use std::copy()
  // for (int i = 0; i < sz; i++) {
  // elem[i] = arg.get(i);
  // }
}

_vector &_vector::operator=(const _vector &arg) {
  cout << "_vector::operator=(const _vector &) called\n";

  double *p = new double[arg.sz];       // allocate new space
  copy(arg.elem, arg.elem + arg.sz, p); // copy elements using std::copy()

  delete[] elem; // deallocate old space

  elem = p; // reset elem
  sz = arg.sz;
  return *this; // return a self reference
}

_vector::_vector(_vector &&a) : sz{a.sz}, elem{a.elem} {
  cout << "_vector::_vector(_vector &&) called\n";
  a.sz = 0;
  a.elem = nullptr;
}

_vector &_vector::operator=(_vector &&a) {
  cout << "_vector::operator=(_vector &&) called\n";

  delete[] elem;
  elem = a.elem;
  sz = a.sz;
  a.elem = nullptr;
  a.sz = 0;
  return *this;
}

_vector fill(istream &is, int n) {
  _vector res(n);
  double x;
  for (int i = 0; i < n; i++) {
    is >> x;
    res.set(i, x);
  }
  return res;
}

void print_vector(const _vector &v) {
  cout << "{ ";
  for (int i = 0; i < v.size(); i++) {
    cout << v.get(i) << ' ';
  }
  cout << "}\n";
}

void ff(const _vector &cv, _vector &v) {
  double d = cv[1]; //!< use const []
  // cv[1] = 2.0; //!< error: expression is not assignable
  double dd = v[1]; //!< use non-const []
  v[1] = 2.0;       //!< use non-const []
}

int main(int argc, char const *argv[]) {
  const _vector cv = move(fill(cin, 3)); // force use move
  print_vector(cv);

  _vector v = fill(cin, 3);
  print_vector(v);

  ff(cv, v);
  print_vector(cv);
  print_vector(v);

  return 0;
}

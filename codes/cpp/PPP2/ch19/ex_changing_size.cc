#include "std_lib_facilities.h"

//! an almost real vector of doubles

class _vector {

  //! invariant:
  //! if 0<=n<sz, elem[n] is element n
  //! sz<=space
  //! if sz<space there is space for (space-sz) doubles after elem[sz-1]

  int sz;       //!< the size
  double *elem; //!< pointer to the elements of 0
  int space;    //!< number of elements plus number of free slots

public:
  _vector() : sz{0}, elem{nullptr}, space{0} {}
  explicit _vector(int s) : sz{s}, elem{new double[s]}, space{s} {
    for (int i = 0; i < sz; i++)
      elem[i] = 0;
  }

  _vector(const _vector &);            //!< copy constructor
  _vector &operator=(const _vector &); //!< copy assignment

  _vector(_vector &&);            //!< move constructor
  _vector &operator=(_vector &&); //!< move assignment

  ~_vector() { delete[] elem; } //!< destructor

  //!< access: return reference
  double &operator[](int n) { return elem[n]; }
  const double &operator[](int n) const { return elem[n]; }

  int size() const { return sz; }
  int capacity() const { return space; }

  //! growth

  void resize(int newsize);
  void push_back(double d);
  void reserve(int newalloc);
};

void _vector::reserve(int newalloc) {
  if (newalloc <= space)
    return;

  double *p = new double[newalloc]; // allocate new space
  for (int i = 0; i < sz; i++)      // copy old elements
    p[i] = elem[i];
  delete[] elem;
  elem = p;
  space = newalloc;
}

void _vector::resize(int newsize) {
  reserve(newsize);
  for (int i = sz; i < newsize; i++) // initialize new elements
    elem[i] = 0;
  sz = newsize;
}

void _vector::push_back(double d) {
  if (space == 0)
    reserve(8);
  else if (sz == space)
    reserve(2 * space);

  elem[sz] = d;
  ++sz;
}

_vector::_vector(const _vector &a)
    : sz{a.sz}, elem{new double[a.sz]}, space{a.space} {
  cout << "_vector::_vector(const _vector &) called\n";

  copy(a.elem, a.elem + sz, elem); // use std::copy()
}

_vector &_vector::operator=(const _vector &a) {
  cout << "_vector::operator=(const _vector &) called\n";

  if (this == &a)
    return *this; // self-assignment

  // enough space
  if (a.sz <= space) {
    for (int i = 0; i < a.sz; i++)
      elem[i] = a.elem[i];
    sz = a.sz;
    return *this;
  }

  // allocate new space
  double *p = new double[a.sz];
  for (int i = 0; i < a.sz; i++)
    p[i] = a.elem[i];
  delete[] elem;
  space = sz = a.sz;
  elem = p;
  return *this;
}

_vector::_vector(_vector &&a) : sz{a.sz}, elem{a.elem}, space{a.space} {
  cout << "_vector::_vector(_vector &&) called\n";

  a.sz = 0;
  a.space = 0;
  a.elem = nullptr;
}

_vector &_vector::operator=(_vector &&a) {
  cout << "_vector::operator=(_vector &&) called\n";

  delete[] elem;
  elem = a.elem;
  sz = a.sz;
  space = a.space;

  a.elem = nullptr;
  a.sz = 0;
  a.space = 0;

  return *this;
}

int main(int argc, char const *argv[]) {
  _vector v(2);
  v.reserve(10);
  v.push_back(7);

  _vector v2{2};
  v = v2;

  return 0;
}

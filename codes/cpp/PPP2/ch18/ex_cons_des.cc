#include "std_lib_facilities.h"

//! simple test class
struct X {
  int val;

  void out(const string &s, int nv) {
    cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
  }

  X() { //!< default constructor
    out("X()", 0);
    val = 0;
  }

  X(int v) {
    val = v;
    out("X(int)", v);
  }

  X(const X &x) { //!< copy constructor
    val = x.val;
    out("X(X&)", x.val);
  }

  X &operator=(const X &a) { //!< copy assignment
    out("X::operator=()", a.val);
    val = a.val;
    return *this;
  }

  ~X() { //!< destructor
    out("~X()", 0);
  }
};

X glob(2); //! a global variable

X copy(X a) { return a; }

X copy2(X a) {
  X aa = a;
  return aa;
}

X &ref_to(X &a) { return a; }

X *make(int i) {
  X a(i);
  return new X(a);
}

struct XX {
  X a;
  X b;
};

int main(int argc, char const *argv[]) {

  X loc{4}; //!< local variable
  cerr << "loc\n";

  X loc2{loc}; //!< copy construction
  cerr << "loc2\n";

  loc = X{5}; //!< copy assignment
  cerr << "loc\n";

  loc2 = copy(loc); //!< call by value and return
  cerr << "copy\n";
  loc2 = copy2(loc);
  cerr << "copy2\n";

  X loc3{6};
  cerr << "loc3\n";

  X &r = ref_to(loc); //!< call by reference and return
  cerr << "r\n";

  delete make(7);
  cerr << "make(7)\n";
  delete make(8);
  cerr << "make(8)\n";

  vector<X> v(4); //!< default values
  cerr << "v\n";

  XX loc4;
  cerr << "loc4\n";

  X *p = new X{9}; //!< an X on the free store
  delete p;
  cerr << "p\n";

  X *pp = new X[5]; //!< an array of Xs on the free store
  delete[] pp;
  cerr << "pp\n";

  return 0;
}

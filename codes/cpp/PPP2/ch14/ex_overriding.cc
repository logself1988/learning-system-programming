#include "std_lib_facilities.h"

struct B {
  virtual void f() const { cout << "B::f "; }

  //!< not virtual
  void g() const { cout << "B::g "; }
};

struct D : B {
  //!< overrides B::f
  void f() const override { cout << "D::f "; }

  void g() { cout << "D::g "; }
};

struct DD : D {
  //!< not override D::f: not const
  void f() { cout << "DD::f "; }

  void g() const { cout << "DD::g "; }
};

void call(const B &b) {
  b.f();
  b.g();
}

int main(int argc, char const *argv[]) {
  B b;
  D d;
  DD dd;

  call(b);
  call(d);
  call(dd);

  cout << '\n';

  b.f();
  b.g();

  d.f();
  d.g();

  dd.f();
  dd.g();

  return 0;
}

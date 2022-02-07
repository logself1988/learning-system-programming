#include "std_lib_facilities.h"

class Link {
public:
  string value;

  Link(const string &v, Link *p = nullptr, Link *s = nullptr)
      : value{v}, prev{p}, succ{s} {}

  Link *insert(Link *n); //!< insert n before this object, return n
  Link *add(Link *n);    //!< insert n after this object, return n
  Link *erase();         //!< remove this object from list, return p's succ
  Link *find(const string &s); //!< find s in list
  const Link *
  advance(int n) const; //!< move n position in list, return nullptr for not
                        //!< found, positive n moves forwrad, negative backword
  Link *next() const { return succ; }
  Link *previous() const { return prev; }

private:
  Link *prev;
  Link *succ;
};

//!< insert n before this object, return n
Link *Link::insert(Link *n) {
  if (n == nullptr) // nothing to insert
    return this;
  if (this == nullptr) // nothing to insert into
    return n;

  n->succ = this; // this comes after n
  if (prev)
    prev->succ = n;

  n->prev = prev; // this's prev becomes n's prev
  prev = n;       // n becomes this's prev
  return n;
}

//!< insert n after this object, return n
Link *Link::add(Link *n) {
  if (n == nullptr) // nothing to add
    return this;
  if (this == nullptr) // nothing to add into
    return n;
  n->prev = this; // n comes after this
  if (succ)
    succ->prev = n;
  n->succ = succ;
  succ = n;
  return n;
}

//!< remove this object from list, return p's succ
Link *Link::erase() {
  if (this == nullptr)
    return nullptr;
  if (succ)
    succ->prev = prev;
  if (prev)
    prev->succ = succ;
  return succ;
}

Link *Link::find(const string &s) {
  Link *p = this;
  while (p) {
    if (p->value == s)
      return p;
    p = p->next();
  }

  return nullptr;
}

//!< move n position in list, return nullptr for not
//!< found, positive n moves forwrad, negative backword
const Link *Link::advance(int n) const {
  if (this == nullptr)
    return nullptr;

  if (0 < n) {
    if (succ == nullptr)
      return nullptr;
    return succ->advance(--n);
  } else if (n < 0) {
    if (prev == nullptr)
      return nullptr;
    return prev->advance(++n);
  }
  return this;
}

void print_all(Link *p) {
  cout << "{ ";
  while (p) {
    cout << p->value;
    if (p = p->next())
      cout << ", ";
  }
  cout << " }";
}

int main(int argc, char const *argv[]) {
  try {
    Link *norse_gods = new Link{"Thor"};
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freia"});

    Link *greek_gods = new Link("Hera");
    greek_gods = greek_gods->insert(new Link{"Athena"});
    greek_gods = greek_gods->insert(new Link{"Mars"});
    greek_gods = greek_gods->insert(new Link{"Poseidon"});

    Link *p = greek_gods->find("Mars");
    if (p)
      p->value = "Ares";

    Link *p2 = norse_gods->find("Zeus");
    if (p2) {
      if (p2 == norse_gods)
        norse_gods = p2->next();
      p2->erase();
      greek_gods = greek_gods->insert(p2);
    }

    print_all(norse_gods);
    cout << '\n';

    print_all(greek_gods);
    cout << '\n';
  } catch (exception &e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
  } catch (...) {
    cerr << "Unknown exception\n";
    return 2;
  }

  return 0;
}

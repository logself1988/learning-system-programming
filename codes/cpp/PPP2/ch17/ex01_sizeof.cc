#include "std_lib_facilities.h"

void sizes(char ch, int i, int *p) {
  cout << "the size of char is " << sizeof(char) << ' ' << sizeof(ch) << '\n';
  cout << "the size of int is " << sizeof(int) << ' ' << sizeof(i) << '\n';
  cout << "the size of int* is " << sizeof(int *) << ' ' << sizeof(p) << '\n';

  vector<int> v(1000); // sizeof is not counting the elements
  cout << "the size of vector<int>(1000) is " << sizeof(v) << '\n';
}

int main(int argc, char const *argv[]) {
  int i = 1;
  int *p = &i;
  sizes('a', i, p);

  return 0;
}

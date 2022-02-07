#include "std_lib_facilities.h"

bool is_palindrome(const string &s) {
  int first = 0;
  int last = s.length() - 1;

  while (first < last) {
    if (s[first] != s[last])
      return false;
    ++first;
    --last;
  }
  return true;
}

//! s points to the first character of an arry of n characters
bool is_palindrome(const char s[], int n) {
  int first = 0;
  int last = n - 1;
  while (first < last) {
    if (s[first] != s[last])
      return false;
    ++first;
    --last;
  }
  return true;
}

//! first points to the first letter, last to the last letter
bool is_palindrome(const char *first, const char *last) {
  while (first < last) {
    if (*first != *last)
      return false;
    ++first;
    --last;
    return true;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  const string s{"anna"};
  cout << "is_palindrome(" << s << ")=" << is_palindrome(s) << '\n';

  const char a[] = {'a', 'n', 'n', 'a'};
  cout << "is_palindrome(" << a << ", 4)=" << is_palindrome(a, 4) << '\n';

  const char *f = &a[0];
  const char *l = &a[3];
  cout << "address of a is" << (void *)a << '\n';
  cout << "is_palindrome(" << (void *)f << ", " << (void *)l << ")=" << dec
       << is_palindrome(f, l) << '\n';

  return 0;
}

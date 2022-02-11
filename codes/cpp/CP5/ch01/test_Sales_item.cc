#include "Sales_item.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  using namespace std;

  Sales_item total;
  if (cin >> total) {
    Sales_item trans;
    while (cin >> trans) {
      if (total.isbn() == trans.isbn()) {
        total += trans;
      } else {
        cout << total << endl;
        total = trans;
      }
    }
    cout << total << endl;
  } else {
    cerr << "No data?!" << endl;
    return -1;
  }

  return 0;
}

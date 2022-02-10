# Part IV Broadening the View

## 22 Ideals and History
### 22.1 History, ideals, and professionalism
### 22.2 Programming language history overview

## 23 Text Manipulation
### 23.1 Text

``` c++
iostream
string
```

### 23.2 Strings

``` c++
#include <string>

string
basic_string

using string = basic_string<char>;

stringstream
ostringstream
istringstream
```

### 23.3 I/O streams

``` c++
istream
istringstream
ifstream

ostream
ostringstream
ofstream

iostream
stringstream
fstream
```

### 23.4 Maps
### 23.5 A problem
### 23.6 The idea of regular expressions

example: a U.S. state abbreviation and ZIP code(two letters followed by five digits), such as TX77845

none-digit ZIP code format, example TX77845-5629

```
\w{2}\s*\d{5}(-\d{4})?
```

raw string literals: `R"( ... )"`

``` c++
"\\w{2}\\s*\\d{5}(-\\d{4})?"
R"(\w{2}\s*\d{5}(-\d{4})?)"
```

### 23.7 Searching with regular expressions

``` c++
#include <regex>

regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"};

smatch matches;
if (regex_search(line, matches, pat)) {
  cout << matches[0] << '\n';
}
```

### 23.8 Regular expression syntax

characters and special characters:

```
.
[
{
(
)
\
*
+
?
|
^
$
```

character clases:

```
\d
\l
\s
\u
\w
\D
\L
\S
\U
\W
```

repeats:

```
{n}
{n,}
{n,m}
*
+
?
```

grouping: `()`, example: `(\d*:)?(\d+)`

alternation: `|`, example: `Subject: (FW:|Re:)?(.*)`, `FW:` or `Re:`

character sets and ranges: `[]`, example: `[a-zA-Z]`, `[^aeiouy]`

```
alnum
alpha
blank
cntrl
d
digit
graph
lower
print
punct
s
space
upper
w
xdigit
```

errors:

``` c++
regex pat1{"(|ghi)"}; // error: missing alternative
regex pat2{"[c-a]"};  // error: not a range

bad_expression
```

### 23.9 Matching with regular expressions

2 basic uses of regular expression:

- **searching** for a string that matches a regular expression in a stream of data: `regex_search()`,
- **matching** a regular expression against a string: `regex_match()`.

### 23.10 References

## 24 Numerics
### 24.1 Introduction
### 24.2 Size, precision, and overflow

``` c++
cout << setprecision(15) << enum << '\n';
```

numeric limits:

``` c++
#include <limits>
#include <climits>
#include <limits.h>
#include <float.h>
```

### 24.3 Arrays
### 24.4 C-style multidimensional arrays

``` c++
int ai[4];
double ad[3][4];
char ac[3][4][5];

ai[1] = 7;
ad[2][3] = 7.2;
ac[2][3][4] = 'c';
```

pass multidimensional arrays:

``` c++
void f1(int a[3][5]);                 // useful for [3][5] matrix only
void f2(int [][5], int dim1);         // 1st dimension can be a variable
void f3(int [5][], int dim2);         // error: 2nd dimension cannot be a variable
void f4(int[][], int dim1, int dim2); // error
void f5(int *m, int dim1, int dim2);  // odd, but works
```

### 24.5 The Matrix library

``` c++
#include "Matrix.h"
using namespace Numeric_lib;
```

### 24.6 An example: solving linear equations
### 24.7 Random numbers

``` c++
#include <random>

default_random_engine ran{};
uniform_real_distribution<> ureal{0,max};
ureal(ran);

#include <functional>
auto gen = bind(normal_distribution<double>{15,4.0}, default_random_engine{});
gen();
```

### 24.8 The standard mathematical functions

``` c++
#include <cmath>
```

### 24.9 Complex numbers

``` c++
#include <complex>
```

### 24.10 References

## 25 Embedded Systems Programming
### 25.1 Embedded systems
### 25.2 Basic concepts
#### 25.2.1 Predictability

all facilities in the C++ language are predictable, except:

- free-store allocation using `new` and `delete`,
- exceptions,
- `dynamic_cast`.

#### 25.2.2 Ideals
#### 25.2.3 Living with failure

### 25.3 Memory management

in C++, there are 3 ways to allocate memory to hold data:

- **static memory**: allocated by the linker, persisting as long as the program runs,
- **statck(automatic) memory**: allocated when we call a function and freed when we return from the function,
- **dynamic(heap) memory**: allocated by `new` and freed for possible reuse by `delete`.

#### 25.3.1 Free-store problems
#### 25.3.2 Alternatives to the general free store

**stack**: a stack is a data structure where you can allocate an arbitrary amount of memeory (up to a given maximum size) and deallocate the last allocation only.

**pool**: a pool is a collection of objects of the same size. we can allocate and deallocate objects as long as we don't allocate more objects than the pool can hold.

#### 25.3.3 Pool example
#### 25.3.4 Stack example

### 25.4 Addresses, pointers, and arrays
#### 25.4.1 Unchecked conversions

``` c++
Device_driver* p = reinterpret_cast<Device_driver*>(0xffb8);
```

#### 25.4.2 A problem: dysfunctional interfaces

``` c++
// poor interface design
// use Shape* as a pointer and an array
void poor(Shape* p, int sz)
{
  for (int i = 0; i < sz; ++i) p[i].draw();
}

// sizeof(Circle) > sizeof(Shape)
// sizeof(Polygon) == sizeof(Shape)

void f(Shape* q, vector<Circle>& s0)
{
  Polygon s1[10];
  Shape s2[10];
  Shape* p1 = new Rectangle{Point{0,0},Point{10,20}};
  poor(&s0[0],s0.size()); // #1 passing wrong element type
  poor(s1,10);            // #2 passing wrong element type, correct magic constant
  poor(s2,20);            // #3 incorrect magic constant
  poor(p1,1);             // #4 correct
  delete p1;
  p1 = 0;
  poor(p1,1);             // #5 passing a null pointer
  poor(q,max);            // #6 need further information
}
```

#### 25.4.3 A solution: an interface class

``` c++
template<typename T>
class Array_ref
{
  // ...
private:
  T* p;
  int sz;
};


void better(Array_ref<Shape> a)
{
  for (int i = 0; i < a.size(); ++i) a[i].draw();
}
```

#### 25.4.4 Inheritance and containers

``` c++
void better2(const Array_ref<Shape* const> a)
{
  for (int i = 0; i < a.size(); i++)
    if (a[i]) a[i]->draw();
}
```

`vector<Circle>` is not a `vector<Shape>`

how do we express the idea that `Array_ref<Circle *>` can be converted:

- to something like `Array_ref<Shape *>`,
- but only to an **immutable** version of `Array_ref<Shape *>` ?

``` c++
template<typename T>
class Array_ref {
public:
  template<typename Q>
  operator const Array_ref<const Q>()
  {
    static_cast<Q>(*static_cast<T*>(nullptr));              // check implicit conversion of element
    return Array_ref<const Q>{reinterpret_cast<Q*>(p), sz}; // convert Array_ref
  }
  // ...  
};
```

### 25.5 Bits, bytes, and words
#### 25.5.1 Bits and bit operations

bitwise operations:

```
|   // or
&   // and
^   // exclusive or
<<  // left shift
>>  // right shift
~   // complement
```

#### 25.5.2 `bitset`

``` c++
#include <bitset>
```

#### 25.5.3 Signedn and unsigned

the leftmost (most significant bit) is taken as the "sign not": 1 for nagative numbers.

#### 25.5.4 Bit manipulation
#### 25.5.5 Bitfields

``` c++
// R6000 Physical Page Number
struct PPN {
  unsigned int PFN : 22;  // Page Frame Number
  int : 3;                // unused
  unsigned int CCA : 3;   // Cache Coherency Algorithm
  bool nonreachable : 1;
  bool dirty : 1;
  bool valid : 1;
  bool global : 1;
};
```

#### 25.5.6 An example: simple encryption

### 25.6 Coding standards
#### 25.6.1 What should a coding standard be?
#### 25.6.2 Sample rules
#### 25.6.3 Real coding standards

- **Google C++ Style Guide**: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml. A rather old-style and restrictive but evolving style guide.

- Lockheed Martin Corporation. **Joint Strike Fighter Air Vehicle Coding Standards for the System Development and Demonstration Program**. Document Number 2RDU00001 Rev C. December 2005. Colloquially known as “JSF++”; a set of rules written at Lockheed-Martin Aero for air vehicle (read “airplane”) software. These rules really were written by and for programmers who produce software upon which human lives depend. www.stroustrup.com/JSF-AV-rules.pdf.

- Programming Research. **High-integrity C++ Coding Standard Manual Version 2.4**. www.programmingresearch.com.

- Sutter, Herb, and Andrei Alexandrescu. **C++ Coding Standards: 101 Rules, Guidelines, and Best Practices**. Addison-Wesley, 2004. ISBN 0321113586. This is more of a “meta coding standard”; that is, instead of specific rules it has guidance on which rules are good and why.

## 26 Testing
### 26.1 What we want
### 26.2 Proofs
### 26.3 Testing
#### 26.3.1 Regression tests
#### 26.3.2 Unit tests
#### 26.3.3 Algorithms and non-algorithms
#### 26.3.4 System tests
#### 26.3.5 Finding assumptions that do not hold

### 26.4 Design for testing
### 26.5 Debugging
### 26.6 Performance
### 26.7 References

- Stone, Debbie, Caroline Jarrett, Mark Woodroffe, and Shailey Minocha. **User Interface
Design and Evaluation**. Morgan Kaufmann, 2005. ISBN 0120884364.

- Whittaker, James A. **How to Break Software: A Practical Guide to Testing**. Addison-
Wesley, 2003. ISBN 0321194330.

## 27 The C Programming Language
### 27.1 C and C++: siblings
#### 27.1.1 C/C++ compatibility

References:

- ISO/IEC 9899:1999. **Programming Languages — C**. This defines C99; most implementations implement C89 (often with a few extensions).
- ISO/IEC 9899:2011. **Programming Languages — C**. This defines C11.
- ISO/IEC 14882:2011. **Programming Languages — C++**.
- Kernighan, Brian W., and Dennis M. Ritchie. **The C Programming Language**. Prentice Hall, 1988. ISBN 0131103628.
- Stroustrup, Bjarne. **“Learning Standard C++ as a New Language.”** C/C++ Users Journal, May 1999.
- Stroustrup, Bjarne. **“C and C++: Siblings”**; **“C and C++: A Case for Compatibility”**; and **“C and C++: Case Studies in Compatibility.”** The C/C++ Users Journal, July, Aug., and Sept. 2002.

#### 27.1.2 C++ features missing from C
#### 27.1.3 The C standard library

### 27.2 Functions
#### 27.2.1 No function name overloading
#### 27.2.2 Function argument type checking
#### 27.2.3 Function definitions
#### 27.2.4 Calling C from C++ and C++ from C
#### 27.2.5 Pointers to functions

### 27.3 Minor language differences
#### 27.3.1 `struct` tag namespace
#### 27.3.2 Keywords
#### 27.3.3 Definitions
#### 27.3.4 C-style casts
#### 27.3.5 Conversion of `void*`
#### 27.3.6 `enum`
#### 27.3.7 Namespaces

### 27.4 Free store
### 27.5 C-style strings
#### 27.5.1 C-style strings and `const`
#### 27.5.2 Byte operations
#### 27.5.3 An example: `strcpy()`
#### 27.5.4 A style issue

### 27.6 Input/output: stdio
#### 27.6.1 Output
#### 27.6.2 Input
#### 27.6.3 Files

### 27.7 Constants and macros
### 27.8 Macros
#### 27.8.1 Function-like macros
#### 27.8.2 Syntax macros
#### 27.8.3 Conditional compilation

### 27.9 An example: intrusive containers

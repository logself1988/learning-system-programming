# Part I The Basics

## 2 Variables and Basic Types

> This chapter covers the built-in types and begins our coverage of how C++ supports more complicated types.

``` c++
i = i + j;  // int, Sales_item
```


### 2.1 Primitive Built-in Types
#### 2.1.1 Arithmetic Types

``` c++
            // meaning                            minimum size
bool        // boolean                            NA
char        // character                          8 bits
wchar_t     // wide character                     16 bits
char16_t    // Unicode character                  16 bits
char32_t    // Unicode character                  32 bits
short       // short integer                      16 bits
int         // integer                            16 bits
long        // long integer                       32 bits
long long   // long integer                       64 bits
float       // single-precision floating-point    6 significant digits
double      // double-precision floating-point    10 significant digits
long double // extended-precision floating-point  10 significant digits
```

> Except for `bool` and the extended character types, the integral types may be `signed` or `unsigned`.

signed and unsigned types:

- all signed: `int`, `short`, `long`, `long long`
- `char`, `signed char`, `unsigned char`: `char` is not the same type as `signed char`

#### 2.1.2 Type Conversions

> Type conversion happen automatically when we use an object of one type where an object of another type is expected.

> We'll have more to say about conversions in § 4.11 (p. 159)

> The compiler applies these same type conversions when we use a value of one arithmetic type where a value of another arithmetic type is expected.

``` c++
int i = 42;
if (i) // condition will evaluate as true
  i = 0;
```

> For example, if we use both `unsigned` and `int` values in an arthmetic expression, the `int` value ordinarily is converted to `unsigned`.

#### 2.1.3 Literals

integer and floating-point literals:

``` c++
20        // decimal
024       // octal
0x14      // hexadecimal

3.14159
3.14159E0 // scientific notation
0.
0e0
.001
```

character and character string literals:

``` c++
'a'             // character literal
"Hello World!"  // string literal

// multiline string literal
std::cout << "a really, really long string literal "
  "that spans two lines" << std::endl;
```

escape sequences:

- `\n`, `\t`, `\a`, `\v`, `\b`, `\"`, `\\`, `\?`, `\'`, `\r`, `\f`,
- `\x` followed by one or more hexadecimal digits: `\x4d ('M')`,
- `\` followed by one, two, or three octal digits: `\115 ('M')`.

specifying the type of a literal:

- character and character string literals: prefix `u` for `char16_t`, `U` for `char32_t`, `L` for `wchar_t`, `u8` for utf-8 `char`;
- integer literals: suffix `u`/`U` for `unsigned`, `l`/`L` for `long`, `ll`/`LL` for `long long`;
- floating-point literals: suffix `f`/`F` for `float`, `l`/`L` for long double

``` c++
L'a'      // wchar_t
u8"hi1"   // utf-8 string literal
42ULL     // unsigned long long
1E-3F     // float
3.14159L  // long double
```

boolean and pointer literals:

``` c++
true
false

nullptr
```

### 2.2 Variables

a **variable** provides us with named storage that our programs can manipulate.

#### 2.2.1 Variable Definitions

``` c++
int sum = 0, value, units_sold = 0;
Sales_item item;
std::string book("0-201-78345-X");
```

initializers:

``` c++
double price = 109.99, discount = price * 0.16;
double salePrice = applyDiscount(price, discount);
```

list initialization:

``` c++
int units_sold = 0;
int units_sold = {0};
int units_sold{0};
int units_sold(0);

long double ld = 3.1415926536;
int a{ld}, b = {ld};  // error: narrowing conversion required
int c(ld), d = ld;    // ok: be truncated
```

default initialization:

``` c++
std::string empty;
Sales_item item;
```

#### 2.2.2 Variable Declarations and Definitions

> To allow programs to be written in logical parts, C++ suports what is commonly known as **seperate compilation**. Separate compilation lets us split our programs into several files, each of which can be compiled independently.

To support seperate compilation, C++ distinguishes between declarations and definitions:

- a **declaration** makes a name known to the program,
- a **definition** create the associated entity.

``` c++
extern int i;               // declares but does not define i
int j;                      // declares and defineds j

extern double pi = 3.1416;  // definition
```

> Variables must be defined exactly once but can be declared many times.

#### 2.2.3 Identifiers

> Identifiers in C++ can be composed of letters, digits, and the underscore character.
> Identifiers are case-sensitive.

#### 2.2.4 Scope of a Name

> A scope is a prat of the program in which a name has a particular meaning.
> Most scopes in C++ are delimited by curly braces `{}`.

### 2.3 Compound Types
#### 2.3.1 References

> A **reference** defines an alternative name for an object.

``` c++
int ival = 1024;
int &refVal = ival; // refVal refers to ival
int &refVal2;       // error: a reference must be initialized
```

When we define a reference, instead of copying the initializer's value, we **bind** the reference to its initializer.

Once initialized, a reference remains bound to its initial object. There is no way to rebind a reference to refer to a different object.

a reference is an alias:

> A reference is not an object. Instead, a reference is just another name for an already existing object.
> We may not define a reference to a reference.

After a reference has been defined, all operations on that reference are actually operations on the object to which the reference is bound:

``` c++
refVal = 2;             // assign 2 to the object to which refVal refers, i.e. to ival
int ii = refVal;        // same as ii = ival

int &refVal3 = refVal;  // refVal3 refers to ival
int i = refVal;         // same as i = ival
```

reference definitions:

``` c++
int i = 1024, i2 = 2048;  // ii, i2: int
int &r = i, r2 = i2;      // r: a reference bound to i, r2: int
int i3 = 1024, &ri = i3;  // i3: int, ri: a reference bound to i3
int &r3 = i3, &r4 = i2;   // r3, r4: references
```

!!! info "the type of a reference and the object to which it refers"
    With two exceptions that we'll cover in § 2.4.1 (p. 61) and § 15.2.3 (p. 601), the type of a reference and the object to which the reference refers must match exactly.

``` c++
int &refVal4 = 10;    // error: initializer must be an object
double dval = 3.14;
int &refVal5 = dval;  // error: initializer must be an int object
```

#### 2.3.2 Pointers

> A **pointer** is a compound type that "points to" another type.

taking the address of an object: the address-of operator `&`

``` c++
int ival = 42;
int *p = &ival; // p holds the address of ival; p is a pointer to ival
```

!!! info "type of the pointer and the object to which it points"
    With two exceptions, which we cover in § 2.4.2 (p. 62) and § 15.2.3 (p. 601), the types of the pointer and the object to which it points must match.

``` c++
double dval;
double *pd = &dval; // ok: initializer is the address of a double
double *pd2 = pd;   // ok: initializer is a pointer to double

int *pi = pd;       // error: types of pi and pd not match
pi = &dval;         // error: assigning the address of a double to a pointer to int
```

The value (i.e. the address) stored in a pointer can be:

1. it can point to an object,
2. it can point to the location just immediately past the end of an object,
3. it can be a null pointer, indicating that it is not bound to any object,
4. it can be invalid; values other than the preceding three are invalid.

using a pointer to access an object: the deference operator `*`

``` c++
int ival = 32;
int *p = &ival;
cout << *p;       // prints 42

*p = 0;
cout << p;        // prints 0
```

null pointers:

> A **null pointer** does not point to any object.

``` c++
int *p1 = nullptr;  // same as int *p1 = 0;
int *p2 = 0;        // directly initialize p2 from the literal constant 0

#include <cstdlib>
int *p3 = NULL;     // same as int *p3 = 0;
                    // NULL: a preprocessor variable
```

> It is illegal to assign an `int` variable to a pointer, even if the variable's value happends to be 0.

``` c++
int zero = 0;
pi = zero;          // error: cannot assign an int to a pointer
```

operations on pointers:

> As with other (non-reference) variable, when we **assign** to a pointer, we give the pointer itself a new value.
> Just as when we use an arithmetic values in a condition, if the pointer is `0`, then the condition is `false`, any non-zero pointer evaluates as `true`.
> Given two valid pointer of the same type, we can compare them using the `==` or `!=` operators.
> § 3.5.3 (p. 117) will cover additional pointer operations.

the type `void*` is a special pointer type that can hold the address of any object.

``` c++
double obj = 3.14, *pd = &obj;
// ok: void* can hold the address value of any data pointer type
void *pv = &obj;
pv = pd;
```

#### 2.3.3 Understanding Compound Type Declarations

> In this book we use the first style and place the `*`(or the `&`) with the variable name.

``` c++
int i = 1024, *p = &i, &r = i;  // i is an int
                                // p is a pointer to int
                                // r is a reference to int

int* p1, p2;                    // p1 is a pointer to int, p2 is an int
int *p1, *p2;                   // p1, p2 are pointers to int
```

pointers to pointers:

``` c++
int ival = 1024;
int *pi = &ival;  // pi points to an int
int **ppi = &pi;  // ppi points to a pointer to an int
```

references to pointers:

``` c++
int i = 42;
int *p;       // p is a pointer to int
int *&r = p;  // r is a reference to the pointer p
r = &i;
*r = 0;
```

### 2.4 `const` Qualifier

We can make a variable unchangeable by defining the variable's type as `const`:

``` c++
const int bufSize = 512;
bufSize = 512;            // error: attempt to write to const object

const int j = get_size(); // ok: initialized at run time
const int j = 42;         // ok: initialized at compile time
const int k;              // error: uninitialized
```

> A `const` type can use most but not all of the same operations as its non-const version. The one restriction is that we may use only those operations that **cannot change an object**.

> Among the operations that don't change the value of an object is **initialization** - when we use an object to initialize another object, it doesn't matter whether either or both of the objects are `const`s:

``` c++
int i = 42;
const int ci = i; // ok: value in i is copied into ci
int j = ci;       // ok: value in ci is copied into j
```

By default, `const` objects are local to file. Sometimes we want to share a `const` variable across multiple files, but whose initalizer is not a constant expression:

``` c++
// file_1.h
extern const int bufSize;         // declaration
// file_1.cc
extern const int bufSize = fcn(); // definition
```

#### 2.4.1 References to `const`

> Unlike an ordinary reference, a reference to `const` cannot be used to change the object to which the reference is bound.

``` c++
const int ci = 1024;
const int &r1 = ci;   // ok: reference and initializer are const
r1 = 42;              // error: r1 is a reference to const
int &r2 = ci;         // error: non-const reference r2 to a const object ci
```

> C++ programmers tend to abbreviate the phrase "reference to `const`" as "`const` reference".

!!! info "a reference to `const`"
    **exception for § 2.3.1 (p. 51)** we can initialized a reference to `const` from any expression that can be **converted** to the type of the reference. In particular, we can bind **a reference to `const`** to a non-const object, a literal, or a more general expression.

``` c++
int i = 42;
const int &r1 = i;      // ok: we can bind a const int& to an int
const int &r2 = 42;     // ok: bind to a literal
const int &r3 = r1 * 2; // ok: bind to an expression value
int &r4 = r1 * 2;       // error: r4 is non-const reference

double dval = 3.14;
const int &ri = dval;   // ok
```

binding a reference to `const` to an object says nothing about whether the underlying object itself is `const`:

``` c++
int i = 42;
int &r1 = i;
const int &r2 = i;
r1 = 0;             // ok: r1 is not const
r2 = 0;             // error: r2 is a reference to const
```

#### 2.4.2 Pointers and `const`

we may store the address of a `const` obbject only in a pointer to `const`:

``` c++
const double pi = 3.14;
double *ptr = &pi;          // error: ptr is a plain pointer
const double *cptr = &pi;   // ok
*cptr = 42;                 // error: cannot assign to *cptr
```

!!! info "a pointer to `const`"
    **exception for § 2.3.2 (p. 52)** we can use **a pointer to `const`** to point to a non-const object.

``` c++
// const double *cptr = ...
double dval = 3.14;
cptr = &dval;         // ok
```

`const` pointers: a `const` pointer must be initialized, and once initialized, its value may not be changed.

> We indicate taht the pointer is `const` by putting the `const` after then `*`.

``` c++
int errNumb = 0;
int *const curErr = &errNumb;   // curErr: always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi;  // pip: a const pointer to a const object

*pip = 2.72;                    // error: pip points to const
if (*curErr) {
  errorHandler();
  *curErr = 0;                  // ok: reset the value of the object to which curErr points
}
```

#### 2.4.3 Top-Level `const`

!!! info "top-level `const`, low-level `const`"
    We can talk independently about whether a pointer is `const` and whether the objects to which it can point are `const`.

    We use the term **top-level const** to indicate that the pointer itself is a `const`.

    When a pointer can point to a `const` object, we refer to that `const` as **low-level const**.

``` c++
int i = 0;
int *const p1 = &i;       // can not change the value of p1, const is _top-level_

const int ci = 42;        // can not change ci; const is _top-level_

const int *p2 = &ci;      // can change p2; const is low-level
const int *const p3 = p2; // right-most const is _top-level_, left-most is not

const int &r = ci;        // const in reference types is always low-level
```

When we copy an object, top-level `const`s are ignored:

``` c++
i = ci;   // top-level const in ci is ignored
p2 = p3;  // top-level const in p3 is ignored
```

while low-level `const` is never ignored:

``` c++
int *p = p3;        // error: p3 has low-level const, p does not
p2 = p3;            // ok: p2 and p3 have same low-level const
p2 = &i;            // ok: we can convert int* to const int*

int &r = ci;        // error: can not bind int& to a const int object
const int &r2 = i;  // ok: can bind const int& to int
```

#### 2.4.4 `constexpr` and Constant Expressions

> A **constant expression** is an expression whose value cannot change and that can be evaluated **at compile time**.

Whether a given object (or expression) is a constant expression dependes on the types and the initializer:

``` c++
const int max_files = 20;         // is constant expression
const int limit = max_files + 1;  // is constant expression
int staff_size = 27;              // not
const int sz = get_size();        // not
```

> Under the new standard, we can ask the compiler to verify that a variable is a constant expression by declaring the variable in a `constexpr` declaration.

``` c++
constexpr int mf = 20;        // 20 is constant expression
constexpr int limit = mf + 1; // mf+1 is constant expression
constexpr int sz = size();    // ok only if size is a constexpr function
```

The types we can use in a `constexpr` are known as **literal types** because they are simple enough to have literal values.

- that arithmetic, reference, and pointer types are literal types,
- `Sales_item`, `std::string` are not literal types,
- other kind of literal types in § 7.5.6 (p. 299) and § 19.3 (p. 832).

> we'll see in § 6.5.2 (p. 239) that the new standard lets us define certain functions as `constexpr`.

> It is important to understand that when we define a pointer in a `constexpr` declaration, the `constexpr` specifier **applies to the pointer**, not the type to which the pointer points.

``` c++
const int *p = nullptr;     // p: a pointer to a const int
constexpr int *q = nullptr; // q: a const pointer to int
```

### 2.5 Dealing with Types
#### 2.5.1 Type Aliases

> A **type alias** is a name that is a synonym for another type.

using `typedef`:

``` c++
typedef double wages;   // wages: double
typedef wages base, *p; // base: double, p: double*

wages hourly, weekly;
```

using **alias declaration**:

``` c++
using SI = Sales_item;  // SI: Sales_item

SI item;
```

> Declarations that use type aliases that represent compound types and `const` can yield surprising results.

``` c++
typedef char *pstring;
const pstring cstr = 0; // cstr: a constant pointer to char
// const (char *) cstr
const pstring *ps;      // ps: a pointer to a constant pointer to char

const char *cstr = 0;   // wrong interpretation of const pstring cstr;
```

#### 2.5.2 The `auto` Type Specifier

> Unlike type specifier, such as `double`, that name a specific type, `auto` tells the compiler to **deduce the type from the initializer**.

``` c++
auto i = 0, *p = &i;    // ok: i is int, p is a pointer to int
auto sz = 0, pi = 3.14; // error: inconsistent types for sz and pi
```

The type that the compiler infers for `auto` is not always exactly the same as the initializer's type:

1. when we use a reference as an initializer, the initializer is the corresponding object: drop `&`

``` c++
int i = 0; &r = i;  // i: int, r: int&
auto a = r;         // a is int - drop &
```

2. `auto` ordinarily ignores (initializer's) top-level `const`s: drop top-level `const`

``` c++
// int i = 0;               // i: int
const int ci = i, &cr = ci; // ci: const int
                            // cr: const int&
auto b = ci;  // b: int - drop const
auto c = cr;  // c: int - drop const and &
auto d = &i;  // d: int*
auto e = &ci; // e: const int*: & of a const object is low-level const
```

want the deduced type to have a top-level `const`: `const auto`

``` c++
// int i = 0;
// const int ci = i;
const auto f = ci;  // f: const int
```

want a reference to the `auto`-deduced type: `auto &`

``` c++
// int i = 0;         // i: int
// const int ci = i;  // ci: const int
auto &g = ci;         // g: const int&
auto &h = 42;         // error: we cannot bind a plain reference to a literal
const auto &j = 42;   // ok: bind a const reference to a literal
```

WHen we ask for a reference to an `auto`-deduced type, top-level `const`s in the initializer are not ignored, see `g` in above example.

define several variables in the same statement:

``` c++
// int i = 0;           // i: int
// const int ci = i;    // ci: const int
auto k = ci, &l = i;    // k: int, l: int& - int
auto &m = ci, *p = &ci; // m: const int&, p: a pointer to const int - const int
auto &n = i, *p2 = &ci; // error:
                        // type deduced from i - int
                        // type deduced from &ci - const int
```

#### 2.5.3 The `decltype` Type Specifier

> Sometimes we want to define a variable with a type that the compiler deduces from an expression but do not want to use that expression to initialize the variable.
> For such cases, the new standard introduced a second type specifier `decltype`, which returns the type of its operand.

When the expression to which we apply `decltype` is a variable, `decltype` returns the type of that variable, **including top-level `const` and references**:

``` c++
const int ci = 0, &cj = ci; // ci: const int
                            // cj: const int&
decltype(ci) x = 0;         // x: const int
decltype(cj) y = x;         // y: const int&
decltype(cj) z;             // error: reference must be initialized
```

Generally speaking, `decltype` returns a reference type for expressions that yield objects that can stand on the left-hand side of the assignment:

``` c++
int i = 42, *p = &i, &r = i;  // i: int
                              // p: int*
                              // r: int&
decltype(r + 0) b;            // b: int
decltype(*p) c;               // error, c: int&
```

When we apply `decltype` to a variable without any parentheses, we get the type of that variable. If we wrap the variable's name in one or more sets of parentheses, the compiler will evaluate the operand as an expression. A variable is an expression that can be the left-hand side of an assignment.

``` c++
decltype((i)) d;  // error, d: int&
decltype(i) e;    // e: int
```

### 2.6 Defining Our Own Data Structures
#### 2.6.1 Defining the `Sales_data` Type

``` c++
struct Sales_data {
  std::string bookNo;
  unsigned units_sold = 0; // in-class initializer
  double revenue = 0;
};
```

> Under the new standard, we can supply an **in-class initializer** for a data member. They must either be enclosed inside curly braces `{}` or follow an `=` sign.

#### 2.6.2 Using the `Sales_data` Class
#### 2.6.3 Writing Our Own Header Files

`Sales_data.h`

C++ programs also use the preprocessor to define **header guards**.

## 3 Strings, Vectors, and Arrays
### 3.1 Namespace `using` Declarations

> A `using` declaration lets us use a name from a namespace without qualifying the name with a `namespace_name::` prefix.

A `using` declaration has the form:

``` c++
using namespace::name;
```

Once the `using` declaration has been made, we can access `name` directly.

> § 18.2.2 (p. 793) covers another way to use names from a namespace.

### 3.2 Library `string` Type

examples assume the following code:

``` c++
#include <string>
using std::string;
```

#### 3.2.1 Defining and Initializing `string`s

Ways to initialize a `string`:

``` c++
string s1;            // default initialization: empty string
string s2(s1);        // s2 is a copy of s1
string s2 = s1;       // s2 is a copy of s1
string s3("value");   // s3 is a copy of the string literal
string s3 = "value";  // s3 is a copy of the string literal
string s4(n, 'c');    // initialize s4 with n copies of the character 'c'
```

#### 3.2.2 Operations on strings

``` c++
os << s               // write s onto putput stream os
is >> s               // read whitespace-separated string from is into s
getline(is,s)         // read a line of input from is into s
s.empty()             // return true if s is empty
s.size()              // return the number of characters in s
s[n]                  // return a reference to the char at position n in s
s1 + s2               // return a string that is the concatenation of s1 and s2
s1 = s2               // replace characters in s1 with a copy of s2
s1 == s2              // return true if they contain the same characters
s1 != s2              //
<, <=, >, >=          // comparasions are case-sensitive and use dictionary orderings
```


- reading and writing `string`s
- reading an unknown number of `string`s
- using `getline` to read an entire line
- the `string` `empty` and `size` operation

``` c++
auto len = line.size(); // len has type string::size_type
```

- comparing `string`s
- assignment for `string`s
- adding two `string`s
- adding literals and `string`s

#### 3.2.3 Dealing with the Characters in a string

- processing every charater? use range-based `for`

``` c++
#include <cctype> // for ispunct

string str("some string");
decltype(s.size()) punct_cnt = 0;
for (auto c : str)
  if (ispunct(c)) ++punct_cnt;
  cout << c << endl;
```

- using a range `for` to change the characters in a `string`

``` c++
#include <cctype> // for toupper

string s("Hello World!");
for (auto &c : s)
  c = toupper(c);
```

- processing only some characters

``` c++
string s("some string");
if (!s.empty())
  cout << s[0] << endl;
```

- using a subscript for iteration

``` c++
for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)
  s[index] = toupper(s[index]);
```

- using a subscript for random access

### 3.3 Library `vector` Type
#### 3.3.1 Defining and Initializing vectors
#### 3.3.2 Adding Elements to a vector
#### 3.3.3 Other vectorOperations

### 3.4 Introducing Iterators
#### 3.4.1 Using Iterators
#### 3.4.2 Iterator Arithmetic

### 3.5 Arrays
#### 3.5.1 Defining and Initializing Built-in Arrays
#### 3.5.2 Accessing the Elementsof an Array
#### 3.5.3 Pointers and Arrays
#### 3.5.4 C-Style Character Strings
#### 3.5.5 Interfacing to Older Code

### 3.6 Multidimensional Arrays

## 4 Expressions
### 4.1 Fundamentals
#### 4.1.1 Basic Concepts
#### 4.1.2 Precedence and Associativity
#### 4.1.3 Order of Evaluation
### 4.2 Arithmetic Operators
### 4.3 Logical and Relational Operators
### 4.4 Assignment Operators
### 4.5 Increment and Decrement Operators
### 4.6 The Member Access Operators
### 4.7 The Conditional Operator
### 4.8 The Bitwise Operators
### 4.9 The sizeof Operator
### 4.10 Comma Operator
### 4.11 Type Conversions
#### 4.11.1 The Arithmetic Conversions
#### 4.11.2 Other Implicit Conversions
#### 4.11.3 Explicit Conversions
### 4.12 Operator Precedence Table

## 5 Statements
### 5.1 Simple Statements
### 5.2 Statement Scope
### 5.3 Conditional Statements
#### 5.3.1 The if Statement
#### 5.3.2 The switch Statement
### 5.4 Iterative Statements
#### 5.4.1 The while Statement
#### 5.4.2 Traditional for Statement
#### 5.4.3 Range for Statement
#### 5.4.4 The do while Statement
### 5.5 Jump Statements
#### 5.5.1 The break Statement
#### 5.5.2 The continue Statement
#### 5.5.3 The goto Statement
### 5.6 try Blocks and Exception Handling
#### 5.6.1 A throw Expression
#### 5.6.2 The try Block
#### 5.6.3 Standard Exceptions

## 6 Functions
### 6.1 Function Basics
#### 6.1.1 Local Objects
#### 6.1.2 Function Declarations
#### 6.1.3 Separate Compilation
### 6.2 Argument Passing
#### 6.2.1 Passing Arguments by Value
#### 6.2.2 Passing Arguments by Reference
#### 6.2.3 const Parameters and Arguments
#### 6.2.4 Array Parameters
#### 6.2.5 main: Handling Command-Line Options
#### 6.2.6 Functions with Varying Parameters
### 6.3 Return Types and the return Statement
#### 6.3.1 Functions with No Return Value
#### 6.3.2 Functions That Return a Value
#### 6.3.3 Returning a Pointer to an Array
### 6.4 Overloaded Functions
#### 6.4.1 Overloading and Scope
### 6.5 Features for Specialized Uses
#### 6.5.1 Default Arguments
#### 6.5.2 Inline and constexpr Functions
#### 6.5.3 Aids for Debugging
### 6.6 Function Matching
#### 6.6.1 Argument Type Conversions
### 6.7 Pointers to Functions

## 7 Classes
### 7.1 Defining Abstract Data Types
#### 7.1.1 Designing the Sales_data Class
#### 7.1.2 Defining the Revised Sales_data Class
#### 7.1.3 Defining Nonmember Class-Related Functions
#### 7.1.4 Constructors
#### 7.1.5 Copy, Assignment, andDestruction
### 7.2 AccessControl and Encapsulation
#### 7.2.1 Friends
### 7.3 Additional Class Features
#### 7.3.1 Class Members Revisited
#### 7.3.2 Functions That Return *this
#### 7.3.3 Class Types
#### 7.3.4 Friendship Revisited
### 7.4 Class Scope
#### 7.4.1 Name Lookup and Class Scope
### 7.5 Constructors Revisited
#### 7.5.1 Constructor Initializer List
#### 7.5.2 Delegating Constructors
#### 7.5.3 The Role of the Default Constructor
#### 7.5.4 Implicit Class-Type Conversions
#### 7.5.5 Aggregate Classes
#### 7.5.6 Literal Classes
### 7.6 static Class Members

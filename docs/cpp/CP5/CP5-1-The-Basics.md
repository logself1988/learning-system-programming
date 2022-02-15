# Part I The Basics

## 2 Variables and Basic Types

> This chapter covers the built-in types and begins our coverage of how C++ supports more complicated types.

``` c++
i = i + j;  // int, Sales_item
```


### 2.1 Primitive Built-in Types
#### 2.1.1 Arithmetic Types

``` c++
bool
char
wchar_t
char16_t
char32_t
short
int
long
long long
float
double
long double
```

> Except for `bool` and the extended character types, the integral types may be `signed` or `unsigned`.

signed and unsigned types:

- all signed: `int`, `short`, `long`, `long long`
- `char`, `signed char`, `unsigned char`: `char` is not the same type as `signed char`

#### 2.1.2 Type Conversions

> We'll have more to say about conversions in § 4.11 (p. 159)

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

When we define a reference, instead of copying the intializer's value, we **bind** the reference to its initializer.

Once initialized, a reference remains bound to its initial object. There is no way to rebind a reference to refer to a different object.

``` c++
int ival = 1024;
int &refVal = ival; // refVal refers to ival
int &refVal2;       // error: a reference must be initialized
```

a reference is an alias:

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

> With two exceptions that we'll cover in § 2.4.1 (p. 61) and § 15.2.3 (p. 601), the type of a reference and the object to which the reference refers must match exactly.

``` c++
int &refVal4 = 10;    // error: initializer must be an object
double dval = 3.14;
int &refVal5 = dval;  // error: intializer must be an int object
```

#### 2.3.2 Pointers

``` c++
int ival = 42;
int *p = &ival; // p holds the address of ival; p is a pointer to ival
```


> With two exceptions, which we cover in § 2.4.2 (p. 62) and § 15.2.3 (p. 601), the types of the pointer and the object to which it points must match.

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

null pointers:

> A **null pointer** does not point to any object.

``` c++
int *p1 = nullptr;  // same as int *p1 = 0;
int *p2 = 0;        // directly intialize p2 from the literal constant 0

#include <cstdlib>
int *p3 = NULL;     // same as int *p3 = 0;

int zero = 0;
pi = zero;          // error: cannot assign an int to a pointer
```

> § 3.5.3 (p. 117) will cover additional pointer operations.

the type `void*` is a special pointer type that can hold the address of any object.

#### 2.3.3 Understanding Compound Type Declarations

> In this book we use the first style and place the `*`(or the `&`) with the variable name.

### 2.4 `const` Qualifier

We can make a variable unchangeable by defining the variable's type as `const`:

``` c++
const int bufSize = 512;
bufSize = 512;            // error: attempt to write to const object

const int j = get_size(); // ok: initialized at run time
const int j = 42;         // ok: initialized at compile time
const int k;              // error: unintialized
```

when we use an object to intialize another object, it doesn't matter whether either or both of the objects are `const`s:

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

**exception for § 2.3.1 (p. 51)** we can intialized a reference to `const` from any expression that can be **converted** to the type of the reference. In particular, we can bind **a reference to `const`** to a non-const object, a literal, or a more general expression:

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

**exception for § 2.3.2 (p. 52)** we can use a pointer to `const` to point to a non-const object:

``` c++
double dval = 3.14;
cptr = &dval;         // ok
```

`const` pointers:

``` c++
int errNumb = 0;
int *const curErr = &errNumb;   // curErr: always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi;  // pip: a const pointer to a const object

*pip = 2.72;                    // error: pip points to const
```

#### 2.4.3 Top-Level `const`

> we can talk independently about whether a pointer is `const` and whether the objects to which it can point are `const`.

> We use the term **top-level const** to indicate that the pointer itself is a `const`.

> When a pointer can point to a `const` object, we refer to that `const` as **low-level const**.

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

> A **constant expression** is an expression whose value cannot change and that can be evaluated at compile time.

> Under the new standard, we can ask the compiler to verify that a variable is a constant expression by declaring the variable in a `constexpr` declaration.

``` c++
constexpr int mf = 20;        // 20 is constant expression
constexpr int limit = mf + 1; // mf+1 is constant expression
constexpr int sz = size();    // ok only if size is a constexpr function
```

> we'll see in § 6.5.2 (p. 239) that the new standard lets us define certain functions as `constexpr`.

> It is important to understand that when we define a pointer in a `constexpr` declaration, the `constexpr` specifier applies to the pointer, not the type to which the pointer points.

``` c++
const int *p = nullptr;     // p: a pointer to a const int
constexpr int *q = nullptr; // q: a const pointer to int
```

### 2.5 Dealing with Types
#### 2.5.1 Type Aliases

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

>　FIXME: read again

> Unlike type specifier, such as `double`, that name a specific type, `auto` tells the compiler to **deduce the type from the initializer**.

``` c++
auto i = 0, *p = &i;    // ok: i is int, p is a pointer to int
auto sz = 0, pi = 3.14; // error: inconsistent types for sz and pi
```

The type that the compiler infers for `auto` is not always exactly the same as the initializer's type:

1. when we use a reference as an intializer, the initializer is the corresponding object: drop `&`

``` c++
int i = 0; &r = i;  // i: int, r: int&
auto a = r;         // a is int
```

2. `auto` ordinarily ignores (intializer's) top-level `const`s: drop top-level `const`

``` c++
// int i = 0;
const int ci = i, &cr = ci; // ci: const int, cr: const int&
auto b = ci;  // b: int
auto c = cr;  // c: int
auto d = &i;  // d: int*
auto e = &ci; // e: const int*: & of a const object is low-level const
```

want the deduced type to have a top-level `const`:

``` c++
// int i = 0;
// const int ci = i;
const auto f = ci;  // f: const int
```

want a reference to the `auto`-deduced type:

``` c++
// int i = 0;
// const int ci = i;
auto &g = ci;       // g: const int&
auto &h = 42;       // error: we cannot bind a plain reference to a literal
const auto &j = 42; // ok: bind a const reference to a literal
```

define several variables in the same statement:

``` c++
// int i = 0;
// const int ci = i;
auto k = ci, &l = i;    // k: int, l: int&
auto &m = ci, *p = &ci; // m: const int&, p: a pointer to const int
auto &n = i, *p2 = &ci; // error: i: int, &ci: const int
```

#### 2.5.3 The `decltype` Type Specifier

### 2.6 Defining Our Own Data Structures
#### 2.6.1 Defining the Sales_data Type
#### 2.6.2 Using the Sales_data Class
#### 2.6.3 Writing Our Own Header Files

## 3 Strings, Vectors, and Arrays
### 3.1 Namespace using Declarations
### 3.2 Library string Type
#### 3.2.1 Defining and Initializing strings
#### 3.2.2 Operations on strings
#### 3.2.3 Dealing with the Characters in a string
### 3.3 Library vectorType
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

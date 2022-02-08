# Part III Data and Algorithms

Chapter 17-21 describe the containers and algorithms part of the C++ standard library, STL.

Chapter 17-19 focus on the design and implementation of the STL container `vector`.

Chapter 17:

- how can we deal with varying amounts of memory?

Chapter 18:

- how can we copy `vector`s?
- how can we provide a subscript operation for them?

Chapter 19:

- how can we have `vectors` with different element types?
- how can we deal with out-of-range errors?

## 17 Vector and Free Store
### 17.1 Introduction
### 17.2 vector basics

``` c++
vector<double> age(4); // a vector with 4 elements of type double
age[0]=0.33;
age[1]=22.0;
age[2]=27.2;
age[3]=54.2;
```

``` c++
// a very simplified vector of doubles (like vector<double>)
class vector {
  int sz;         // the size
  double* elem;   // pointer to the first element (of type double)
public:
  vector(int s);  // constructor: allocate s doubles, let elem point to them, store s in sz
  int size() const { return sz; } // the current size
};
```

### 17.3 Memory, addresses, and pointers

address: a number that indicates a location in memory.

``` c++
int var = 17;
int* ptr = &var;  // ptr hold the address of var
```

pointer: an object that holds an address value.

- *address of* operator `&`: get the address of an object.
- *content of* / *dereference* operator `*`: get the value of the object pointed to.

each type has a corresponding pointer type:

``` c++
int x = 17;
int* pi = &x;     // pointer to int

double e = 2.71828;
double* pd = &e;  // pointer to double
```

``` c++
*pi = 27;       // ok
*pd = 3.14159;  // ok
*pd = *pi;      // ok

int i = pi;     // error: cannot assign an int* to an int
pi = 7;         // error: cannot assign an int to an int*

char* pc = pi;  // error: cannot assig an int* to a char*
pi = pc;        // error: cannot assign a char* to an int*
```

``` c++
sizeof()
```

### 17.4 Free store and pointers

memory layout:

```
|Code         | text
|Static data  |
|Free store   | heap
|Stack        | automatic
```

``` c++
double* p = new double[4]; // allocate 4 doubles on the free store

char* q = new double[4];   // error: cannot assign double* to char*
```

the `new` operator: request memory to be allocated on the free store

- returns a pointer to the allocated memory,
- a pointer value is the address of the first byte of the memory,
- a pointer points to an object of a specified type,
- a poiner does not know how many elements it points to,
- can allocate individual elements or sequences (arrays) of elements.

``` c++
int* pi = new int;          // allocate one int
int* qi = new int[4];       // allocate 4 ints(an array of 4 ints)

double* pd = new double;    // allocate one double
double* qd = new double[n]; // allocate n doubles(an array of n doubles)

// allowing assignment of pointers to different types would allow type errors.
pi = pd;  // error: cannot assign a double* to an int*
pd = pi;  // error: cannot assign an int* to a double*
```

the subscript operator `[]`

``` c++
double* p = new double[4];  // allocate 4 doubles on the free store
double x = *p;              // read the first object pointed to by p
double y = p[2];            // read the 3rd object pointed to by p

*p = 7.7;                   // write to the first object pointed to by p
p[2] = 9.9;                 // write to the 3rd object pointerd to by p

double x = *p;              // read the object pointed to by p
*p = 8.8;                   // write to the object pointed to by p

double x = p[3];            // read the 4th object pointed to by p
p[3] = 4.4;                 // write to the 4th object pointed to by p
double y = p[0];            // p[0] is the same as *p
```

ranges:

``` c++
double *p = new double;         // allocate a double
double *q = new double[1000];   // allocate 1000 doubles

q[700] = 7.7;                   // ok
q = p;                          // let q point to the same as p
double d = q[700];              // error: out-of-range access!
```

intialization:

``` c++
double* p0;                     // uninitialized
double* p1 = new double;        // allocate an uninitialzed double
double* p2 = new double{5.5};   // allocate a double intialized to 5.5
double* p3 = new double[5];     // allocate 5 unintialized doubles

*p0 = 7.0;  // trouble: assign 7.0 to some location in memory

// specify an initializer list
double* p4 = new double[5] {0,1,2,3,4};
double* p5 = new double[] {0,1,2,3,4};

// type X has a default constructor
// type Y has a constructor, but not a default constructor
X* px1 = new X;       // one default-initialzed X
X* px2 = new X[17];   // 17 default-intialized Xs

Y* py1 = new Y;       // error: no default constructor
Y* py2 = new Y{13};   // OK: intialized to Y{13}
Y* py3 = new Y[17];   // error: no default constructor
Y* py4 = new Y[17] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
```

the null pointer `nullptr`, older alternatives: `0`, `NULL`.

``` c++
double* p0 = nullptr;

if (p0 != nullptr) {}

if (p0) {}
```

return memory to the free store:

- `delete p`: frees the memory for an individual object allocated by `new`,
- `delete[] p`: frees the memory for an array of objects allocated by `new`.

``` c++
double* calc(int res_size, int max)
{
  double* p = new double[max];
  double* res = new double[res_size];
  // use p to calculate results to be put in res
  delete[] p;
  return res;
}

double* r = calc(100, 1000);
// use r
delete[] r;
```

deleteing an object twice is a bad mistake, deleting the null pointer doesn't do anything.

``` c++
int* p = new int{5};
delete p;
// no use of p here
delete p; // error: p points to memory owned by the free-store manager
```

``` c++
int* p = nullptr;
delete p; // no action needed
delete p; // ok: still no action needed
```

### 17.5 Destructors

``` c++
class vector {
  int sz;
  double* elem;
public:
  vector(int s): sz{s}, elem{new double[s]}
  {
    for (int i = 0; i < s; i++) elem[i] = 0;
  }
  int size() const { return sz; }
  // ...
};
```

destructor: a function that does the opposite of a constructor

- a constructor is implicitly called when an object of a class is created,
- a destructor is implicitly called when an object goes out of scope.

``` c++
class vector {
  // ...
public:
  ~vector() { delete[] elem; }
  // ...
};
```

destructors are called when object is destroyed: by going out of scope, by `delete`, etc

- if a member of a class has a destructor, the that destructor will be called when the object containing the memeber is destroyed.
- the destructors for members, and for bases, are implicitly called from a derived class destructor (whether user-defined or generated).

as a rule of thumb: if you have a class with a `virtual` function, it needs a `virtual` destructor.

``` c++
Shape* p = new Text{Point{100,100}, "Nicholas"}; // virtual ~Shape () {}
// use p
delete q;
```

### 17.6 Access to elements
### 17.7 Pointers to class objects

unless you have a good strategy for deleting objects, try to keep `new`s in constructor and `delete`s in destructors.

access members:

- the dot operator `.`: given the name of an object,
- the arrow operator `->`: given a pointer to an object.

``` c++
vector v(4);
int x = v.size();
double d = v.get(3);

vector* p = new vector(4);
int x = p->size();
double d = p->get(3);
```

### 17.8 Messing with types: void* and casts

type `void*`: pointer to some memory that the compiler doesn't know the type of.

there are no objects of type `void`, bu we use `void` to mean "no value returned":

``` c++
void v;   // error
void f(); // returns nothing
```

a pointer to any object type can be assigned to a `void *`.

``` c++
void* pv1 = new int;        // ok: int* converts to void*
void* pv2 = new double[10]; // ok: double* converts to void*
```

explicit type convertion/cast:

- `static_cast`: explicitly convert between related pointer types, such as `void *` and `double *`.
- `reinterpret_cast`: cast between unrelated types, such as `int` and `double *`.
- `const_cast`: cast away `const`.

``` c++
void f(void* pv)
{
  void* pv2 = pv;   // copying is ok
  double* pd = pv;  // error: cannot convert void* to double*
  *pv = 7;          // error: cannot dereference a void*
  pv[2] = 9;        // error: cannot subscript a void*
  int* pi = static_cast<int*>(pv); // ok: explicit conversion
}

Register* in reinterpret_cast<Register*>(0xff);

void f(const Buffer* p)
{
  Buffer* b = const_cast<Buffer*>(p);
}
```

### 17.9 Pointers and references

think of a reference as:

- an automatically dereferenced immutable pointer, or
- an alternative name for an object.

pointers and references differ in these ways:

- assignment to a **pointer** changes the pointer's value (not the pointed-to-value);
- to get a **pointer**, you generally need to use `new` or `&`;
- to access an object pointed to by a **pointer**, you use `*` or `[]`;
- assignment to a **reference** changes the value of the object referred to (not the reference itself);
- you cannot make a **reference** refer to a different object after initialization;
- assignment of **references** does deep copy (assigns to the referred-to object); assignment of **pointers** does not (assigns to the pointer object itself);
- beware of null pointers.

> pointer examples

``` c++
int x = 10;
int* p = &x;      // need & to get a pointer
*p = 7;           // use * to assign to x through p
int x2 = *p;      // read x trough p
int* p2 = &x2;    // get a pointer to another int
p2 = p;           // p2 and p both point to x
p = &x2;          // make p point to another object
```

> reference examples

``` c++
int y = 10;
int& r = y;       // the & is in the type
r = 7;            // assign to y through r
int y2 = r;       // read y through r
int& r2 = y2;     // get a reference to another int
r2 = r;           // the value of y is assigned to y2
r = &y2;          // error: cannot change the value of a reference
```

#### 17.9.1 Poiter and reference parameters

``` c++
int incr_v(int x) { return x+1; } // compute a new value and return
void incr_p(int* p) { ++*p; }     // pass a pointer, dereference it and increment the result
void incr_r(int& r) { ++r; }      // pass a reference

int x = 2;
x = incr_v(x);  // copy x to incr_v(), then copy the result out and assign it

int x = 7;
incr_p(&x);
incr_r(x);

incr_p(nullptr);  // error: incr_p() dereference the null pointer
int* p = nullptr;
incr_p(p);        // error
```

``` c++
void incr_p(int* p)
{
  if (p == nullptr) error("null pointer arguemnts to incr_p()");
  ++*p;
}
```

how do wee choose between using a reference argument and using a pointer argument?

- for tiny objects prefer pass-by-value;
- for functions where no objects (`nullptr`) is a valid argument, use a pointer parameter;
- otherwise, use a reference parameter.

#### 17.9.2 Pointers, references, and inheritance

a `Circle*` can be implicitly converted to a `Shape*`, because `Shape` is a public base of `Circle`; and similarly for references.

``` c++
void rotate(Shape* s, int n); // rotate *s n degrees

Shape* p = new Circle{Point{100,100},40};
Circle c{Point{200,200},50};

rotate(p,35);
rotate(&c,45);

void rotate(Shape& s, int n);
Shape& r = c;
rotate(r,55);
rotate(*p,65);
rotate(c,75);
```

#### 17.9.3 An example: lists

a list is made out of **links** where each link holds some information and pointers to other link.

see `ch17/ex02_lists.cc`

#### 17.9.4 List operations
#### 17.9.5 List use

### 17.10 The `this` pointer

`this` points to the object for which a member function is called.

``` c++
struct S {
    // ...
    void mutate(S* p)
    {
      this = p; // error: this is immutable
      // ...
    }
};
```

## 18 Vectors and Arrays
### 18.1 Introduction

copying:

- what do we mean by copying a nontrivial object?
- to what extent are the copies independent after a copy operation?
- what copy operations are there? how do we specify them?
- how do they relate to other fundamental operations, such as initialization and cleanup?

### 18.2 Initialization

a `{}`-delimited list of elements of type `T` is presented to the programmer as an object of the standard library type `initializer_list<T>`, a list of `T`s.

``` c++
class vector {
  // ...
public:
  vector(int s): sz{s}, elem{new double{sz}}
  {
    for (int i = 0; i < sz; i++) elem[i] = 0.0; // initalize
  }
  vector(initializer_list<double> lst): sz{lst.size()}, elem{new double[sz]}
  {
    copy(lst.begin(), lst.end(), elem); // initalize, use std::copy()
  }
};

vector v1 = {1,2,3};  // 3 elements: 1.0, 2.0, 3.0
vector v2(3);         // 3 elements: each with default value 0.0
vector v3{3};         // 1 element: 3.0

// the = before an {} initializer list is optional
vector v11 = {1,2,3}; // 3 elements: 1.0, 2.0, 3.0
vector v12{1,2,3};    // 3 elements: 1.0, 2.0, 3.0
```

### 18.3 Copying

the default meaning of copying for a class is "Copy all the data members".

#### 18.3.1 Copy constructors

copy constructor: a constructor that copies, it is defined to take as its argument a reference to the object from which to copy.

``` c++
vector(const vector&);

vector v2 = v;
vector v2{v};
```

#### 18.3.2 Copy assignments

the default meaning of copy assignment is memberwise copy.

``` c++
vector& operator=(const vector&);

v2 = v;
v = v; // self assignment
```

#### 18.3.3 Copy terminology

**shallow copy**: copy only a pointer so taht the two pointers now refer to the same object.

**deep copy**: copy what a pointer points to so that the two pointers now refer to distinct objects.

types that provide shallow copy are said to have **pointer semantics** or **reference semantics**, they copy addresses.

types that provide deep copy are said to have **value semantics**.

#### 18.3.4 Moving

``` c++
vector fill(istream& is)
{
  vector res;
  for (double x; is >> x;) res.push_back(x);
  return res;
}

void use()
{
  vector vec = fill(cin); // expensive copying
  // use vec
}
```

``` c++
vector(vector&&);             // move constructor
vector& operator=(vector&&);  // move assignment
```

### 18.4 Essential operations

7 essential operations:

- 1. constructors from one or more arguments

usually we need one or more constructors that take arguments needed to initialize an object.

usually we use a **constructor** to establish an invariant.

- 2. default constructor

we need a **default constructor** if we want to be able to make objects of the class without specifying an intializer.


Q: when does it make sense to have a default constructor?

A: when we can establish the invariant for the class with a meaningful and obvious default value.

- 3. copy constructor (copy object of same type)
- 4. copy assignment (copy object of same type)
- 5. move constructor (move object of same type)
- 6. move assignment (move object of same type)
- 7. destructor

a class needs a destructor if it acquires resources.

another sign that a class needs a destructor is simply that it has members that are **pointers** or **references**.

a class that needs a destructor almost also needs a **copy constructor** and a **copy assignment**.

a class that needs a destructor almost also needs a **move constructor** and a **move assignment**.

a base class for which a derived class may have a destructor needs a `virtual` destructor.

#### 18.4.1 Explicit constructors

a constructor that takes a **single** argument defines a **conversion** from its argument type to its class.

``` c++
class complex {
public:
  complex(double);          // defines double-to-complex conversion
  complex(double, double);
};

complex z1 = 3.14; // ok: convert 3.14 to (3.14, 0)
complex z2 = complex{1.2, 3.4};
```

a constructor defined `explicit` provides only the usual construction semantics and not the implicit conversion:

``` c++
class vector {
  // ...
  explicit vector(int);
};

vector v = 10;  // error: no int-to-vector conversion
v = 20;         // error: no int-to-vector conversion
vector v0(10);  // ok

void f(const vector&);
f(10);          // error: no int-to-vector conversion
f(vector(10));  // ok
```

#### 18.4.2 Debugging constructors and destructors

think of constructors and destructors this way:

- whenever an object of type `X` is created, one of `X`'s constructors is invoked: a variable is intitalized, an object is create using `new`, an object is copied.
- whenever an object of type `X` is destroyed, `X`'s destructor is invoked: names go out of scope, program terminates, `delete` is used on a pointer to an object.

### 18.5 Access to vector elements

``` c++
class vector {
  // ...
  double &operator[](int n) { //!< operator[], return reference
    return elem[n];
  }

  double operator[](int n) const { //!< for const vectors
    return elem[n];
  }
};
```

### 18.6 Arrays

An array is a homogeneous sequence of objects allocated in contiguous memory:

- all element of an array have the same type and
- there are no gaps between the objects of the sequence,
- the elements of an array are numbered from 0 upward.

``` c++
const int max = 100;
int gai[max]; // a global array of 100 ints

void f(int n)
{
  char lac[20];   // local array
  int lai[60];
  double lad[n];  // error: array size not a constant
}
```

limitation: the number of elements of a named array must be known at compile time. if we want the number of elements to be a variable, we must put it on the free store and acess it through a pointer.

access named arrays using the subscript and dereference operators `[]` and `*`:

``` c++
void f2()
{
  char lac[20];   // local array
  lac[7] = 'a';
  *lac = 'b';     // equal to lac[0] = 'b'

  // arrays do not range check
  lac[-2] = 'b';  // ?
  lac[2--] = 'c'; // ?
}
```

#### 18.6.1 Pointers to array elements

``` c++
double ad[10];
double* p = &ad[5]; // point to ad[5]

// subscript and dereference
*p = 7;
p[2] = 6;
p[-3] = 9;

// pointer arithmetic

p += 2;
p -= 5;

p += 1000;      // ?
double d = *p;  // ?
*p = 12.34;     // ?

for (double* p = &ad[0]; p < &ad[10]; ++p) {}
for (double* p = &ad[9]; p >= &ad[0]; --p) {}

double* p1 = &ad[0];
double* p2 = p1+7;
double* p3 = &p1[7]; // p2 == p3
```

#### 18.6.2 Pointers and arrays

the name of an arry refers to all the elements of the array:

``` c++
char ch[100]; // sizeof(ch) == 100
char* p = ch; // p == &ch[0], sizeof(p) == 4
```

the pointer we get from treating the name of an array as a pointer to its first element is a **value** and not a variable:

``` c++
char ac[10];
ac = new char[20];      // error: no assignment to array name
&ac[0] = new char[20];  // error: no assignment to pointer value
```

we cannot copy arrays using assignment:

``` c++
int x[100];
int y[100];

x = y;          // error
int z[100] = y; // error
// use memcpy() or std::copy() instead
```

#### 18.6.3 Array intialization

an array of `char`s can be initialized with a string literal.

``` c++
char ac[] = "Beorn"; // C-style string: a terminating zero character
```

all string literals are C-style strings.

all arrays can be intialized by a list of values of their element type:

``` c++
int ai[] = {1,2,3,4,5,6};             // array of 6 ints
int ai2[100] = {0,1,2,3,4,5,6,7,8,9}; // the last 90 elements are intialized to 0
double ad[100] = {};                  // all elements intialized to 0.0
char chars[] = {'a','b','c'};         // no terminating 0
```

#### 18.6.4 Pointer problems

all serious problems with pointers involve:

- trying to access something that isn't an object of the expected type,
- access outside the bounds of an array.

cautions:

- do not access through the null pointer;

``` c++
int* p = nullptr;
*p = 7; // ?
```

- do intialize pointers;

``` c++
int* p;
*p = 9; // ?
```

- do not access nonexistent array elements;

``` c++
int a[10];
int* p = &a[10];
*p = 11;    // ?
a[10] = 12; // ?
```

- do not access through a deleted pointer;

``` c++
int* p = new int{7};
// ...
delete p;
// ...
*p = 13; // ?
```

- do not return a pointer to a local variable.

``` c++
int* f()
{
  int x = 7;
  // ...
  return &x;
}


int *p = f();
// ...
*p = 15; // ?
```


### 18.7 Examples: palindrome

a palindrome is a word that is spelled the same from both ends, example: anna, petep, malayalam.

#### 18.7.1 Palindromes using `string`

``` c++
bool is_palindrome(const string& s);
```

#### 18.7.2 Palindromes using arrays

``` c++
// s points to the first character of an arry of n characters
bool is_palindrome(const char s[], int n);
```

#### 18.7.3 Palindromes using pointers

``` c++
// first points to the first letter, last to the last letter
bool is_palindrome(const char* first, const char* last);
```

## 19 Vector, Templates, and Exceptions
### 19.1 The problems

concerns:

- how do we change the size of a `vector`?
- how do we catch and report out-of-range `vector` element access?
- how do we specify the element type of a `vector` as an argument?

for `vector`, we can vary two things:

- the number of elements,
- the type of elements.

### 19.2 Changing size

``` c++
vector<double> v(n);

// change v's size
v.resize(10);
v.push_back(7);
v = v2;
```

#### 19.2.1 Representation

``` c++
class vector {
  int sz;         // number of elements
  double* elem;   // addres of first element
  int space;      // number of elements pls free space/slots
  // ...
};
```

#### 19.2.2 `reserve` and `capacity`

``` c++
//  add space for new elements
void vector::reserve(int newalloc)
{
  if (newalloc <= space) return;
  double* p = new double[newalloc];
  for (int i = 0; i < sz; i++) p[i] = elem[i]; // copy old elements
  delete[] elem;
  elem = p;
  space = newalloc;
}

int vector::capacity() const { return space; }
```

#### 19.2.3 `resize`

``` c++
void vector::resize(int newsize)
{
  reserve(newsize);
  for (int i = sz; i < newsize; i++) elem[i] = 0;
  sz = newsize;
}
```

#### 19.2.4 `push_back`
#### 19.2.5 Assignment
#### 19.2.6 Our `vector` so far

### 19.3 Templates

basically, a **template** is a mechanism that allows a programmer to use type as parameters for a class or a function; the compiler then generates a specific class or funtion when we later provide specific types as arguments.

#### 19.3.1 Types as template parameters
#### 19.3.2 Generic programming
#### 19.3.3 Concepts

we call a set of requirements on a template argument a **concept**.

``` c++
// C++11
template<typename T>    // for all types T
class vector {};

// C++14
template<typename T>    // for all types T
  requires Element<T>() // such that T is an Element
class vector {};

// shorthand notation
template<Element T>
class vector {};

// before C++14
template<typename Elem> // requires Element<Elem>()
class vector {};
```

some common and useful concepts:

``` c++
Element<E>()
Container<C>()
Forward_iterator<For>()
Input_iterator<In>()
Output_iterator<Out>()
Random_access_iterator<Ran>()
Allocator<A>()
Equal_comparable<T>()
Equal_comparable<T,U>()
Predicate<P,T>()
Binary_predicate<P,T>()
Binary_predicate<P,T,U>()
Less_comparable<L,T>()
Less_comparable<L,T,U>()
Binary_operation<B,T,U>()
Binary_operation<B,T,U>()
Number<N>()
```

#### 19.3.4 Containers and inheritance
#### 19.3.5 Integers as template parameters
#### 19.3.6 Template argument deduction
#### 19.3.7 Generalizing `vector`

### 19.4 Range checking and exceptions
#### 19.4.1 An aside: design considerations
#### 19.4.2 A confession: macros

### 19.5 Resources and exceptions
#### 19.5.1 Potential resource management problems
#### 19.5.2 Resource acquisition is initialization - RAII
#### 19.5.3 Guarantees
#### 19.5.4 `unique_ptr`
#### 19.5.5 Return by moving
#### 19.5.5 RAII for `vector`

## 20 Containers and Iterators
### 20.1 Storing and processing data
### 20.2 STL ideals
### 20.3 Sequences and iterators
### 20.4 Linked lists
### 20.5 Generalizing vector yet again
### 20.6 An example: a simple text editor
### 20.7 vector, list, and string
### 20.8 Adapting our vector to the STL
### 20.9 Adapting built-in arrays to the STL
### 20.10 Container overview

containers:

``` c++
vector
list
deque
map
multimap
unordered_map
unordered_multimap
set
multiset
unordered_set
unordered_multiset
array
```

An STL container

- is a sequence of elements `[begin():end()]`,
- provides copy operations that copy elements. copying can be done with assignment or a copy constructor,
- names its element type `value_type`,
- has iterator types called `iterator` and `const_iterator`. <br/>
iterators provides `*`, `++`, `==`, `!=` with the appropriate semantics. <br/>
the iterators for `list` also provide `--` for moving backward in the sequence (bidirection iterator)<br/>
the iterators for `vector` also provide `--`, `[]`, `+`, `-` (random-access iterators),
- provides `insert()`, `erase()`, `front()`, `back()`, `push_back()`, `pop_back()`, `size()` etc. <br/>
`vector` and `map` also provide subscripting `[]`,
- provides comparison operators `==`, `!=`, `<`, `<=`, `>`, `>=` that compare the elememnts. <br/>
containers use lexicographical ordering for `<`, `<=`, `>`, `>=`, i.e. compare the elements in order starting with the first.

"almost containers":

``` c++
T[n] // built-in array
string
valarray
```

iterator categories:

- input iterator
- output iterator
- forward iterator
- bidirectional iterator
- random-access iterator

## 21 Algorithms and Maps
### 21.1 Standard library algorithms

selected standard algorithms:

``` c++
r=find(b,e,v)
r=find_if(b,e,p)

x=count(b,e,v)
x=count_if(b,e,p)

sort(b,e)
sort(b,e,p)

copy(b,e,b2)
unique_copy(b,e,b2)

merge(b,e,b2,e2,r)

r=equal_range(b,e,v)

equal(b,e,b2)

x=accumulate(b,e,i)
x=accumulate(b,e,i,op)

x=inner_product(b,e,b2,i)
x=inner_product(b,e,b2,i,op,op2)
```


### 21.2 The simplest algorithm: `find()``
### 21.3 The general search: `find_if()``

### 21.4 Function objects
#### 21.4.1 An abstract view of function objects
#### 21.4.2 Predicates on class members
#### 21.4.3 Lambda expressions

### 21.5 Numerical algorithms
#### 21.5.1 Accumulate
#### 21.5.2 Generalizing `accumulate()`
#### 21.5.3 Inner product
#### 21.5.4 Generalizing `inner_product()`

### 21.6 Associative containers
#### 21.6.1 `map`
#### 21.6.2 `map` overview
#### 21.6.3 Another `map` example
#### 21.6.4 `unordered_map`
#### 21.6.5 `set`

### 21.7 Copying
#### 21.7.1 Copy
#### 21.7.2 Stream iterators
#### 21.7.3 Using a `set` to keep order
#### 21.7.4 `copy_if`

### 21.8 Sorting and searching
### 21.9 Container algorithms

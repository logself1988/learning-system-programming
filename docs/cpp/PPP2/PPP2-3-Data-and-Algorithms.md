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
vector(vector&&);             // move constructor
vector& operator=(vector&&);  // move assignment
```

### 18.4 Essential operations

7 essential operations:

- constructors from one or more arguments
- default constructor
- copy constructor (copy object of same type)
- copy assignment (copy object of same type)
- move constructor (move object of same type)
- move assignment (move object of same type)
- destructor

usually we use a **constructor** to establish an invariant.

we need a **default constructor** if we want to be able to make objects


### 18.5 Access to vector elements
### 18.6 Arrays
### 18.7 Examples: palindrome

## 19 Vector, Templates, and Exceptions
### 19.1 The problems
### 19.2 Changing size
### 19.3 Templates
### 19.4 Range checking and exceptions
### 19.5 Resources and exceptions

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

## 21 Algorithms and Maps
### 21.1 Standard library algorithms
### 21.2 The simplest algorithm: find()
### 21.3 The general search: find_if()
### 21.4 Function objects
### 21.5 Numerical algorithms
### 21.6 Associative containers
### 21.7 Copying
### 21.8 Sorting and searching
### 21.9 Container algorithms

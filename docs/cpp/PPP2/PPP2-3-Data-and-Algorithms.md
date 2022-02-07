# Part III Data and Algorithms

## 17 Vector and Free Store
### 17.1 Introduction
### 17.2 vector basics
### 17.3 Memory, addresses, and pointers

address: a number that indicates a location in memory.

pointer: an object that holds an address value.

- *address of* operator `&`: get the address of an object.
- *content of* / *dereference* operator `*`: get the value of the object pointed to.

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

the `new` operator: request memory to be allocated on the free store

- returns a pointer to the allocated memory,
- a pointer value is the address of the first byte of the memory,
- a pointer points to an object of a specified type,
- a poiner does not know how many elements it points to,
- can allocate individual elements or sequences (arrays) of elements.

allowing assignment of pointers to different types would allow type errors.

the subscript operator `[]`

the null pointer `nullptr`, older alternatives: `0`, `NULL`.

return memory to the free store:

- `delete p`: frees the memory for an individual object allocated by `new`,
- `delete[] p`: frees the memory for an array of objects allocated by `new`.

deleteing an object twice is a bad mistake, deleting the null pointer doesn't do anything.

### 17.5 Destructors

destructor: a function that does the opposite of a constructor

- a constructor is implicitly called when an object of a class is created,
- a destructor is implicitly called when an object goes out of scope.

destructors are called when object is destroyed: by going out of scope, by `delete`, etc.

as a rule of thumb: if you have a class with a `virtual` function, it needs a `virtual` destructor.

### 17.6 Access to elements
### 17.7 Pointers to class objects

unless you have a good strategy for deleting objects, try to keep `new`s in constructor and `delete`s in destructors.

access members:

- the dot operator `.`: given the name of an object,
- the arrow operator `->`: given a pointer to an object.

### 17.8 Messing with types: void* and casts

type `void *`: ponter to some memory that the compiler doesn't know the type of.

a pointer to any object type can be assigned to a `void *`.

explicit type convertion/cast:

- `static_cast`: explicitly convert between related pointer types, such as `void *` and `double *`.
- `reinterpret_cast`: cast between unrelated types, such as `int` and `double *`.
- `const_cast`: cast away `const`.

``` c++
void f(void* pv)
{
  int* pi = static_cast<int*>(pv);
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

how do wee choose between using a reference argument and using a pointer argument?

- for tiny objects prefer pass-by-value;
- for functions where no objects (`nullptr`) is a valid argument, use a pointer parameter;
- otherwise, use a reference parameter.

a `Circle*` can be implicitly converted to a `Shape*`, because `Shape` is a public base of `Circle`; and similarly for references.

> example: lists

a list is made out of **links** where each link holds some information and pointers to other link.


### 17.10 The `this` pointer

## 18 Vectors and Arrays
### 18.1 Introduction
### 18.2 Initialization

a `{}`-delimited list of elements of type `T` is presented to the programmer as an object of the standard library type `initializer_list<T>`, a list of `T`s.

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

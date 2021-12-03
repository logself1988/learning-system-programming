# Notes of **C++ Primer Plus**


|时间|内容|
|:---|:---|
|20190513|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1 Getting Started with C++
#### Learning C++: What Lies Before You
#### The Origins of C++: A Little History
#### Portability and Standards
#### The Mechanics of Creating a Program
#### Summary

### 2 Setting Out to C++
#### C++ Initiation
#### C++ Statements
#### More C++ Statements
#### Functions
#### Summary
#### Chapter Review
#### Programming Exercises

### 3 Dealing with Data
#### Simple Variables
#### The const Qualifier
#### Floating-Point Numbers
#### C++ Arithmetic Operators
#### Summary
#### Chapter Review
#### Programming Exercises

### 4 Compound Types
#### Introducing Arrays
#### Strings
#### Introducing the string Class
#### Introducing Structures
#### Unions
#### Enumerations
#### Pointers and the Free Store
#### Pointers, Arrays, and Pointer Arithmetic
#### Combinations of Types
#### Array Alternatives
#### Summary
#### Chapter Review
#### Programming Exercises

### 5 Loops and Relational Expressions
#### Introducing for Loops
#### The while Loop
#### The do while Loop
#### The Range-Based for Loop (C++11)
#### Loops and Text Input
#### Nested Loops and Two-Dimensional Arrays
#### Summary
#### Chapter Review
#### Programming Exercises

### 6 Branching Statements and Logical Operators
#### The if Statement
#### Logical Expressions
#### The cctype Library of Character Functions
#### The ?: Operator
#### The switch Statement
#### The break and continue Statements
#### Number-Reading Loops
#### Simple File Input/Output
#### Summary
#### Chapter Review
#### Programming Exercises

### 7 Functions: C++’s Programming Modules
#### Function Review
#### Function Arguments and Passing by Value
#### Functions and Arrays
#### Functions and Two-Dimensional Arrays
#### Functions and C-Style Strings
#### Functions and Structures
#### Functions and string Class Objects
#### Functions and array Objects
#### Recursion
#### Pointers to Functions
#### Summary
#### Chapter Review
#### Programming Exercises

### 8 Adventures in Functions
#### C++ Inline Functions
#### Reference Variables

``` c++
int rats = 101;
int & rodents = rats; // rodents a reference, make rodents an alias for rats
int * prats = &rats;  // prats a pointer
```

it is necessary to initialize the reference when you declare it: a reference is rather like a `const` pointer

``` c++
int rat;
int & rodent;
rodent = rat; // WRONG
```

pasing by references:

``` c++
void swapr(int & a, int & b) { int temp; temp = a; a = b; b = temp; }
void swapp(int *a, int * b) { int temp; temp = *p; *p = *q; *q = temp; }
void swapv(int a, int b) { int temp; temp = a; a = b; b = temp; }

int v1 = 300;
int v2 = 350;
swpar(v1, v2);    // pass variables
swapp(&v1, &v2);  // pass address of variables
swapv(v1, v2);    // pass values of variables, swap failed
```

**temporary variables**, **reference arguments**, `const`:

**lvalue**: an argument that's an lvalue is a data object that can be references by address:

- lvalues: a variable, an array element, a struct member, a reference, a dereferenced pointer
- non-lvalues: literal constants(aside from quoted strings), expression with multiple terms.

- modifiable lvalue: regular variable
- non-modifiable lvalue: `const` variable.

only if the argument is a `const` reference, C++ can generate a **temporary variable** if the actual argument does not match a reference arguments:

- when the actual argument is the correct type, but is not an lvaue;
- when the actual argument is of the wrong type, but it's of a type that can be converted to the correct type.

``` c++
double refcube(const double & ra) { return ra * ra * ra; }

double side = 3.0;
double * pd = &side;
double & rd = side;
long edge = 5L;
double lens[4] = {2.0, 5.0, 10.0, 12.0};
double c1 = refcube(side);      // ra is side
double c2 = refcube(lens[2]);   // ra is lens[2]
double c3 = refcube(rd);        // ra is rd is side
double c4 = refcube(*pd);       // ra is *pd is side
double c5 = refcube(edge);      // ra is temporary variable
double c6 = refcube(7.0);       // ra is temporary variable
double c7 = refcube(side+10.0); // ra is temporary variable
```

**rvalue references** (C++11): refer to an rvalue, declared using `&&`:

- help library designers provide more efficent implementations of certain operations,
- be used to implement move semantics.

``` c++
double && rref = std::sqrt(36.00);  // not allowed for double &
double j = 15.0;                    // not allowed for double &
double && jref = 2.0 * j + 18.5;
```

Using References with a Structure:



#### Default Arguments
#### Function Overloading
#### Function Templates
#### Summary
#### Chapter Review
#### Programming Exercises

### 9 Memory Models and Namespaces
#### Separate Compilation
#### Storage Duration, Scope, and Linkage
#### Namespaces
#### Summary
#### Chapter Review
#### Programming Exercises

### 10 Objects and Classes
#### Procedural and Object-Oriented Programming
#### Abstraction and Classes
#### Class Constructors and Destructors
#### Knowing Your Objects: The this Pointer
#### An Array of Objects
#### Class Scope
#### Abstract Data Types
#### Summary
#### Chapter Review
#### Programming Exercises

### 11 Working with Classes
#### Operator Overloading
#### Time on Our Hands: Developing an Operator
#### Overloading Example
#### Introducing Friends
#### Overloaded Operators: Member Versus Nonmember
#### Functions
#### More Overloading: A Vector Class
#### Automatic Conversions and Type Casts for Classes
#### Summary
#### Chapter Review
#### Programming Exercises

### 12 Classes and Dynamic Memory Allocation
#### Dynamic Memory and Classes
#### The New, Improved String Class
#### Things to Remember When Using new
#### in Constructors
#### Observations About Returning Objects
#### Using Pointers to Objects
#### Reviewing Techniques
#### A Queue Simulation
#### Summary
#### Chapter Review
#### Programming Exercises

### 13 Class Inheritance
#### Beginning with a Simple Base Class
#### Inheritance: An Is-a Relationship
#### Polymorphic Public Inheritance
#### Static and Dynamic Binding
#### Access Control: protected
#### Abstract Base Classes
#### Inheritance and Dynamic Memory Allocation
#### Class Design Review
#### Summary
#### Chapter Review
#### Programming Exercises

### 14 Reusing Code in C++
#### Classes with Object Members
#### Private Inheritance
#### Multiple Inheritance
#### Class Templates
#### Summary
#### Chapter Review
#### Programming Exercises

### 15 Friends, Exceptions, and More
#### Friends
#### Nested Classes
#### Exceptions

Exception Specifications Meet C++11:

``` c++
double harm(double a) throw(bad_thing); // may throw bad_thing exception
double harm(double) throw();            // does not throw an exception
double marm() noexcept;                 // does not throw an exception
```

#### Runtime Type Identification
#### Type Cast Operators
#### Summary
#### Chapter Review
#### Programming Exercises

### 16 The string Class and the Standard
#### Template Library
#### The string Class
#### Smart Pointer Template Classes
#### The Standard Template Library
#### Generic Programming
#### Function Objects (a.k.a. Functors)
#### Algorithms
#### Other Libraries
#### Summary
#### Chapter Review
#### Programming Exercises

### 17 Input, Output, and Files
#### An Overview of C++ Input and Output
#### Output with cout
#### Input with cin
#### File Input and Output
#### Incore Formatting
#### Summary
#### Chapter Review
#### Programming Exercises

### 18 Visiting with the New C++ Standard
#### C++11 Features Revisited
#### Move Semantics and the Rvalue Reference
#### New Class Features
#### Lambda Functions
#### Wrappers
#### Variadic Templates
#### More C++11 Features
#### Language Change
#### What Now?
#### Summary
#### Chapter Review
#### Programming Exercises

### Appendix A Number Bases
### Appendix B C++ Reserved Words
### Appendix C The ASCII Character Set
### Appendix D Operator Precedence
### Appendix E Other Operators
### Appendix F The string Template Class
### Appendix G The Standard Template Library Methods and
### Appendix Functions
### Appendix H Selected Readings and Internet Resources
### Appendix I Converting to ISO Standard C++
### Appendix J Answers to Chapter Reviews


## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Stephen Prata. **C++ Primer Plus**, Sixth Edition. Pearson Education: 2012.

## 其他备注

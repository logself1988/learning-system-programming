# Part I The Basics

## 2 Hello, World!
### 2.1 Programs
### 2.2 The classic first program
### 2.3 Compilation
### 2.4 Linking
### 2.5 Programming environments

``` c++
// std_lib_facilities.h
// https://www.stroustrup.com/programming.html

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;
inline void keep_window_open() { char ch; cin>>ch; }
```

## 3 Objects, Types, and Values
### 3.1 Input
### 3.2 Variables

- objects: the places in which we store data are called **objects**;
- name: to access an object we need a **name**;
- variable: a named object is called a **variable** and has a specific **type**,
- type: that determines what can be put into the object and which operations can be applied;
- value: that data items we put into variables are called **values**;
- definition: a statement that defines a variable is called a **definition**, and a definition can provide an initial value.


### 3.3 Input and type

输入操作`>>`和输出操作`<<`是类型敏感的:

- 通常读取字符串以whitespace终止;
- 其他情况忽略whitespace.

### 3.4 Operations and operators

operators for some common and useful types:

|Operator               |`bool`   |`char`   |`int`    |`double` |`string` |
|:---                   |:---     |:---     |:---     |:---     |:---     |
|assignment             |`=`      |`=`      |`=`      |`=`      |`=`      |
|addition               |         |         |`+`      |`+`      |         |
|concatenation          |         |         |         |         |`+`      |
|subtraction            |         |         |`-`      |`-`      |         |
|multiplication         |         |         |`*`      |`*`      |         |
|division               |         |         |`/`      |`/`      |         |
|remainder              |         |         |`%`      |         |         |
|increment by 1         |         |         |`++`     |`++`     |         |
|decrement by 1         |         |         |`--`     |`--`     |         |
|increment by n         |         |         |`+= n`   |`+= n`   |         |
|add to end             |         |         |         |         |`+=`     |
|decrement by n         |         |         |`-= n`   |`-= n`   |         |
|multiply and assign    |         |         |`*=`     |`*=`     |         |
|divide and assign      |         |         |`/=`     |`/=`     |         |
|remainder and assign   |         |         |`%=`     |         |         |
|read from s into x     |`s >> x` |`s >> x` |`s >> x` |`s >> x` |`s >> x` |
|write x to s           |`s << x` |`s << x` |`s << x` |`s << x` |`s << x` |
|equals                 |`==`     |`==`     |`==`     |`==`     |`==`     |
|not equal              |`!=`     |`!=`     |`!=`     |`!=`     |`!=`     |
|greater than           |`>`      |`>`      |`>`      |`>`      |`>`      |
|greater than or equal  |`>=`     |`>=`     |`>=`     |`>=`     |`>=`     |
|less than              |`<`      |`<`      |`<`      |`<`      |`<`      |
|less than or equal     |`<=`     |`<=`     |`<=`     |`<=`     |`<=`     |


### 3.5 Assignment and initialization
### 3.6 Composite assignment operators
### 3.7 Names

names are case sensitive.

The C++ language reserves about 85 names as **keywords**, we cannot use those to name variables, types, functions, etc.

### 3.8 Types and objects

- a **type** defines a set of possible values and a set of operations (for an object);
- an **object** is some memory that holds a value of a given type;
- a **value** is a set of bits in memory interpreted according to a type;
- a **variable** is a named object;
- a **declaration** is a statement that gives a name to an object;
- a **definition** is a declaration that sets aside memory for an object.

### 3.9 Type safety

a program - or a part of a program - is **type-safe** when objects are used only according to the rules for their type.

these conversions are **safe**:

- `bool` to `char`
- `bool` to `int`
- `bool` to `double`
- `char` to `int`
- `char` to `double`
- `int` to `double`

C++ allows for implicit **unsafe** conversions: a value can be implicitly turned into a value of another type that does not equal the original value. such conversion are also called **narrowing** conversions.

these conversions are accepted by the compiler even though they are unsafe:

- `double` to `int`
- `double` to `char`
- `double` to `bool`
- `int` to `char`
- `int` to `bool`
- `char` to `bool`

C++11 introduced an initialization notation that outlaws narrowing conversions:

``` c++
double x {2.7}; // OK
int y {x};      // error
```


## 4 Computation
### 4.1 Computation
### 4.2 Objectives and tools
### 4.3 Expressions

symbolic constant: a named object to which you cannot give a new value after it has been initialized.

``` c++
constexpr double pi = 3.14159;
```

constant expression: an expression with an integer value composed exclusively of constants.

``` c++
constexpr int max = 17;
```

`const` variables: the value of a variable that is initialized with a value that is not known at compile time, but never changes after initialization.

a list of the most common operators:

|Operator     |Name                     |Comment                                      |
|:---         |:---                     |:---                                         |
|`f(a)`       |function call            |pass `a` to `f` as an argument               |
|`++lval`     |pre-increment            |increment and use the incremented value      |
|`--lval`     |pre-decrement            |decrement and use the decremented value      |
|`!a`         |not                      |result is `bool`                             |
|`-a`         |unary minus              |                                             |
|`a * b`      |multiply                 |                                             |
|`a / b`      |divide                   |                                             |
|`a % b`      |remainder                |only for integer types                       |
|`a + b`      |add                      |                                             |
|`a - b`      |subtract                 |                                             |
|`out << b`   |write `b` to `out`       |where `out` is an `ostream`                  |
|`in >> b`    |read from `in` into `b`  |where `in` is an `istream`                   |
|`a < b`      |less than                |result is `bool`                             |
|`a <= b`     |less than or equal       |result is `bool`                             |
|`a > b`      |greater than             |result is `bool`                             |
|`a >= b`     |greater than or equal    |result is `bool`                             |
|`a == b`     |equal                    |not to be confused with `=`                  |
|`a != b`     |not equal                |result is `bool`                             |
|`a && b`     |logical and              |result is `bool`                             |
|`a || b`     |logical or               |result is `bool`                             |
|`lval = a`   |assignment               |not to be confused with `==`                 |
|`lval *= a`  |compound assignment      |`lval = lval * a`; also for `/`,`%`,`+`,`-`  |

- `lval`: value that can appear on the left-hand side of an assignment


`type(value)`, `type{value}`: convert `value` to `type` as if we were initializing a variable of type `type` with the value `value`.

### 4.4 Statements

- expression statements
- declarations
- empty statements

selection:

- `if`-statement
- `switch`-statement

iteration:

- `while`-statement
- blocks: `{}`, compound statement
- `for`-statements


### 4.5 Functions

function definition:

```
type identifier ( parameter-list ) function-body
```

function declaration

### 4.6 vector

a `vector` is a sequence of elements that you can access by an index.

range-for-loop

``` c++
vector<int> v = {5,7,9,4,6,8};
for(int x : v)
  cout << x << '\n';
 ```


### 4.7 Language features

## 5 Errors
### 5.1 Introduction
### 5.2 Sources of errors
### 5.3 Compile-time errors

``` c++
int area(int length, int width);
```

### 5.4 Link-time errors
### 5.5 Run-time errors
### 5.6 Exceptions

``` c++
try {}
catch () {}


exception
out_of_range
runtime_error
```

### 5.7 Logic errors
### 5.8 Estimation
### 5.9 Debugging
### 5.10 Pre- and post-conditions
### 5.11 Testing

## 6 Writing a Program

In this chapter and the next, we will develop a program from a first vague idea through stages of analysis, design, implementation, testing, redesign, and re-implementation.


### 6.1 A problem

a simple calculator: "Get the computer to do ordinary arithmetic on expression we type in".

### 6.2 Thinking about the problem
### 6.3 Back to the calculator!
### 6.4 Grammars

a simple expression grammar:

```
Expression:
  Term
  Expression "+" Term     // addition
  Expression "-" Term     // subtraction

Term:
  Primary
  Term "*" Primary        // multiplication
  Term "/" Primary        // division
  Term "%" Primary        // remainder

Primary:
  Number
  "(" Expression ")"      // grouping

Number:
  floating-point-literal
```

### 6.5 Turning a grammar into code

we simply write one function for each grammar rule and use our type `Token` to represent tokens.


a slightly different grammar:

```
Expression:
  Term
  Term "+" Expression     // addition
  Term "-" Expression     // subtraction
```

### 6.6 Trying the first version
### 6.7 Trying the second version
### 6.8 Token streams
### 6.9 Program structure

## 7 Completing a Program
### 7.1 Introduction
### 7.2 Input and output
### 7.3 Error handling
### 7.4 Negative numbers

```
Primary:
  Number
  "(" Expression ")"
  "-" Primary
  "+" Primary
```

### 7.5 Remainder: %
### 7.6 Cleaning up the code
### 7.7 Recovering from errors

read input until we find a semicolon(`;`)


``` c++
// discard characters up to and including a c
void Token_stream::ignore(char c);
```

### 7.8 Variables

grammar:

```
Calculation:
  Statement
  Print
  Quit
  Calculation Statement

Statement:
  Declaration
  Expression

Declaration:
  "let" Name "=" Expression
```

`class Variable` and symbol tables

## 8 Technicalities: Functions, etc.
### 8.1 Technicalities
### 8.2 Declarations and definitions

define entities in C++:

- variables,
- constants,
- functions,
- namespaces,
- types: classes, enumerations,
- templates.

### 8.3 Header files

To ease consistency checking, we `#include` a header both in:

- source files that use its declarations, and
- source files that provide definitions for those declarations.


a header should only contain declarations that can be duplicated in several files, sunch as:

- function declarations,
- class definitions,
- definitions of numeric constants.

### 8.4 Scope

a scope is a region of program text.

kinds of scopes:

- global scope: the area of text outside any other scope,
- namespace scope: a named scope nested in the global scope or in another namespace,
- class scope: the area of text within a class,
- local scope: between `{...}` braces of a block or in a function argument list,
- statement scope: e.g. in a `for`-statement.

### 8.5 Function call and return

rule of thumb:

- use **pass-by-value** to pass very small objects,
- use **pass-by-const-reference** to pass large objects that you don't need to modify,
- return a result rather than modifying an object through a reference argument,
- use **pass-by-reference** only when you have to.


passing an argument is the initialization of the function's formal argument with the actual argument specified in the call.

### 8.6 Order of evaluation
### 8.7 Namespaces

`using` declaration: `using std::string;`

`using` directive: `using namespace std;`


## 9 Technicalities: Classes, etc.
### 9.1 User-defined types
### 9.2 Classes and members
### 9.3 Interface and implementation
### 9.4 Evolving a class
### 9.5 Enumerations

scoped enumerations: new in C++11

``` c++
enum class Month {
  jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
```

plain enumerations: implicitly export their enumerators to the scope of the enumeration, and allow implicit conversions to `int`

``` c++
enum Month {
  jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
```


### 9.6 Operator overloading

example of C++ provided operators:

``` c++
+ - * / % [] () ^ ! & < <= > >=
```

references: [C++ - C++ language - Expressions - operator overloading](https://en.cppreference.com/w/cpp/language/operators)


### 9.7 Class interfaces

general principles to design interfaces:

- keep interfaces complete,
- keep interfaces minimal,
- provide constructors,
- support copying or prohibit it,
- use types to provide good argument checking,
- identify nonmodifying member functions,
- free all resources in the destructor.

### 9.8 The Date class

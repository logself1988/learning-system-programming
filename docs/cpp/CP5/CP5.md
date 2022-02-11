# Note of **C++ Primer, 5th Edition**


|时间|内容|
|:---|:---|
|2022-02-10| kick off. |

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

#### 1 Getting Started

a bookstore keeps a file of transactions, each of which records the sale of one or more copies of a single book. eacch transaction contains 3 data elements: ISBN, the number of copies sold, the price at which each copy was sold, for example: `0-201-70353-X 4 24.99`.

##### 1.1 Writing a Simple C++ Program
###### 1.1.1 Compiling and Executing Our Program
##### 1.2 A First Look at Input/Output
##### 1.3 A Word about Comments
##### 1.4 Flow of Control
###### 1.4.1 The while Statement
###### 1.4.2 The for Statement
###### 1.4.3 Reading an Unknown Number of Inputs

``` c++
while (std::cin >> value)  {}
```

when we use an `istream` as a conditon, the effect is to test the state of the stream.

###### 1.4.4 The if Statement
##### 1.5 Introducing Classes
###### 1.5.1 The Sales_item Class
###### 1.5.2 A First Look at Member Functions
##### 1.6 The Bookstore Program

### Part I: The Basics
### Part II The C++ Library  
### Part III Tools for Class Authors
### Part IV Advanced Topics

### Appendix A The Library
#### A.1 Library Names and Headers

#### A.2 A Brief Tour of the Algorithms
##### A.2.1 Algorithms to Find an Object
##### A.2.2 Other Read-Only Algorithms
##### A.2.3 Binary Search Algorithms
##### A.2.4 Algorithms That Write Container Elements
##### A.2.5 Partitioning and Sorting Algorithms
##### A.2.6 General Reordering Operations
##### A.2.7 Permutation Algorithms
##### A.2.8 Set Algorithms for Sorted Sequences
##### A.2.9 Minimum and Maximum Values
##### A.2.10 Numeric Algorithms

#### A.3 Random Numbers
##### A.3.1 Random Number Distributions
##### A.3.2 Random Number Engines

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

### New Features in C++11

- `long long` Type: 2.1.1
- List Intialization: 2.2.1
- `nullptr` Literal: 2.3.2
- `constexpr` Variables: 2.4.4
- Type Alias Declarations: 2.5.1
- The `auto` Type Specifier: 2.5.2
- The `decltype` Type Specifier: 2.5.3
- In-Class Initializers: 2.6.1

- Using `auto` or `decltype` for Type Abbreviation: 3.2.2
- Range `for` Statement: 3.2.3, 5.4.3
- Defining a `vector` of `vector`s: 3.3
- List Initialization for `vector`s: 3.3.1
- Container `cbegin` and `cend` Functions: 3.4.1
- Library `begin` and `end` Functions: 3.5.3
- Using `auto` or `decltype` to Simplify Declarations: 3.6

- Rounding Rules for Division: 4.2
- Assignment from a Braced List of Values: 4.4
- `sizeof` Applied to a Class Member: 4.9

- Library `initializer_list` Class: 6.2.6
- List Initializing a Return Value: 6.3.2
- Declaring a Trailing Return Type: 6.3.3
- Using `decltype` to Simplify Return Type Declarations: 6.3.3
- `constexpr` Functions

- Using `= default` to Generate a Default Constructor: 7.1.4
- In-class Initializers for Members of Class Type: 7.3.1
- Delegating Constructors: 7.5.2
- `constexpr` Constructors: 7.5.6

- Using `string`s for File Names: 8.2.1

- The `array` and `forward_list` Containers: 9.1
- Container `cbegin` and `cend` Functions: 9.2.3
- List Initialization for Containers: 9.2.4
- Container Nonmember `swap` Functions: 9.2.5
- Return Type for Container `insert` Members: 9.3.1
- Container `emplace` Members: 9.3.1
- `shrink_to_fit`: 9.4
- Numeric Conversion Functions for `string`s: 9.5.5

- Lambda Expressions: 10.3.2
- Trailing Return Type in Lambda Expressions: 10.3.3
- The Library `bind` Function: 10.3.4

- List Initialization of an Associative Container: 11.2.1
- List Initializing `pair` Return Type: 11.2.3
- List Initialization of a `pair`: 11.3.2
- The Unordered Containers: 11.4

- Smart Poiners: 12.1
- The `shared_ptr` Class: 12.1.1
- List Initialization of Dynamically Allocated Objects: 12.1.2
- `auto` and Dynamic Allocation: 12.1.2
- The `unique_prt` Class: 12.1.5
- The `weak_ptr` Class: 12.1.6
- Range `for` Doesn't Apply to Dynamically Allocated Arrays: 12.2.1
- List Initialization of Dynamically Allocated Arrays: 12.2.1
- `allocator::construct` Can Use any Constructor: 12.2.2

- Using `= default` for Copy-Control Members: 13.1.5
- Using `= delete` to Prevent Copying Class Objects: 13.1.6
- Moving Instead of Copying Class Objects: 13.5
- Rvalue References: 13.6.1
- The Library `move` Function: 13.6.1
- Move Constructor and Move Assignment: 13.6.2
- Move Constructors Usually Should Be `noexcept`: 13.6.2
- Move Iterators: 13.6.2
- Reference Qualified Member Functions: 13.6.3

- The `function` Class Template: 14.8.3
- `explicit` Conversion Operators: 14.9.1

- `override` Specifier for Virtual Functions: 15.2.2
- Preventing Inheritance by Defining a Class as `final`: 15.2.2
- `override` and `final` Specifiers for Virtual Functions: 15.3
- Deleted Copy Control and Inheritance: 15.7.2
- Inherited Constructors: 15.7.4

- Declaring a Template Type Parameter as a Friend: 16.1.2
- Template Type Aliases: 16.1.2
- Default Template Arguments for Template Functions: 16.1.3
- Explicit Control of Instantiation: 16.1.5
- Template Functions and Trailing Return Types: 16.2.3
- Reference Collapsing Rules: 16.2.5
- `static_cast` from an Lvalue to an Rvalue: 16.2.6
- The Library `forward` Function: 16.2.7
- Variadic Templates: 16.4
- The `sizeof...` Operator: 16.4
- Variadic Templates and Forwarding: 16.4.3

- The Library `Tuple` Class Template: 17.1
- New `bitset` Operations: 17.2.2
- The Regular Expression Library: 17.3
- The Random Number Library: 17.4
- Floating-Point Format Control: 17.5.1

- The `noexcept` Exception Specifier: 18.1.4
- The `noexcept` Operator: 18.1.4
- Inline Namespaces: 18.2.1
- Inherited Constructors and Multiple Inheritance: 18.3.1

- Scoped `enum`s: 19.3
- Specifying The Type Used to Hold an `enum`: 19.3
- Forward Declarations for `enum`s: 19.3
- The Library `mem_fn` Class Template: 19.4.3
- Union Members of Class Types: 19.6

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

## 其他备注

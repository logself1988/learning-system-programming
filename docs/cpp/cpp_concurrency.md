# Notes of **C++ Concurrency in Action**


|时间|内容|
|:---|:---|
|20211130|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1 Hello, world of concurrency in C++!
#### 1.1 What is concurrency?
#### 1.2 Why use concurrency?
#### 1.3 Concurrency and multithreading in C++

- C++11 Thread Library;
- C++14: a new mutex type for protecting shared data;
- C++17: a full suite of parallel algorithms for starters.

platform-specfic facilities: `native_handle()`.

#### 1.4 Getting started

``` c++
#include <thread>
std::thread
```

### 2 Managing threads
#### 2.1 Basic thread management

``` c++
# include <thread>

std::thread t;
t.join();
t.joinable();
t.detach();
```

#### 2.2 Passing arguments to a thread function

pass arguments to the `std::thread` constructor:

- the arguments are copied into **internal storage**, where they can be accessed by the noewly created thread of execution,
- then they are passed to the callable object or functions as **rvalues** as if they were temporaries.

cannot pass an **rvalue** to a function that expected a non-`const` reference.

#### 2.3 Transferring ownership of a thread

`std::thread` are **moveable** but not copyable:

- ownership can be transferred out of a function,
- ownership can be transferred into a function: accept `std::thread` instance by value.

#### 2.4 Choosing the number of threads at runtime

`std::thread::hardware_concurrency()`: indication of the number of threads that can truly run concurrency for a given execution of a program.

#### 2.5 Identifying threads

`std::thread::id`: thread identifier

- `std::thread::get_id()`
- `std::this_thread::get_id()`

### 3 Sharing data between threads
#### 3.1 Problems with sharing data between threads

Example: a doubliy linked list, remove a node from list

- identify the node to delete: N
- update the link from the node prior to N to point to the node after N,
- update the link from the node after N to point to the node prior to N,
- delete node N.

#### 3.2 Protecting shared data with mutexes

`std::mutex`

`std::lock_guard`: implements RAII idiom for a mutex.

`std::scoped_lock`: C++17

DON'T pass pointer and references to protected data outside the scope of the lock:

- whether by returning them from a function,
- storing them in externally visible memory, or
- passing them as arguments to user-supplied functions.


#### 3.3 Alternative facilities for protecting shared data
### 4 Synchronizing concurrent operations
#### 4.1 Waiting for an event or other condition
#### 4.2 Waiting for one-off events with futures
#### 4.3 Waiting with a time limit
#### 4.4 Using synchronization of operations to simplify code
### 5 The C++ memory model and operations on atomic types
#### 5.1 Memory model basics
#### 5.2 Atomic operations and types in C++
#### 5.3 Synchronizing operations and enforcing ordering
### 6 Designing lock-based concurrent data structures
#### 6.1 What does it mean to design for concurrency?
#### 6.2 Lock-based concurrent data structures
#### 6.3 Designing more complex lock-based data structures
### 7 Designing lock-free concurrent data structures
#### 7.1 Definitions and consequences
#### 7.2 Examples of lock-free data structures
#### 7.3 Guidelines for writing lock-free data structures
### 8 Designing concurrent code
#### 8.1 Techniques for dividing work between threads
#### 8.2 Factors affecting the performance of concurrent
#### 8.3 Designing data structures for multithreaded
#### 8.4 Additional considerations when designing for
#### 8.5 Designing concurrent code in practice
### 9 Advanced thread management
#### 9.1 Thread pools
#### 9.2 Interrupting threads
### 10 Parallel algorithms
#### 10.1 Parallelizing the standard library algorithms
#### 10.2 Execution policies
#### 10.3 The parallel algorithms from the C++ Standard
### 11 Testing and debugging multithreaded applications
#### 11.1 Types of concurrency-related bugs
#### 11.2 Techniques for locating concurrency-related bugs
### appendix A Brief reference for some C++11 language features
### appendix B Brief comparison of concurrency libraries
### appendix C A message-passing framework and complete ATM example
### appendix D C++ Thread Library reference


## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Anthony Williams. **C++ Concurrency in Action**, Second Edition. Manning Publications, 2019.

## 其他备注

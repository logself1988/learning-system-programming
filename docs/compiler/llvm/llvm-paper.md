# Notes of **LLVM: A Compilation Framework for Lifelong Program Analysis & Transformation**

|时间|内容|
|:---|:---|
|20210818||

<!--
Purugganan M, Hewitt J. How to read a scientific article[J]. Rice University, 2004.

IMRD structure: Introduction, Methods, Results, and Discussion.

Before and during your reading, ask yourself these questions:
• Who are these authors? What journal is this? Might I question the credibility of the work?
• Have I taken the time to understand all the terminology?
• Have I gone back to read an article or review that would help me understand this work better?
• Am I spending too much time reading the less important parts of this article?
• Is there someone I can talk to about confusing parts of this article?

After reading, ask yourself these questions:
• What specific problem does this research address? Why is it important?
• Is the method used a good one? The best one?
• What are the specific findings? Am I able to summarize them in one or two sentences?
• Are the findings supported by persuasive evidence?
• Is there an alternative interpretation of the data that the author did not address?
• How are the findings unique/new/unusual or supportive of other work in the field?
• How do these results relate to the work I’m interested in? To other work I’ve read about?
• What are some of the specific applications of the ideas presented here? What are some further experiments that would answer remaining questions?
 -->


## 引用

<!--
Author(s), Date of publication, Title (book or article), Journal,Volume #, Issue #, pages:
If web access: url; date accessed
-->

```
@InProceedings{LLVM:CGO04,
    author    = {Chris Lattner and Vikram Adve},
    title     = "{LLVM: A Compilation Framework for Lifelong Program Analysis \& Transformation}",
    booktitle = "{Proceedings of the 2004 International Symposium on Code Generation and Optimization (CGO'04)}",
    address   = {Palo Alto, California},
    month     = {Mar},
    year      = {2004}
  }
```

## 关键字

## 主题

<!-- General subject, Specific subject -->

## 假设

## 方法论

## 结果

## 关键点总结

<!--
Document level
• Title
• Abstract
• Keywords
• visuals (especially figure and table titles)
• first sentence or the last 1-2 sentences of the Introduction

Paragraph level: words or phrases to look for
• surprising
• unexpected
• in contrast with previous work
• has seldom been addressed
• we hypothesize that
• we propose
• we introduce
• we develop
• the data suggest
-->

### 文章结构

```
ABSTRACT
1. INTRODUCTION

2. PROGRAM REPRESENTATION
2.1 Overview of the LLVM Instruction Set
2.2 Language-independent Type Information, Cast, and GetElementPtr
2.3 Explicit Memory Allocation and Unified Memory Model
2.4 Function Calls and Exception Handling
2.5 Plain-text, Binary, and In-memory Representations

3. COMPILER ARCHITECTURE
3.1 High-Level Design of the LLVM Compiler Framework
3.2 Compile-Time: External front-end & static optimizer
3.3 Linker & Interprocedural Optimizer
3.4 Offline or JIT Native Code Generation
3.5 Runtime Path Profiling & Reoptimization
3.6 Offline Reoptimization with End-user Profile Information

4. APPLICATIONS AND EXPERIENCES
4.1 Representation Issues
4.1.1 What value does type information provide?
4.1.2 How do high-level features map onto LLVM?
4.1.3 How compact is the LLVM representation?
4.1.4 How fast is LLVM?
4.2 Applications using lifetime analysis and optimization capabilities of LLVM
4.2.1 Projects using LLVM as a general compiler infrastructure
4.2.2 SAFECode: A safe low-level representation and execution environment
4.2.3 External ISA design for Virtual Instruction Set Computers

5. RELATED WORK
6. CONCLUSION
7. REFERENCES
```

### 术语

### 摘要

|Title: [Enter the title of the class]||
|:---|:---|
|Topic: [Type the main topic.]||
|Questions|Comments|
|[Identify main questions.]|[Include accompanying notes.]|
|||
|Subtopic #1: [Type the name of the subtopic.]||
|Questions|Comments|
|||
|Subtopic #2: [Type the name of the subtopic.]||
|Questions|Comments|
|||
Subtopic #3: [Type the name of the subtopic.]
|Questions|Comments|
|||
|Subtopic #4: [Type the name of the subtopic.]||
|Questions|Comments|
|||
|Summary||
|[Summarize all of the contents presented in the lesson.]||

## 上下文

<!-- how this article relates to other work in the field; how it ties in with key issues and findings by others, including yourself -->

## 意义

<!-- Significance to the field; in relation to your own work -->

## 重要的图表

<!-- brief description; page number -->

### Figure 4: LLVM system architecture diagram

(1) 静态编译器前端生成LLVM表示的代码;
(2) LLVM链接器组合上一步生成的LLVM代码, 执行链接时优化(过程间优化等);
(3) 链接时或安装时, 上一步生成的LLVM代码翻译成特定目标的本地代码, 本地代码与LLVM代码一并保存(也可以在运行时使用JIT翻译器翻译LLVM代码);
(4) 本地代码生成器插入轻量级的监控和调试信息(instrumentation), 以检测经常执行的代码区域;
(5) 终端用户运行时收集的剖析数据(profile data), 可被离线优化器用于执行激进的剖析驱动的优化.

提供的能力:

(1) 持久化程序信息: persistent program information;
(2) 离线代码生成: offline code generation;
(3) 基于用户的剖析和优化: user-based profiling and optimization;
(4) 透明的运行时模型: transparent runtime model;
(5) 一致的完整程序编译: uniform, whole-program compilation.

## 引用的重要文献

<!-- cite those obviously related to your topic AND any papers frequently cited by others because those works may well prove to be essential as you develop your own work -->

## 其他备注
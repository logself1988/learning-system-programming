# Notes of **An Introduction to Assembly Programming with RISC-V**


| 时间       | 内容                                                                   |
| :--------- | :--------------------------------------------------------------------- |
| 2022-06-19 | skimming **I Introduction to computer systems and assembly language**. |
| 2022-06-22 | skimming **II User-level programming**. |
| 2022-06-23 | skip **III System-level programming**. |

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

The content is divided into 3 parts:

1. 计算机系统和汇编语言的介绍.
2. 用户级汇编编程.
3. 系统级汇编编程.

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

As a step by step learning procedure for assembly programming with RISC-V.

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

## I Introduction to computer systems and assembly language

--8<--
assembly/introduction-with-risc-v/I
--8<--

## II User-level programming 

--8<--
assembly/introduction-with-risc-v/II
--8<--

## III System-level programming 

<!--
--8<--
assembly/introduction-with-risc-v/III
--8<--
-->

## A RV32IM ISA reference card 

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

1. 介绍了计算机系统和汇编语言的基础性知识点.
2. 清晰的阐述了RV32I ISA(寄存器、逻辑/移动/算术指令、数据移动指令、控制流指令、条件设置指令)、实现常见"C"语言构造的方法(条件语句、循环语句、过程调用), 以及实现例程时所要遵循的ABI约定.
3. 简单介绍了系统级编程的场景: 访问外部设备、中断、软件中断和异常.
4. 提供了丰富的示例, 便于理解.

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

在阅读RISC-V unprivileged specifications和The RISC-V Reader, 甚至整理了RISC-V Cheatsheet之后, 仍没有如何动手编写代码的可操作性知识, 这本小书提供了编写RISC-V代码的具体示例.

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Edson Borin. **An Introduction to Assembly Programming with RISC-V**. 2022.

## 其他备注

需要学习汇编语言编程的思想? 参考 Randall Hyde. **The Art of Assembly Language, 2nd Edition**. 2010.
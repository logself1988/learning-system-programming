# Notes of **深入分析GCC**


|时间|内容|
|:---|:---|
|20211018|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- IR: Intermediate Representation, 中间表示;
- AST: Abstract Syntax Tree, 抽象语法树;
- AST/GENERIC: 规范的AST;
- GIMPLE: 与前端语言无关的中间表示, 是一种三地址码的中间表示形式, 是McGill University MacCAT编译工程中SIMPLE中间语言的一种变化形式;
- RTL: Register Transfer Language, 寄存器传输语言; 才用了类似于LISP语言列表的形式, 描述了每个指令的语义动作;
- IR-RTL: Intermediate Representation RTL, 由GIMPLE转化而成; 内部RTL格式;
- MD-RTL: Machine Description RTL, 用于机器描述文件中; 文本RTL格式;

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. GCC概述
#### 1.1　GCC的产生与发展
#### 1.2　GCC的特点
#### 1.3　GCC代码分析

### 2. GCC源代码分析工具
#### 2.1　vim+ctags代码阅读工具
#### 2.2　GNU gdb调试工具
#### 2.3　GNU binutils工具
#### 2.4　shell工具及graphviz绘图工具
#### 2.5　GCC调试选项

### 3. GCC总体结构
#### 3.1　GCC的目录结构
#### 3.2　GCC的逻辑结构
#### 3.3　GCC源代码编译

### 4. 从源代码到AST/GENERIC
#### 4.1　抽象语法树
#### 4.2　树节点的声明
#### 4.3　树节点结构
#### 4.4　AST输出及图示
#### 4.5　AST的生成
#### 4.6　小结

### 5. 从AST/GENERIC到GIMPLE
#### 5.1　GIMPLE
#### 5.2　GIMPLE语句
#### 5.3　GIMPLE的表示与存储
#### 5.4　GIMPLE语句的操作数
#### 5.5　GIMPLE语句序列的基本操作
#### 5.6　GIMPLE的生成
#### 5.7　GIMPLE转换实例
#### 5.8　实例分析
#### 5.9　小结

### 6. GIMPLE处理及其优化
#### 6.1　GCC Pass
#### 6.2　Pass列表
#### 6.3　GIMPLE Pass实例
#### 6.4　小结

### 7. RTL
#### 7.1　RTL中的对象类型
#### 7.2　RTX_CODE
#### 7.3　RTX类型
#### 7.4　RTX输出格式
#### 7.5　RTX操作数
#### 7.6　RTX的机器模式
#### 7.7　RTX的存储
#### 7.8　RTX表达式
#### 7.9　IR-RTL
#### 7.10　小结

### 8. 机器描述文件${target}.md
#### 8.1　机器描述文件
#### 8.2　指令模板
#### 8.3　定义RTL序列
#### 8.4　指令拆分
#### 8.5　枚举器
#### 8.6　窥孔优化
#### 8.7　小结

### 9. 机器描述文件${target}.[ch]
#### 9.1　targetm
#### 9.2　编译驱动及选项
#### 9.3　存储布局
#### 9.4　寄存器使用
#### 9.5　堆栈及函数调用规范描述
#### 9.6　寻址方式
#### 9.7　汇编代码分区
#### 9.8　定义输出的汇编语言
#### 9.9　机器描述信息的提取
#### 9.10　小结

### 10. 从GIMPLE到RTL
#### 10.1　GIMPLE序列
#### 10.2　典型数据结构
#### 10.3　RTL生成的基本过程
#### 10.4　GIMPLE语句转换成RTL
#### 10.5　小结

### 11. RTL处理及优化
#### 11.1　RTL处理过程
#### 11.2　特殊虚拟寄存器的实例化
#### 11.3　指令调度
#### 11.4　统一寄存器分配
#### 11.5　汇编代码生成
#### 11.6　小结

### 12. 支持新的目标处理器
#### 12.1　GCC移植
#### 12.2　PAAG处理器
#### 12.3　GCC移植的基本步骤
#### 12.4　PAAG机器描述文件(paag.md)
#### 12.5　paag.[ch]文件
#### 12.6　PAAG后端注册
#### 12.7　GCC移植测试
#### 12.8　小结

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

### 编译

version: 9.3.0

1. 下载依赖

``` shell
./contrib/download_prerequisites

tar jxvf gmp-6.1.0.tar.bz2
cd gmp-6.1.0
./configure --prefix=/usr/local/gmp
make && sudo make install
cd ..

tar jxvf mpfr-3.1.4.tar.bz2
cd mpfr-3.1.4
./configure --prefix=/usr/local/mpfr --with-gmp=/usr/local/gmp
make -j2 && sudo make install
cd ..

tar zxvf mpc-1.0.3.tar.gz
cd mpc-1.0.3
./configure --prefix=/usr/local/mpc --with-gmp=/usr/local/gmp --with-mpfr=/usr/local/mpfr
make -j2 && sudo make install
cd ..

tar jxvf isl-0.18.tar.bz2
cd isl-0.18
./configure --prefix=/usr/local/isl --with-gmp-prefix=/usr/local/gmp
make -j2 && sudo make install
cd ..
```

2. 编译和安装

``` shell
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/mpc/lib:/usr/local/gmp/lib:/usr/local/mpfr/lib/:/usr/local/isl/lib

./configure CFLAGS="-w -g -O0" --prefix=/home/zhoujiagen/gnu/gcc-9.3.0/bin --with-gmp=/usr/local/gmp/ --with-mpfr=/usr/local/mpfr/ --with-mpc=/usr/local/mpc/ --with-isl=/usr/local/isl --disable-multilib
make -j2
make install
```


## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- 王亚刚. **深入分析GCC**. 机械工业出版社, 2017.

## 其他备注

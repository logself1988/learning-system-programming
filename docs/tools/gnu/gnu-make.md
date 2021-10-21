# Notes of **Managing Projects with GNU Make**


|时间|内容|
|:---|:---|
|20210929|kick off.|
|20210930|Complete PART I.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- target: 目标
- prerequisite: 前提
- stem of a file: 词干, 即文件名称中后缀之前的部分, 例如`xxx.c`中的`xxx`
- RHS: righthand side, 右手侧

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### Part I. Basic Concepts
#### 1. How to Write a Simple Makefile

Makefile中规则的形式:

``` Makefile
target1 target2 target3: prerequisite1 prerequisite2
  command1
  command2
  command3
```

- 每个命令必须以TAB键作为开始.

#### 2. Rules

当请求更新target时, 如果规则的prerequisite文件的修改时间在target修改时间之后, `make`会执行规则中的命令脚本.

规则的类型:

- 显式规则(explicit rules): 常见的编写的规则;
- 模式规则(pattern rules): 使用通配符, 而不是明确的文件名;
- 隐式规则(implicit rules): 内建的规则数据中找到的模式规则或后缀规则;
- 静态模式规则: 但只应用于特定的目标文件列表的模式规则;
- 后缀规则(suffix rules): 已废弃的编写通用规则的方法.

##### 显式规则

一个规则可以有多个target:

``` Makefile
vpath.o variable.o: make.h config.h getopt.h gettext.h dep.h
```

等价于独立的两个规则:

``` Makefile
vpath.o: make.h config.h getopt.h gettext.h dep.h
variable.o: make.h config.h getopt.h gettext.h dep.h
```

一个规则不一定需要一次定义完整: 在依赖图中已存在的target, 会追加新的定义中prerequisite

``` Makefile
vpath.o: vpath.c make.h config.h getopt.h gettext.h dep.h
vpath.o: filedef.h hash.h job.h commands.h variable.h vpath.h
```

`make`的通配符(wildcard/globbing)与Bourne shell通配符等价:

```
~               # 当前用户的主目录
*               # 多个字符
?               # 单个字符
[...]           # 字符类
[^...]          # 反字符类
```

- 在target、prerequisite或命令脚本上下文中出现的通配符, 会被`make`自动展开; 出现在命令中的模式在子shell中展开;
- 而在其他上下文中, 可以通过调用函数显式展开通配符.


``` Makefile
prog: *.c
    $(CC) -o $@ $^
```

伪目标(phony target): 不表示文件的目标; 通常总是被执行(因总是out of date).

`make`无法区分伪目标与文件目标, 提供了一个特殊的目标`.PHONY`:

``` Makefile
.PHONY: clean
clean:
    rm -f *.o lexer.c
```

标准的伪目标:

- `all`: 执行构建应用的所有任务;
- `install`: 从已编译的二进制文件创建应用的安装;
- `clean`: 删除从源文件生成的二进制文件;
- `distclean`: 删除不在原始源代码发布中的生成的文件;
- `TAGS`: 创建给编辑器使用的tag表;
- `info`: 从Texinfo源文件创建GNU info文件;
- `check`: 运行应用关联的测试.

空目标(empty target): 空文件

``` Makefile
prog: size prog.o
    $(CC) $(LDFLAGS) -o $@ $^

size: prog.o
    size $^    # size命令
    touch size # 空文件size
```

##### 变量

变量引用语法:

```
$(variable-name)
${variable-name}
$single-character-variable-name
```

自动变量(automatic variables): 在规则匹配时由`make`设置, 通过它们可以访问target和prerequisite中元素.

- `$@`: 目标文件名(The filename representing the target).
- `$*`: 目标文件名的无后缀名称(The stem of the target filename. A stem is typically a filename without its suffix. Its use outside of pattern rules is discouraged).

- `$%`: 目标是归档成员时的成员名, 例目标是foo.a(bar.o), `$%`是bar.o, `$@`是foo.a; 目标不是归档成员时`$%`为空.(The filename element of an archive member specification).

- `$<`: 第一个前提文件名(The filename of the first prerequisite).
- `$?`: 比目标新的所有前提文件名(The names of all prerequisites that are newer than the target, separated by spaces).
- `$^`: 所有前提文件名(The filenames of all the prerequisites, separated by spaces. This list has duplicate filenames removed since for most uses, such as compiling, copying, etc.,duplicates are not wanted).
- `$+`: 所有前提文件名, 可能存在重复(Similar to `$^`, this is the names of all the prerequisites separated by spaces, except that `$+` includes duplicates. This variable was created for specific situations such as arguments to linkers where duplicate values have meaning).

上面的变量的两个变种:

- 返回值的目录部分, 例如: `$(@D)`, `$(<D)`;
- 返回值的文件部分, 例如: `$(@F)`, `$(<F)`.

例:

``` Makefile
word_count: word_count.o lexer.o
	gcc -o $@ $^ -lfl

word_count.o: word_count.c
	gcc -c $<

lexer.o: lexer.c
	gcc -c $<

lexer.c: lexer.l
	flex -o $@ $<
```

##### 使用`VPATH`和`vpath`查找文件

`make`默认在当前目录下查找target和prerequisite, 使用`VPATH`变量和`vpath`指令可以修改查找目录:

- `VPATH = directory-list`: 由目录列表构成;
- `vpath pattern directory-list`: 如果`VPATH`列表中有相同名称的文件, `make`使用第一个找到的文件; `vpath`指定在特定目录中查找满足特定模式的文件.

``` Makefile
VPATH = src       # 指定源文件目录

vpath %.c src     # 指定特定文件的查找目录
vpath %.l src
vpath %.h include
```

##### 模式规则

模式规则(pattern rules)与一般的规则类似, 除了文件的stem用字符`%`表示.

通过识别常见的文件名称模式, 提供內建规则来简化规则创建, 例:

``` Makefile
VPATH = src
CPPFLAGS = -I include

word_count: counter.o lexer.o -lfl
word_count.o: include/counter.h
counter.o: include/counter.h include/lexer.h
lexer.o: include/lexer.h
```

使用了内建规则:

``` Makefile
$ make --print-data-base              # 查看内建规则和变量
# ...
%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
# ...
%.c: %.l
	@$(RM) $@
	 $(LEX.l) $< > $@
# ...
%: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
```

###### 模式

字符`%`可以在模式中任意位置出现, 但只能出现一次.

例:

```
%,v
s%.o
wrapper_%
```

###### 静态模式规则

静态模式规则只能应用于特定的目标.

``` Makefile
$(OBJECTS): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

- `$(OBJECTS):`描述在`$(OBJECTS)`中的每个对象文件与模式`%.o`匹配, 提取文件stem;
- 将文件stem在`%.c`中替换来产生prerequisite.

###### 后缀规则

后缀规则(suffix rules)是最初定义隐式规则的方式, 现已废弃.

``` Makefile
.c.o:
    $(COMPILE.c) $(OUTPUT_OPTION) $<
# 等价于
%.o: %.c
    $(COMPILE.c) $(OUTPUT_OPTION) $<
```

``` Makefile
.p:
    $(LINK.p) $^ $(LOADLIBES) $(LDLIBS) -o $@
# 等价于
%: %.p
    $(LINK.p) $^ $(LOADLIBES) $(LDLIBS) -o $@
```

使用特殊的目标`.SUFFIXES`定义已知的后缀列表:

``` Makefile
.SUFFIXES: .out .a .ln .o .c .cc .C .cpp .p .f .F .r .y .l
```

##### 隐式规则数据库

- `--print-data-base`/`-p`: 查看规则数据库和变量.
- `--just-print`/`-n`: 查看构建动作.
- `--no-builtin-rules`/`-r`: 不使用内建规则.
- `--no-builtin-variables`/`-R`: 不使用内建变量.

###### 使用隐式规则

每当处理一个target时, 没有更新它的显式规则, `make`会引用內建的隐式规则.

无命令脚本的模式规则将规则从数据库中移除,

例: 有Lisp和C源文件editor.l, editor.c; 不应用使用flex

``` Makefile
%.o: %.l
%.c: %.l
```

`make`尝试更新target时使用规则链:

- 需要更新一个target时, 搜索隐式规则以找到匹配该target的target模式;
- 对每个匹配的target模式, 查找已存在的匹配prerequisite源文件;
- 如果找到prerequisite, 则使用该规则;
- 如果在所有规则中没有找到prerequisite, 则假设匹配的prerequisite源文件应该是需要更新的target, 继续搜索规则.

由规则链生成的文件称为中间文件(intermediate file):

- `make`不会简单的更新中间文件;
- `make`在退出前会删除中间文件.

例:

```
$ touch foo.y
$ make -n foo
yacc  foo.y
mv -f y.tab.c foo.c
cc    -c -o foo.o foo.c
cc   foo.o   -o foo
rm foo.c foo.o
```

###### 规则结构

内建规则有标准的结构, 便于定制. 定制是通过规则中使用的变量控制的.

例: 内建规则

``` Makefile
%.o: %.c
  $(COMPILE.c) $(OUTPUT_OPTION) $<
```

例: 定制内建规则

``` Makefile
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
CC = gcc
OUTPUT_OPTION = -o $@
```

- `CC`: 用于选择C编译器的变量;
- `CFLAGS`: 编译选项;
- `CPPFLAGS`: 预处理器选项;
- `TARGET_ARCH`: 体系结构特定选项.
- 在命令行中覆盖: `$ make CPPFLAGS=-DDEBUG`.

##### 特殊目标

特殊的目标是用于修改`make`默认行为的内建伪目标:

- `.PHONY`: 声明prerequisite不引用实际的文件, 总是out of date;
- `.SUFFIXES`: 指定后缀规则;
- `.INTERMEDIATE`: prerequisite是中间文件;
- `.SECONDARY`: prerequisite是中间文件, 但不自动删除;
- `.PRECIOUS`: 默认情况下`make`执行中断后会删除更新的target文件; 将文件标记为`.PRECIOUS`则中断时不会被删除;
- `.DELETE_ON_ERROR`: 与`.PRECIOUS`行为相反.
- `.EXPORT_ALL_VARIABLES`

##### 自动依赖生成

自动生成C中`include`预处理指令包含的依赖, 例见`codes/make/ch02/work_count_defaults`.

##### 管理库

生成库归档: `ar`

```
ar rv libcounter.a counter.o lexer.o  # 添加
ar rv libcounter.a counter.o          # 更新
```

###### 创建和更新库

例见`codes/make/ch02/work_count_lib`.

###### 使用库作为prerequisite

当库作为prerequisite出现时, 可以用标准文件名称或使用`-l`语法引用库.

``` Makefile
xpong: $(OBJECTS) /lib/X11/libX11.a /lib/X11/libXaw.a # 标准文件名称
    $(LINK) $^ -o $@
xpong: $(OBJECTS) -lX11 -lXaw                         # -l语法
    $(LINK) $^ -o $@
```

处理库中循环依赖: `-lA -lB -lA`.

###### 双冒号规则

根据不同的prerequisite使用不同的命令来更新target:

- 多个同名target的常规规则, 各prerequisite会追加在一起; 而双冒号规则不会;
- 对某一特定的target, 其规则必须是同一类型: 即都是双冒号规则, 或都是单冒号规则.

``` Makefile
file-list:: generate-list-script
  chmod +x $<
  generate-list-script $(files) > file-list

file-list:: $(files)
  generate-list-script $(files) > file-list
```

#### 3. Variables and Macros

`make`中包含两种语言:

- 通过target和prerequisite描述依赖图的语言;
- 执行文本替换的宏语言.

变量是大小写敏感的, 获取变量的值: `$()`、`$letter`、`${}`.

命名约定:

``` Makefile
# 常量: 全大写, 单词用_分隔
CC := gcc
# 内部变量: 全小写, 单词用_分隔
sources = *.c
# 函数:全小写, 单词用-分隔
maybe-make-dir = $(if $(wildcard $1),,$(MKDIR) $1)
```

##### 变量类型

- `:=`: 简单变量(简单展开的变量);
- `=`: 递归变量(递归展开的变量), `make`不会对RHS进行求值或展开, 直接将RHS存储为变量的值; 只在使用变量时展开;
- `?=`: 条件变量赋值操作符, 变量没有值时才执行赋值;
- `+=`: 追加操作符.

##### 宏

使用`define`指令定义宏, 例:

``` Makefile
define sample-macro
	@echo "I can do this"
	@echo "I can also do this"
endef

.POHNY: test
test:
	$(sample-macro)
```

##### 变量何时展开?

`make`工作机制的两个阶段:

- (1) 读取makefile和导入的makefile, 将变量和规则加载到内部数据库, 创建依赖图;
- (2) 分析依赖图, 确定需要更新的目标, 执行更新目标所需的命令脚本.

当`make`处理遇到递归变量或`define`指令时, 存储该变量内容或宏的体. 当宏展开时, 在展开的文本中扫描需要进一步处理的宏和变量引用, 并递归的展开这些宏和变量.

makefile中元素的展开规则:

- For variable assignments, the lefthand side of the assignment is always expanded immediately when `make` reads the line during its first phase.
- The righthand side of `=` and `?=` are deferred until they are used in the second phase.
- The righthand side of `:=` is expanded immediately.
- The righthand side of `+=` is expanded immediately if the lefthand side was originally defined as a simple variable. Otherwise, its evaluation is deferred.
- For macro definitions (those using `define`), the macro variable name is immediately expanded and the body of the macro is deferred until used.
- For rules, the targets and prerequisites are always immediately expanded while the commands are always deferred.

##### 特定于目标/模式的变量

``` Makefile
gui.o: gui.h
    $(COMPILE.c) -DUSE_NEW_MALLOC=1 $(OUTPUT_OPTION) $< # 使用特殊编译选项

gui.o: CPPFLAGS += -DUSE_NEW_MALLOC=1                   # 使用特定于目标的变量
gui.o: gui.h
    $(COMPILE.c) $(OUTPUT_OPTION) $<
```

目标特定变量的通用语法:

``` Makefile
target...: variable = value
target...: variable := value
target...: variable += value
target...: variable ?= value
```

#####  变量的来源

- makefile文件;
- 命令行: 例`$ make CFLAGS=-g CPPFLAGS='-DBSD -DDEBUG'`;
- 环境变量;
- 自动变量: `make`在执行规则的命令脚本之前创建自动变量.

优先级: 命令行 > makefile > 环境变量

- 命令行中变量赋值会覆盖makefile文件中变量和环境变量的赋值; 在makefile中使用`override`指令修改这一行为;
- makefile中变量赋值会覆盖环境变量的赋值, 使用`--environment-overrides`/`-e`命令行选项修改这一行为.

当递归调用`make`时, 默认情况下, 子`make`可见父`make`中的原始环境变量, 可以使用`export`和`unexport`指令控制导出的环境变量.

##### 条件化和导入处理

条件化处理指令: `ifdef`、`ifndef`、`ifeq`、`ifneq`

```
<conditional-stmt>:            
  <if-condition> text if the condition is true [endif]
  |<if-condition> text if the condition is true [else] text if the condition is false [endif]

<if-condition>:
  [ifdef] variable-name     # 变量名variable-name不能使用$()
  | [ifndef] variable-name
  | [ifeq] <test>
  | [ifneq] <test>

<test>:
  "a" "b"
  | (a,b)
```

makefile中可以使用`include`指令包含其他文件, 例:

``` Makefile
include definitions.mk
```

`make`处理`include`指令的方式:

- 遇到`include`指令时, 展开通配符和变量引用, 尝试读取被包含的文件;
- 如果文件存在, 继续常规的处理; 如果文件不存在, `make`报告问题并继续读取剩下的makefile内容;
- 当所有读取完成时, `make`在规则数据库中查找更新被包含文件的规则;
- 如果找到匹配的而规则, 则执行更新target的处理逻辑;
- 如果被包含的文件被规则更新了, `make`清空该文件的内部数据库并重新读取整个makefile;
- 如果在完成这些读取、更新、再读取操作后, 如果存在因文件缺失而失败的`include`指令, `make`以错误状态退出.

`make`将makefile文件视为target:

- 在读取完整个makefile之后, `make`会查找重新构建(remake)当前执行的makefile的规则;
- 如果找到, `make`处理该规则并检查makefile是否已更新;
- 如果已更新, `make`清除相应的内部状态并重新读取makefile, 再次执行整个分析.

`make`查找导入文件的顺序:

- 如果`include`指令是绝对文件引用, 则直接读取该文件;
- 如果是相对引用, 首先在当前工作目录中查找;
- 如果没有找到, 在`--include-dir`/`-I`命令行参数指令的目录中查找;
- 如果没有找到, 在编译搜索路径中查找.

如果`make`无法找到被包含文件且无法使用规则创建它, 则以错误状态退出. 在无法找到时忽略被包含文件:

``` Makefile
-include i-mqy-not-exist.mk
```

在makefile第一个目标之前使用`include`指令导入文件可能会修改默认目标, 解决方法:

``` Makefile
all:
include support.mk
all: $(programs)
```

##### 标准make变量

- `MAKE_VERSION`: `make`的版本号;
- `CURDIR`: 执行`make`进程的当前工作路径;
- `MAKEFILE_LIST`: `make`读取的文件列表;
- `MAKECMDGOALS`: 当前`make`执行的命令行参数中指定的目标列表;
- `.VARIABLES`: 当前读取到的变量名称列表, 不包括特定于目标的变量.

变量也用定制`make`中内建的隐式规则:

- 变量形式: `ACTION.suffix`;
- `ACTION`: `COMPILE`、`LINK`、`PREPROCESS`、`YACC`、`LEX`;
- `suffix`: `C`、`cc`、`c`、`y`、`l`等;
- `CC`: 指定C编译器, 默认为`gcc`;
- `CXX`: 指定C++编译器, 默认为`g++`;
- `CXXFLAGS`: C++编译器标志;
- `CPPFLAGS`: C预处理器标志;
- `TARGET_ARCH`: 体系结构特定编译选项;
- `OUTPUT_OPTION`: 输出文件选项;
- `LD`: 指定连接器;
- `LDFLAGS`: 连接器选项;
- `LOADLIBES`、`LDLIBS`: 指定链接时使用的库.


#### 4. Functions

函数调用与变量引用类似, 但包含由逗号`,`分隔的参数.

##### 用户自定义函数

用户自定义函数存储为变量或宏, 预期一个或多个参数.

展开变量或宏的语法:

``` Makefile
$(call macro-name[, param1...])
```

- `call`: 内建函数;
- 展开第一个参数`macro-name`, 并使用剩余的参数依次替换其中`$1`、`$2`等.

##### 内建函数

内建函数的形式:

``` Makefile
$(function-name arg1[, argn])
```

部分内建函数接收模式参数`pattern`, 使用与模式规则中相同的模式语法.

- 字符串函数

``` Makefile
$(filter pattern...,text)
$(filter-out pattern...,text)
$(findstring string,text)
$(subst search-string,replace-string,text)
$(patsubst search-pattern,replace-pattern,text)
$(words text)
$(word n,text)
$(firstword text)
$(wordlist start,end,text)
```

- 杂项函数

``` Makefile
$(sort list)
$(shell command)
$(strip text)
$(origin variable)
$(warning text)
```

- 文件名函数

``` Makefile
$(wildcard pattern...)
$(dir list...)
$(notdir name...)
$(suffix name...)
$(basename name...)
$(addsuffix suffix,name...)
$(addprefix prefix,name...)
$(join prefix-list,suffix-list)
```

- 流程控制函数

``` Makefile
$(if condition,then-part,else-part)
$(error text)
$(foreach variable,list,body)
```

##### 高级的用户自定义函数

`eval`函数: 将文本直接传给`make`解析器.

钩子函数(hooking function): 用户可以自定义的钩子函数.

传递参数: 函数中数据来源可以是通过`call`传递的参数、全局变量、自动变量和目标特定的变量.

#### 5. Commands

命令本质上是单行shell脚本, `make`逐行将命令放在子shell中执行. `SHELL`变量控制使用的shell, 默认为`/bin/sh`.

##### 解析命令

在target之后, 以TAB字符开始的行被认为是命令(除了上一行以`\`结尾). 当解析器遇到合法上下文中的命令, 则切换到命令解析模式.


命令的修饰符(command modifier):

- 前缀`@`: 不输出该命令; 特殊目标`.SILENT`和命令行选项`--silent`/`-s`;
- 前缀`-`: 指定命令中的错误应该被忽略; 特殊目标`.IGNORE`和命令行选项`--ignore-errors`/`-i`;
- 前缀`+`: 指定必须执行命令, 甚至使用了命令行选项`--just-print`/`-n`时也需要执行.

`make`执行的每个命令均返回状态码, 0表示命令执行成功.

##### 空命令

例:

``` Makefile
header.h: ;
```

##### 命令环境

`make`执行的命令会继承`make`进程的环境, 同时命令执行所处的子shell中会有新的变量:

- `MAKEFLAGS`: 传递给`make`的命令行选项;
- `MFLAGE`: 同`MAKEFLAGS`;
- `MAKELEVEL`: 嵌套`make`调用的层级;
- 通过`export`指令添加的变量.

###### 求值命令

命令脚本处理顺序: 读取代码, 展开变量, 求值`make`表达式, 执行命令.

### Part II. Advanced and Specialized Topics
#### 6. Managing Large Projects

#### 7. Portable Makefiles
#### 8. C and C++
#### 9. Java
#### 10. Improving the Performance of make
#### 11. Example Makefiles
#### 12. Debugging Makefiles

### Part III. Appendixes
#### A. Running make
#### B. The Outer Limits
#### C. GNU Free Documentation License

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Robert Mecklenburg. **Managing Projects with GNU Make, Third Edition**. O’Reilly Media, 2005. https://resources.oreilly.com/examples/9780596006105
- [What is the difference between the GNU Makefile variable assignments =, ?=, := and +=?](https://stackoverflow.com/questions/448910/what-is-the-difference-between-the-gnu-makefile-variable-assignments-a)

## 其他备注

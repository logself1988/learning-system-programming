# Notes of **Mastering CMake, pre-3.0**


|时间|内容|
|:---|:---|
|20190513|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- `CMAKE_INSTALL_DIR`: CMake安装目录
- `CMAKE_MODULE_DIR`: CMake模块默认目录 `/usr/share/cmake-3.16/Modules/`
- `CMAKE_EXAMPLE_DIR`: CMake示例目录 `codes/cmake/mastering`
- listfile: CMakeLists.txt文件

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1 WHY CMAKE?

CMake是开源的软件项目构建管理器, 允许开发者以一个简单的可移植的文本文件的形式指定构建参数.

CMake使用该文件为本地构建工具生成项目文件, 包括IDE Microsoft Visual Studio、Apple XCode、UNIX/Linux/NMake/Borland风格的Makefiles等.

#### 1.1 The History of CMake
#### 1.2 Why Not Use Autoconf?
#### 1.3 Why Not Use JAM, qmake, SCons, or ANT?
#### 1.4 Why Not Script It Yourself?
#### 1.5 On What Platforms Does CMake Run?

### 2 GETTING STARTED
#### 2.1 Getting and Installing CMake an Your Computer
#### 2.2 Building CMake Yourself
#### 2.3 Basic CMake Usage and Syntax

项目的构建构过程由一个或多个CMakeList.txt文件控制. 该文件用CMake的简单语言编写项目描述. 这个语言由一组命令构成.

命令的形式:

``` cmake
command (args...)
```

- `command`: 命令的名称, 从v2.2开始大小写不敏感;
- `args`: 空格分隔的参数列表.

变量:

- 支持字符串或字符串列表的简单变量, 用`${VAR}`语法引用变量;
- 用`set`命令将多个参数组装到列表中, 例: `set(Foo a b c)`;
- 使用列表变量例: `command(${Foo})`等价于`command(a b c)`, `command("${Foo}")`等价于`command("a b c")`;
- 环境变量: `$ENV{VAR}`;
- Windows注册表项: `[HKEY_CURRENT_USER\\Software\\path1\\path2;key]`.

#### 2.4 Hello World for CMake


``` cmake
# cmake_minimum_required(2.6)
project (HELLO)

set (HELLO_SRCS Hello.c File2.c File3.c)

if (WIN32)
  set (HELLO_SRCS ${HELLO_SRCS} WinSupport.c)
else ()
  set (HELLO_SRCS ${HELLO_SRCS} UnixSupport.c)
endif ()

# build the executable
add_executable (Hello ${HELLO_SRCS})

# look for the Tcl library
find_library (TCL_LIBRARY
  NAMES tcl tcl84 tcl83 tcl82 tcl80
  PATHS /usr/lib /usr/local/lib
  )

if (TCL_LIBRARY)
  # add link for executable target
  target_link_library (Hello ${TCL_LIBRARY})
endif ()
```

#### 2.5 How to Run CMake?

- CMake's Qt interface: cmake-gui
- ccmake Curses Interface
- cmake in command line

指定编译器:

- 对基于Makefile的生成器, CMake尝试在这些文件中找到可以工作的编译器:

```
// CMAKE_INSTALL_DIR/share/cmake-3.16/Modules目录下
CMakeDetermineCCompiler.cmake
CMakeDetermineCXXCompiler.cmake
```

- 使用环境变量: `CC`、`CXX`, 这会覆盖上一行为;
- 在命令行中指定, 例`-DCMAKE_CXX_COMPILER=g++`;
- 如果上述方法均未指定, 则尝试使用这些编译器:

```
c++ g++ CC aCC c1 bcc x1C
```

- 一旦CMake开始运行且挑选了一个编译器, 可以通过修改缓存项`CMAKE_CXX_COMPILER`、`CMKAE_C_COMPILER`改变选择.


修改编译器和链接器标志(flag):

- `CXXFLAGS`、`CFLAGS`: 分别初始化编译器标志缓存值`CMAKE_CXX_FLAGS`、`CMAKE_CXX_FLAGS`;
- `LDFLAGS`: 初始化链接标志缓存值.

依赖分析(dependency analysis), 项目中目标的信息依赖文件: depend.make、flags.make、build.make、DependInfo.cmake. ???


#### 2.6 Editing CMakeLists Files
#### 2.7 Setting Initial Values for CMake

- 在CMake命令行中使用`-DCACHE_VAR:TYPE=VALUE`
- 使用CMake的`-C`选项加载文件, 文件由一组`set`命令构成.

#### 2.8 Building Your Project

- 目标生成器是基于Makefile的: 使用make;
- 为IDE生成目标文件: 使用IDE加载项目文件, 手动构建;
- 使用CMake的`--build`选项:

```
cmake --build <your binary dir>
```

### 3 KEY CONCEPTS
#### 3.1 Main Structures

CMake内部中类之间的基本关系:

- source files: C或C++源代码文件;
- target: 源代码文件组合为目标, 目标通常是执行体(executable)或库(library);
- directory: 目录表示源码树中的一个目录, 通常有一个CMakeLists文件, 其中有一个或多个目标;
- local generator: 每个目录有一个本地生成器, 负责为该目录生成Makefile或项目文件;
- global generator: 所有本地生成器共享一个能观察到整个构建过程的全局生成器, 由`cmake`驱动.

```
// CMake Internals

cmake -has-one-> cmGlobalGenerator -has-many-> cmLocalGenerator -has-one-> cmMakefile
cmCommand
```

#### 3.2 Targets

创建目标:

- `add_library`: 库;
- `add_executable`: 执行体;
- `add_custom_target`: 自定义目标.

``` cmake
add_library (foo STATIC foo1.c foo2.c)
```

库的类型:

- `STATIC`: 静态库;
- `SHARED`: 共享库;
- `MODULE`: 可被动态加载到执行体中;
- 未指定时, 使用`BUILD_SHARED_LIBS`变量确定是`STATIC`还是`SHARED`; 如果该变量未设置, 则为`STATIC`.

设置和获取目标的属性(properties)的命令:

- `set_target_properties`, `get_target_property`
- `set_property`, `get_property`

目标的链接属性:

- `LINK_FLAGS`: 指定目标链接标志的属性;
- `target_link_libraries`: 设置链接的库的命令.

#### 3.3 Source Files

使用`set_source_files_properties`、`get_source_files_property`来设置、获取源文件结构属性.

一些属性:

- `COMPILE_FLAGS`
- `GENERATED`
- `OBJECT_DEPENDES`
- `ABSTRACT`, `WRAP_EXCLUDE`

#### 3.4 Directories, Generators, Tests, and Properties

在这些类结构上都可以使用设置和获取属性: `set_property`、`get_property`.

使用`cmake --help-property-list`查询完整属性列表.

#### 3.5 Variables and Cache Entries

CMake中变量可以表示单个值或一个列表, 例:

- `"ON"`、`"OFF"`;
- `(/usr/include /home/foo/include /usr/local/include)`.

变量通过`${VARIABLE}`引用, 按`set`命令执行的顺序定义. 变量表示列表时, 展开为多值(multiple values):

``` cmake
set (items_to_buy apple orange pear beer)

foreach (item ${items_to_buy})
  message ( "Don't forget to buy one ${item}")
endforeach ()
```

变量的作用域:

- 设置变量时, 该变量对当前CMakeLists文件或当前函数可见, 对子目录中的CMakeLists文件可见, 对被调用的函数和宏可见, 对使用`INCLUDE`命令包含入的文件可见.
- 当处理新的子目录或调用函数时, 会创建新的变量作用域, 并用调用作用域中所有变量的当前值初始化;
- 在子作用域中创建的任何新变量, 或者对已存在变量的修改, 不会影响父作用域;
- 使用`set`命令的`PARENT_SCOPE`选项, 修改父作用域中变量的值, 例:

``` cmake
function (foo)
  message (${test})             # 1
  set (test 2 PARENT_SCOPE)
  message (${test})             # 1
endfunction ()

set (test 1)
foo()
message (${test})               # 2
```

缓存:

- 当CMake运行时, 在写入二进制文件的目录中生成一个缓存文件;
- 缓存文件中的值在CMake的用户界面中展示;
- 缓存用于存储用户的选择和选项, 用于存储计算耗时的关键变量;
- 在缓存中创建变量:

```
option (USE_JPEG "Do you want to use the jpeg library")
find_file (...)
set (USE_JPEG ON CACHE BOOL "include jpeg support?")    # 提供变量类型和文档字符串
```

变量类型有: `BOOL`、`PATH`、`FILEPATH`、`STRING`.

缓存中变量有表示是否是高级变量的属性, 使用`mark_as_advanced`命令将变量标记为高级变量.

通过设置`STRINGS`属性来限制缓存中变量的取值, 例:

``` cmake
set (CRYPTOBACKEND "OpenSSL" CACHE STRING "Select a cryptograph backend")
set_property (CACHE CRYPTOBACKEND PROPERTY STRINGS "OpenSSL" "LibTomCrypt" "LibDES")
```

变量与缓存的注意事项:

- 如果变量在缓存中, 在CMakeLists文件中使用不带`CACHE`选项的`set`命令可以覆盖该变量;
- 只有在CMakeLists文件处理开始之前, 变量在当前cmMakefile实例中未找到时, 才会去检查缓存值;
- 一旦变量在缓存中, 该变量的值通常不会在CMakeLists文件中修改, 原因是修改之后可能会覆盖用户设置的值; 使用`set`命令中的`CACHE`和`FORCE`选项可以修改缓存变量的值.

#### 3.6 Build Configurations

构建配置允许项目为调试、优化或其他特殊的标记执行不同的构建. 默认情况下, CMake支持的配置有:

- `Debug`: 开启基本的调试标志;
- `Release`: 开启基本的优化;
- `MinSizeRel`: 开启生成最小对象代码的标志;
- `RelWithDebInfo`: 开启调试和优化标志.

CMake处理构建配置的方式依赖于使用的生成器(Visual Studio项目文件、Makefiles), 并尽可能的使用本地构建系统的约定.

使用基于Makefile的生成器时, 只能有一个激活的构建配置, 用变量`CMAKE_BUILD_TYPE`指定:

- 该变量为空: 构建时不添加任何标志;
- 该变量设置为配置的名称, 构建时在编译行中添加恰当的变量和规则, 例如`CMAKE_CXX_FLAGS<ConfigName>`.

### 4 WRITING CMAKELISTS FILES

CMake是由为软件项目编写的CMakeLists.txt文件驱动的.

#### 4.1 CMake Syntax

CMakeLists文件遵循由注释、命令和空白符构成的简单语法:

- 注释行以`#`开始;
- 命令由命令名称、`(`、空白符分隔的参数列表、`)`构成;
- 空白符除了分隔参数外, 均被忽略;
- 被`""`包裹的内容视为单个参数, `\`用于转移字符.

#### 4.2 Basic Commands

- `project`

``` cmake
project (projectname [CXX] [C] [Java] [NONE])
```

`project`命名项目和可选的指定语言, 通常是出现在顶层CMakeLists文件中的第一个命令.

对项目中出现的每个`project`命令, CMake会创建一个顶层IDE项目. 该项目会包含CMakeLists.txt中的所有目标和用`add_subdirectory`命令指定的子目录中的目标. 如果在`add_subdirectory`命令中使用`EXCLUDE_FROM_ALL`选项, 生成的项目不会在顶层Makefile或IDE项目文件中出现.

- `set`, `remove`, `separate_arguments`

`set`命令用于定义和修改变量和列表;<br>
`remove`命令用于从变量列表中移除值;<br/>
`separate_arguments`用于将单个值按空格拆分为列表.

- `add_executable`, `add_library`

定义构建生成的库和执行体, 以及构成库和执行体的源文件.

#### 4.3 Flow Control

CMake支持三种流程控制结构:

- 条件语句: `if`;
- 循环构造: `foreach`、`while`;
- 过程定义: `macro`、`function`;
- 中断处理流: `break`退出`foreach`、`while`循环; `return`从函数或listfile返回.

`if-else-endif`: 两种风格

``` cmake
if (FOO)
  # ...
else (FOO)
  # ...
endif (FOO)

if (FOO)
  # ...
else ()
  # ...
endif ()
```

`if-elseif-endif`:

``` cmake
if (MSVC80)
  # ...
elseif (MSVC90)
  # ...
elseif (APPLE)
  # ...
endif ()
```

`if`命令不支出C风格表达式(例如`${FOO} && ${BAR} || ${FUBAR}`), 只支持:

- `if (variable)`: `variable`的值不为空、`FALSE`、`OFF`或`NOTFOUND`时为真;
- `if (NOT variable)`: `variable`的值为空、`FALSE`、`OFF`或`NOTFOUND`时为真;
- `if (variable1 AND variable2)`: 均为真时为真;
- `if (variable1 OR variable2)`: 存在真时为真;
- `if (COMMAND command-name)`: `command-name`是命令名称时为真;
- `if (DEFINED variable)`: `variable`被设置时为真;
- `if (EXISTS file-name)`: 文件存在时为真;
- `if (EXISTS directory-name)`: 目录存在时为真;
- `if (IS_DIRECTORY name)`: `name`为目录名称时为真;
- `if (IS_ABSOLUTE name)`: `name`为绝对路径时为真;
- `if (name1 IS_NEWER_THAN name2)`: `name1`的修改时间比`name2`晚时为真;
- `if (variable MATCHES regex)`: `variable`的值匹配正则表达式时为真;
- `if (string MATCHES regex)`: 字符串匹配正则表达式时为真.

比较选项:

- 数值比较: `EQUAL`、`LESS`、`GREATER`;
- 字典序比较: `STRLESS`、`STREQUAL`、`STRGREATER`;
- 版本(`major[.minor[.patch[.tweak]]]`)比较: `VERSION_LESS`、`VERSION_EQUAL`、`VERSION_GREATER`.

优先级, 从高到低:

```
带()的分组
EXISTS, COMMAND, DEFINED等前缀操作符
EQUAL, LESS, GREATER, STREQUAL, STRLESS, STRGREATER, MATCHES
NOT
AND, OR
```

真假值: 大小写不敏感

- 真: ON, 1, YES, TRUE, Y;
- 假: OFF, 0, NO, FALSE, N, NOTFOUND, *-NOTFOUND, IGNORE.

`foreach`、`while`、`function`、`macro`的示例见`CMAKE_EXAMPLE_DIR/ch04/flow_control`.

`function`与C/C++中函数类似, 接受参数, 会开启新的变量作用域, 可以使用标准变量`ARGC`、`ARGV`、 `ARGN`、`ARGV0`、`ARGV1`等.

`macro`不会开发新的变量作用域, 其参数不被视为变量, 而是作为执行前被替换的文本. 支持变长参数列表, 变长参数用`ARGC`、`ARGV0`、`ARGV1`等引用.

#### 4.4 Regular Expressions

支持的正则表达式元字符:

- `^`: 匹配行或字符串的开始;
- `$`: 匹配行或字符串的结束;
- `.`: 匹配除换行符之外的任意单个字符;
- `[]`: 匹配方括号中出现的任意字符;
- `[^]`: 匹配不在方括号中出现的任意字符;
- `[-]`: 匹配字符区间中的任意字符;
- `*`: 匹配零次或多次;
- `+`: 匹配一次或多次;
- `?`: 匹配零次或一次;
- `()`: 表达式分组;
- `(|)`: 备选.

#### 4.5 Checking Versions of CMake

使用`CMAKE_VERSION`变量检测版本:

``` cmake
if (${CMAKE_VERSION} VERSION_GREATER 1.6.1)
  # ...
endif ()
```

在CMakeLists文件中指定支持的最小版本:

``` cmake
cmake_minimum_required(VERSION 3.16)
```

#### 4.6 Using Modules

模块是放在文件中的CMake命令片段, 使用`include`命令可以将模块包含到CMakeLists中.

模块位置可以使用模块文件的完整路径; 如果不是完整路径, CMake会在`CMAKE_MODULE_PATH`目录中查找, 如果没找到会在安装目录下的Modules目录下查找.

模块的类别:

- 查找模块: 确定头文件、库的位置;
- 系统内省(system introspection)模块: 检测系统的属性;
- 工具模块.

查看模块列表和具体模块:

```
cmake --help-module-list
cmake --help-module FindZLIB
```

#### 4.7 Policies

策略是CMake用于增强后向兼容性和跟踪兼容性问题的机制.

> skip

#### 4.8 Linking Libraries

库: `/path/to/libfoo.a`, `/path/to/libfoo.so`

``` cmake
# libfoo.a
add_executable (myexe myexe.c)
target_link_libraries (myexe /path/to/libfoo.a)

# libA.so, libB.so
link_directories (/path/to)
add_executable (myexe myexe.c)
target_link_libraries (myexe /path/to/libA.so B)
```

链接到系统库: 系统库通常在`/usr/lib`或`/lib`中.

``` cmake
find_library (M_LIB m)
target_link_libraries (myexe ${M_LIB})

# matches:
# /usr/lib/libm.so
# /usr/lib32/libm.so
# /usr/lib64/libm.so
```

#### 4.9 Shared Libraries and Loadable Modules

> skip

#### 4.10 Shared Library Versioning

``` cmake
set_target_properties (foo PROPERTIES VERSION 1.2 SOVERSION 4)
```

产生库和符号链接:

```
libfoo.so.1.2
libfoo.so.4 -> libfoo.so.1.2
libfoo.so -> libfoo.so.4
```

#### 4.11 Installing Files

`install`命令告知如何生成安装脚本. 对`install`命令的调用定义了一些安装规则, 在单个CMakeLists文件中按序求值, 而在多个目录中求值顺序未指定.

不同的签名:

``` cmake
install (TARGETS ...)     # 安装项目中构建的目标对应的二进制文件
install (FILES ...)       # 通用的文件安装: 头文件、文档和数据文件
install (PROGRAMS ...)    # 安装不由项目构建的执行文件, 例如Shell脚本
install (DIRECTORY ...)   # 安装整个目录树

install (SCRIPT ...)      # 指定安装时执行的CMake脚本文件
install (CODE ...)        # 指定安装时执行的CMake代码
```

#### 4.12 Advanced Commands


``` cmake
add_dependencies (...)            # 创建目标之间的依赖
include_regular_expression (...)  # 控制用于跟踪源代码依赖的正则表达式
output_required_files (...)       # 取一个源文件, 输出该文件依赖的文件列表
```

### 5 SYSTEM INSPECTION

系统内省: 检查软件构建所在的系统的环境; 包括

- 查找和使用头文件和库;
- 一些高级特性: `try_compile`、`try_run`命令等.

#### 5.1 Using Header Files and Libraries

使用文件、库、包、程序的相关CMake命令:

``` cmake
find_file (...)
find_library (...)
find_path (...)
find_program (...)
find_package (...)
```

例:

``` cmake
find_library (TIFF_LIBRARY
              NAMES tiff tiff2                # 查找库libtiff或libtiff2
              PATHS /usr/local/lib /usr/lib)  # 指定除环境变量PATH之外的路径

find_path (TIFF_INCLUDES tiff.h               # 在指定目录中查找头文件
          /usr/local/include
          /usr/include)

include_directories (${TIFF_INCLUDES})              # 包含头文件
add_executable (mytiff mytiff.c)
target_link_libraries (myprogram ${TIFF_LIBRARY})   # 链接库
```

#### 5.2 System Properties

`try_compile`和`try_run`在CMake配置时编译和运行简单的测试程序, 使用构建项目的编译器编译该程序, 如果出现错误, 则该特性被禁用.

- `try_compile (...)`: 尝试编译测试程序, 依据是否可编译设置特性启用/禁用;
- `try_run (...)`: 尝试编译和运行测试程序, 可获得程序运行的输出.

一些预先定义的`try-compile`和`try-run`宏(在`CMAKE_MODULE_DIR`目录下):

- CMakeCheckCompilerFlagCommonPatterns.cmake
- CMakePushCheckState.cmake
- CheckCCompilerFlag.cmake
- CheckCSourceCompiles.cmake
- CheckCSourceRuns.cmake
- CheckCXXCompilerFlag.cmake
- CheckCXXSourceCompiles.cmake
- CheckCXXSourceRuns.cmake
- CheckCXXSymbolExists.cmake
- CheckFortranCompilerFlag.cmake
- CheckFortranFunctionExists.cmake
- CheckFortranSourceCompiles.cmake
- CheckFortranSourceRuns.cmake
- CheckFunctionExists.cmake: 检查系统中是否有C函数;
- CheckIPOSupported.cmake
- CheckIncludeFile.cmake: 检查系统中的包含文件;
- CheckIncludeFileCXX.cmake: 检查C++程序中的包含文件;
- CheckIncludeFiles.cmake: 检查一组包含文件
- CheckLanguage.cmake
- CheckLibraryExists.cmake: 检查库是否存在;
- CheckOBJCCompilerFlag.cmake
- CheckOBJCSourceCompiles.cmake
- CheckOBJCSourceRuns.cmake
- CheckOBJCXXCompilerFlag.cmake
- CheckOBJCXXSourceCompiles.cmake
- CheckOBJCXXSourceRuns.cmake
- CheckPIESupported.cmake
- CheckPrototypeDefinition.cmake
- CheckSizeOf.cmake
- CheckStructHasMember.cmake
- CheckSymbolExists.cmake: 检查符号是否在一个头文件中定义;
- CheckTypeSize.cmake: 确定变量类型的字节大小;
- CheckVariableExists.cmake: 检查全局变量是否存在.

#### 5.3 Finding Packages

使用`find_package`命令查找包:

``` cmake
find_package (<Package> [version])
```

- `<Package>`是包名;
- `[version]`是可选的版本请求, 形式为`major.[.minor.[patch]]`.

`find_package`有两个模式:

- `Module`模式: 使用`find-module`查找`Find<Package>.cmake`;
- `Config`模式: `Module`模式失败或用户明确要求情况下使用, 查找包配置文件: `<Package>Config[Version].cmake`或`<package>-config[-version].cmake`.

#### 5.4 Built-in Find Modules

内建的查找模块`Find<XX>.cmake`, 有约定的变量:

- `<XX>_INCLUDE_DIRS`: 包的头文件位置, 头文件通常为`<XX>.h`;
- `<XX>_LIBRARIES`: 使用`<XX>`需要链接的库, 包含完整路径;
- `<XX>_DEFINITIONS`: 使用`<XX>`编译代码时使用的预处理器定义;
- `<XX>_EXECUTABLE`: 包中`<XX>`工具的路径;
- `<XX>_<YY>_EXECUTABLE`: 与`<XX>`一同的`<YY>`工具的路径;
- `<XX>_ROOT_DIR`: `<XX>`安装位置的基目录.
- `<XX>_VERSION_<YY>`: 包`<XX>`的版本`<YY>`是否找到;
- `<XX>_<YY>_FOUND`: 包`<XX>`的可选`<YY>`是否找到;
- `<XX>_FOUND`: 未找到`<XX>`.

``` cmake
find_package(OpenGL)
```

等价于:

``` cmake
include (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)
include (FindOpenGL)
```

#### 5.5 How to Pass Parameters to a Compilation?

一旦确定了系统中的特性, 需要基于这些事实配置软件, 有两种方式传递这些事实信息给编译器:

- 使用编译行: 在CMakeLists文件中使用`add_definitions`命令给编译器传递预处理器定义;
- 使用预配置的头文件: 头文件中包含了构建项目所需的所有`#define`宏, 详情见5.6节.

``` cmake
# 选项变量
option (DEBUG_BUILD "Build with extra debug pring message")

if (DEBUG_BUILD)
  add_definitions (-DDEBUG_BUILD) # 传递预处理器定义
endif (DEBUG_BUILD)
```

``` c
# 在C文件中使用预处理器定义
#ifdef DEBUG_BUILD
  printf("[DEBUG]\n");
#endif
```

使用`COMPILE_DEFINITIONS`属性细粒度的传递预处理器定义:

``` cmake
add_library (mylib src1.c src2.c)
add_executable (myexe main1.c)

set_property (DIRECTORY                 # 目录
  PROPERTY COMPILE_DEFINITIONS A AV=1)
set_property (TARGET mylib              # 目标
  PROPERTY COMPILE_DEFINITIONS B BV=2)
set_property (SOURCE src1.c             # 源文件
  PROPERTY COMPILE_DEFINITIONS C CV=3)
set_property (SOURCE src1.c
  APPEND PROPERTY COMPILE_DEFINITIONS D DV=4) # 与上述完整设置属性的方式不同, 这里追加属性

# 只在Debug配置中使用-DMYLIB_DEBUG_MODE编译mylib
set_property (TARGET mylib
  PROPERTY COMPILE_DEFINITIONS_DEBUG MYLIB_DEBUG_MODE)
```

- 使用`add_definitions`命令时`-DX`定义会添加到当前目录的`COMPILE_DEFINITIONS`属性中;
- 使用`add_subdirectory`创建子目录时, 当前目录的`COMPILE_DEFINITIONS`属性会传播到子目录.

#### 5.6 How to Configure a Header File

使用`configure_file`命令配置头文件: 在提供的输入文件中展开或替换所有变量.

在输入文件中使用变量的三种方式:

- `#cmakedefine VARIABLE`: `VARIABLE`为真时结果为`#define VARIABLE`, 否则为`/*#undef VARIABLE */`
- `${VARIABLE}`: 用`VARIABLE`的值替换;
- `@VARIABLE@`: 用`VARIABLE`的值替换. 传递`@ONLY`选项给`configure_file`命令时使用.

例:

``` cmake
configure_file (
  ${PROJECT_SOURCE_DIR}/projectConfigure.h.in
  ${PROJECT_BINARY_DIR}/projectConfigure.h)     # 放在二进制树中, 使用`include_directories`命令放入项目列表中
```

``` c
// projectConfigure.h.in

#cmake HAS_FOOBAR_CALL
#define PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR}"
```

#### 5.7 Creating CMake Package Configuration Files

在二进制树或构建树中安装和导出目标: 使用包配置文件.

### 6 CUSTOM COMMANDS AND TARGETS

使用自定义命令和目标执行CMake没有内置支持的复杂任务, 例如编译文档、生成源文件、移动和处理结果执行体等.

#### 6.1 Portable Custom Commands

`cmake -E`是一个通用的跨平台工具命令. 在CMakeLists文件中使用`CMAKE_COMMAND`引用`cmake`.

CMake提供了一些描述平台特征的变量.

#### 6.2 Using `add_custom_command` an a Target

`add_custom_command`命令有两种使用方式:

- 向目标添加自定义命令;
- 为构建输出文件添加自定义命令.

``` cmake
add_custom_command (TARGET target
  PRE_BUILD | PRE_LINK | POST_BUILD
  COMMAND command [ARGS arg1 arg2 arg3 ...]
  [COMMAND command [ARGS arg1 arg2 arg3 ...] ...]
  [COMMENT comment])

add_custom_command (OUTPUT output1 [output2 ...]
  COMMAND command [ARGS [args ...]]
  [COMMAND command [ARGS arg1 arg2 arg3 ...] ...]
  [MAIN_DEPENDENCY depend]
  [DEPENDS [depends ...]]
  [COMMENT comment])
```

例: 拷贝构建后的执行体

``` cmake
add_executable (Foo bar.c)
get_target_property (EXE_LOC Foo LOCATION)

add_custom_command (TARGET Foo
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${EXE_LOC} /testing_deparment/files)
```

#### 6.3 Using `add_custom_command` to Generate a File

例: 使用执行体构建源文件

``` cmake
add_executable (creator creator.cxx)
get_target_property (EXE_LOC creator LOCATION)
add_custom_command (OUTPUT ${PROJECT_BINARY_DIR}/created.c
  DEPENDS creator
  COMMAND ${EXE_LOC} ARGS ${PROJECT_BINARY_DIR}/created.c)

add_executable (Foo ${PROJECT_BINARY_DIR}/created.c)
```

#### 6.4 Adding a Custom Target

自定义目标例: 构建文档、运行测试等. 使用`add_custom_target`命令:

``` cmake
add_custom_target (name [ALL]
  [command arg1 arg2 arg3 ...]
  [DEPENDS dep1 dep2 dep3 ...])
```

- `name`: 自定义目标的名称;
- `ALL`: 该目标被包含在`ALL_BUILD`目标里, 每当项目构建时自动构建;
- 命令和参数是可选的, 作为目标的后置构建命令;
- `DEPENDS`: 列出目标依赖的文件.

例: 从.tex生成.pdf

``` cmake
add_custom_command (OUTPUT ${PROJECT_BINARY_DIR}/doc1.pdf
  DEPENDS ${PROJECT_SOURCE_DIR}/doc1.tex
  COMMAND ${LATEX} ARGS ${PROJECT_SOURCE_DIR}/doc1.tex
  COMMAND ${DVIPDF} ARGS ${PROJECT_BINARY_DIR}/doc1.dvi)

add_custom_target (TDocument ALL
  DEPENDS ${PROJECT_BINARY_DIR}/doc1.pdf)
```

#### 6.5 Specifying Dependencies and Outputs

在自定义命令中指定依赖或输出时, 应该总是使用完整路径.

在将目标指定为依赖时, 可以直接使用目标名称.

#### 6.6 When There Isn't One Rute For One Output

两种情况:

- 单个命令/执行体产生多个输出: 在`OUTPUT`关键字后列出多个输出、命令相同但参数不同.
- 多个命令可用于产生单个输出.

### 7 CONVERTING EXISTING SYSTEMS TO CMAKE - TODO
#### 7.1 Source Code Directory Structures
#### 7.2 Build Directories
#### 7.3 Useful CMake Commands When Converting Projects
#### 7.4 Converting UNIX Makefiles
#### 7.5 Converting Autoconf Based Projects
#### 7.6 Converting Windows Based Workspaces

### 8 CROSS COMPILING WITH CMAKE - TODO
#### 8.1 Toolchain Files
#### 8.2 System Inspection
#### 8.3 Running Executables Built in the Project
#### 8.4 Cross Compiling Hello World
#### 8.5 Cross Compiling for a Microcontroller
#### 8.6 Cross Compiling an Existing Project
#### 8.7 Cross Compiling a Complex Project - VTK
#### 8.8 Some Tips and Tricks

### 9 PACKAGING WITH CPACK - TODO
#### 9.1 CPack Basics
#### 9.2 CPack Source Packages
#### 9.3 CPack Installer Commands
#### 9.4 CPack for Windows Installer NSIS
#### 9.5 CPack for Cygwin Setup
#### 9.6 CPack for Mac OS X PackageMaker
#### 9.7 CPack for Mac OS X Drag and Drop
#### 9.8 CPack for Mac OS X X11 Applications
#### 9.9 CPack for Debian Packages
#### 9.10 CPack for RPM
#### 9.11 CPack Files

### 10 AUTOMATION & TESTING WITH CMAKE - TODO
#### 10.1 Testing with CMake, CTest, and CDash
#### 10.2 How Does CMake Facilitate Testing?
#### 10.3 Additional Test Properties
#### 10.4 Testing Using CTest
#### 10.5 Using CTest to Drive Complex Tests
#### 10.6 Handling a Large Number of Tests
#### 10.7 Producing Test Dashboards
#### 10.8 Customizing Dashboards for a Project
#### 10.9 Setting up Automated Dashboard Clients
#### 10.10 Advanced CTest Scripting
#### 10.11 Setting up a Dashboard Server
#### 10.12 Subprojects

### 11 PORTING CMAKE TO NEW PLATFORMS AND LANGUAGES - TODO
#### 11.1 The Determine System Process
#### 11.2 The Enable Language Process
#### 11.3 Porting to a New Platform
#### 11.4 Adding a New Language
#### 11.5 Rule Variable Listing
#### 11.6 Compiler and Platform Examples
#### 11.7 Extending CMake

### 12 TUTORIALS

见示例`CMAKE_EXAMPLE_DIR/ch12/tutorial`

#### APPENDIX

见[References](./refs/index.md)

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

```
$ uname -a
Linux DESKTOP-V3GKSFN 4.19.128-microsoft-standard #1 SMP Tue Jun 23 12:58:10 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
$ cmake --version
cmake version 3.16.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).

$ sudo apt install cmake-curses-gui
```

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- Ken Matring, Bill Hoffman. **Mastering CMake**.
- [CMake Reference Documentation](https://cmake.org/documentation/)
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)

## 其他备注

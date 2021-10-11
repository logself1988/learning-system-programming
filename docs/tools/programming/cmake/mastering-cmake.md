# Notes of **Mastering CMake, pre-3.0**


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
#### 2.6 Editing CMakeLists Files
#### 2.7 Setting Initial Values for CMake
#### 2.8 Building Your Project

### 3 KEY CONCEPTS
#### 3.1 Main Structures
#### 3.2 Targets
#### 3.3 Source Files
#### 3.4 Directories, Generators, Tests, and Properties
#### 3.5 Variables and Cache Entries
#### 3.6 Build Configurations

### 4 WRITING CMAKELISTS FILES
#### 4.1 CMake Syntax
#### 4.2 Basic Commands
#### 4.3 Flow Control
#### 4.4 Regular Expressions
#### 4.5 Checking Versions of CMake
#### 4.6 Using Modules
#### 4.7 Policies
#### 4.8 Linking Libraries
#### 4.9 Shared Libraries and Loadable Modules
#### 4.10 Shared Library Versioning
#### 4.11 Installing Files
#### 4.12 Advanced Commands

### 5 SYSTEM INSPECTION
#### 5.1 Using Header Files and Libraries
#### 5.2 System Properties
#### 5.3 Finding Packages
#### 5.4 Built-in Find Modules
#### 5.5 How to Pass Parameters to a Compilation?
#### 5.6 How to Configure a Header File
#### 5.7 Creating CMake Package Configuration Files

### 6 CUSTOM COMMANDS AND TARGETS
#### 6.1 Portable Custom Commands
#### 6.2 Using add_custom_command an a Target
#### 6.3 Using add_custom_command to Generate a File
#### 6.4 Adding a Custom Target
#### 6.5 Specifying Dependencies and Outputs
#### 6.6 When There Isn't One Rute For One Output

### 7 CONVERTING EXISTING SYSTEMS TO CMAKE
#### 7.1 Source Code Directory Structures
#### 7.2 Build Directories I
#### 7.3 Useful CMake Commands When Converting Projects
#### 7.4 Converting UNIX Makefiles
#### 7.5 Converting Autoconf Based Projects
#### 7.6 Converting Windows Based Workspaces

### 8 CROSS COMPILING WITH CMAKE
#### 8.1 Toolchain Files
#### 8.2 System Inspection
#### 8.3 Running Executables Built in the Project
#### 8.4 Cross Compiling Hello World
#### 8.5 Cross Compiling for a Microcontroller
#### 8.6 Cross Compiling an Existing Project
#### 8.7 Cross Compiling a Complex Project - VTK
#### 8.8 Some Tips and Tricks

### 9 PACKAGING WITH CPACK
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

### 10 AUTOMATION & TESTING WITH CMAKE
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

### 11 PORTING CMAKE TO NEW PLATFORMS AND LANGUAGES241
#### 11.1 The Determine System Process
#### 11.2 The Enable Language Process
#### 11.3 Porting to a New Platform
#### 11.4 Adding a New Language
#### 11.5 Rule Variable Listing
#### 11.6 Compiler and Platform Examples
#### 11.7 Extending CMake

### 12 TUTORIALS
#### 12.1 A Basic Starting Point (Step 1)
#### 12.2 Adding a Library (Step 2)
#### 12.3 Installing and Testing (Step 3)
#### 12.4 Adding System Introspection (Step 4)
#### 12.5 Adding a Generated File and Generator (Step 5)
#### 12.6 Building an Installer (Step 6)
#### 12.7 Adding Support for a Dashboard (Step 7)

#### APPENDIX A - VARIABLES
#### Variables That Change Behavior
#### Variables That Describe the System
#### Variables for Languages
#### Variables That Control the Build
#### Variables That Provide Information

#### APPENDIX B — COMMAND LINE REFERENCE
#### CMake Command Line Options
#### CMake Generators
#### CTest Command Line Options
#### CPack Command Line Options
#### CPack Generators

#### APPENDIX C — LISTFILE COMMANDS
#### Current Commands
#### Compatibility Commands

#### APPENDIX D — SELECTED MODULES
#### CMake Modules

#### INDEX

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

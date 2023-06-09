# Notes of **The Linux Programming Interface**

> 作为系统调用的详细描述.

- [Book website](http://man7.org/tlpi/index.html): With 1552 pages, 115 diagrams, 88 tables, nearly 200 example programs, and over 200 exercises, TLPI is the most comprehensive description of Linux and UNIX system programming available.
- [系统调用的概览](syscall.md)
- [Source Code for The Linux Programming Interface](https://man7.org/tlpi/code/)


## 1 历史和标准
### 1.1 UNIX和C语言简史
### 1.2 Linux简史
#### 1.2.1 GNU项目
#### 1.2.2 Linux内核
### 1.3 标准化
#### 1.3.1 C编程语言
#### 1.3.2 首个POSIX标准
#### 1.3.3 X/Open公司和The Open Group
#### 1.3.4 SUSv3和POSIX.1-2001
#### 1.3.5 SUSv4和POSIX.1-2008
#### 1.3.6 UNIX标准时间表
#### 1.3.7 实现标准
#### 1.3.8 Linux、标准、Linux标准规范(Linux Standard Base)
### 1.4 总结

## 2 基本概念
### 2.1 操作系统的核心—内核
### 2.2 shell
### 2.3 用户和组
### 2.4 单根目录层级、目录、链接及文件
### 2.5 文件I/O模型
### 2.6 程序
### 2.7 进程
### 2.8 内存映射
### 2.9 静态库和共享库
### 2.10 进程间通信及同步
### 2.11 信号
### 2.12 线程
### 2.13 进程组和shell任务控制
### 2.14 会话、控制终端和控制进程
### 2.15 伪终端
### 2.16 日期和时间
### 2.17 客户端服务器架构
### 2.18 实时性
### 2.19 /proc文件系统
### 2.20 总结

## 3 系统编程概念
### 3.1 系统调用
### 3.2 库函数
### 3.3 标准C语言函数库；GNU C语言函数库(glibc)

- [The GNU C Library (glibc)](https://www.gnu.org/software/libc/)

> The GNU C Library project provides the core libraries for the GNU system and GNU/Linux systems, as well as many other systems that use Linux as the kernel. These libraries provide critical APIs including ISO C11, POSIX.1-2008, BSD, OS-specific APIs and more. These APIs include such foundational facilities as open, read, write, malloc, printf, getaddrinfo, dlopen, pthread_create, crypt, login, exit and more.

``` C
#include <gnu/libc-version.h>
const char *gnu_get_libc_version(void);
  // Returns pointer to null-terminated, statically allocated string containing GNU C library version number
```

### 3.4 处理来自系统调用和库函数的错误

``` C
#include <stdio.h>
void perror(const char *msg);
```

``` C
#include <string.h>
char *strerror(int errnum);
  // Returns pointer to error string corresponding to errnum
```

### 3.5 关于本书示例程序的注意事项
#### 3.5.1 命令行选项及参数
#### 3.5.2 常用的函数及头文件

```
lib/tlpi_hdr.h

lib/error_functions.h
lib/error_functions.c
lib/ename.c.inc

lib/get_num.h
lib/get_num.c
```

### 3.6 可移植性问题
#### 3.6.1 特性测试宏

```
_POSIX_SOURCE
_POSIX_C_SOURCE
_XOPEN_SOURCE

glibc-specific:
_BSD_SOURCE
_SVID_SOURCE
_GNU_SOURCE
```


#### 3.6.2 系统数据类型

|Name|Type|Description|Ref|
|:---|:---|:---|---:|
|blkcnt_t     |signed integer           |  File block count |15.1|
|blksize_t    |signed integer           |  File block size |15.1|
|cc_t         |unsigned integer         | Terminal special character |62.4|
|clock_t      |integer or real-floating | System time in clock ticks |10.7|
|clockid_t    |an arithmetic type       | Clock identifier for POSIX.1b clock and timer functions |23.6|
|comp_t       |not in SUSv3             | Compressed clock ticks |28.1|
|dev_t        |an arithmetic type       | Device number, consisting of major and minor numbers |15.1|
|DIR          |no type| requirement Directory stream |18.8|
|fd_set       |structure type           | File descriptor set for `select()`| |63.2.1|
|fsblkcnt_t   |unsigned integer         | File-system block count |14.11|
|fsfilcnt_t   |unsigned integer         | File count |14.11|
|gid_t        |integer                  | Numeric group identifier |8.3|
|id_t         |integer                  | A generic type for holding identifiers; large enough to hold at least pid_t, uid_t, and gid_t||
|in_addr_t    |32-bit unsigned integer  | IPv4 address |59.4|
|in_port_t    |16-bit unsigned integer  | IP port number |59.4|
|ino_t        |unsigned integer         | File i-node number |15.1|
|key_t        |an arithmetic type       | System V IPC key |45.2|
|mode_t       |integer                  | File permissions and type |15.1|
|mqd_t        |no type requirement, but shall not be an array type| POSIX message queue descriptor||
|msglen_t     |unsigned integer         | Number of bytes allowed in System V message queue |46.4|
|msgqnum_t    |unsigned integer         | Counts of messages in System V message queue |46.4|
|nfds_t       |unsigned integer         | Number of file descriptors for `poll()`| |63.2.2|
|nlink_t      |integer                  | Count of hard links to a file |15.1|
|off_t        |signed integer           | File offset or size |4.7, 15.1|
|pid_t        |signed integer           | Process ID, process group ID, or session ID |6.2, 34.2, 34.3|
|ptrdiff_t    |signed integer           | Difference between two pointer values, as a signed integer
|rlim_t       |unsigned integer         | Resource limit |36.2|
|sa_family_t  |unsigned integer         | Socket address family |56.4|
|shmatt_t     |unsigned integer         | Count of attached processes for a System V shared memory segment |48.8|
|sig_atomic_t |integer                  | Data type that can be atomically accessed |21.1.3|
|siginfo_t    |structure type           | Information about the origin of a signal |21.4|
|sigset_t     |integer or structure type| Signal set |20.9|
|size_t       |unsigned integer         | Size of an object in bytes||
|socklen_t    |integer type of at least 32 bits| Size of a socket address structure in bytes |56.3|
|speed_t      |unsigned integer         | Terminal line speed |62.7|
|ssize_t      |signed integer           | Byte count or (negative) error indication||
|stack_t      |structure type           | Description of an alternate signal stack |21.3|
|suseconds_t  |signed integer allowing range `[–1, 1000000]`| Microsecond time interval |10.1|
|tcflag_t     |unsigned integer         | Terminal mode flag bit mask |62.2|
|time_t       |integer or real-floating | Calendar time in seconds since the Epoch |10.1|
|timer_t      |an arithmetic type       | Timer identifier for POSIX.1b interval timer functions |23.6|
|uid_t        |integer                  | Numeric user identifier |8.1|

#### 3.6.3 其他的可移植性问题

### 3.7 总结
### 3.8 练习

## 4 文件I/O：通用的I/O模型
### 4.1 概述
### 4.2 通用I/O
### 4.3 打开一个文件：open()
#### 4.3.1 open()调用中的flags参数
#### 4.3.2 open()函数的错误
#### 4.3.3 creat()系统调用
### 4.4 读取文件内容：read()
### 4.5 数据写入文件：write()
### 4.6 关闭文件：close()
### 4.7 改变文件偏移量：lseek()
### 4.8 通用I/O模型以外的操作：ioctl()
### 4.9 总结
### 4.10 练习

## 5 深入探究文件I/O
### 5.1 原子操作和竞争条件
### 5.2 文件控制操作：fcntl()
### 5.3 打开文件的状态标志
### 5.4 文件描述符和打开文件之间的关系
### 5.5 复制文件描述符
### 5.6 在文件特定偏移量处的I/O：pread()和pwrite()
### 5.7 分散输入和集中输出(Scatter-Gather I/O)：readv()和writev()
### 5.8 截断文件：truncate()和ftruncate()系统调用
### 5.9 非阻塞I/O
### 5.10 大文件I/O
### 5.11 /dev/fd目录
### 5.12 创建临时文件
### 5.13 总结
### 5.14 练习

## 6 进程
### 6.1 进程和程序
### 6.2 进程号和父进程号

``` C
#include <unistd.h>
pid_t getpid(void);
  // Always successfully returns process ID of caller
```

``` C
#include <unistd.h>
pid_t getppid(void);
  // Always successfully returns process ID of parent of caller
```

``` C
#include <stdlib.h>
int putenv(char *string);
  // Returns 0 on success, or nonzero on error
```

``` C
#include <stdlib.h>
int setenv(const char *name, const char *value, int overwrite);
  // Returns 0 on success, or –1 on error
```

``` C
#include <stdlib.h>
int unsetenv(const char *name);
  // Returns 0 on success, or –1 on error
```

``` C
#define _BSD_SOURCE /* Or: #define _SVID_SOURCE */
#include <stdlib.h>
int clearenv(void)
  // Returns 0 on success, or a nonzero on error
```

### 6.3 进程内存布局
### 6.4 虚拟内存管理
### 6.5 栈和栈帧
### 6.6 命令行参数(argc, argv)
### 6.7 环境列表

``` C
#include <stdlib.h>
char *getenv(const char *name);
  // Returns pointer to (value) string, or NULL if no such variable
```

``` C
#include <stdlib.h>
int putenv(char *string);
  // Returns 0 on success, or nonzero on error
```


### 6.8 执行非局部跳转：setjmp()和longjmp()

``` C
#include <setjmp.h>
int setjmp(jmp_buf env);
  // Returns 0 on initial call, nonzero on return via longjmp()

void longjmp(jmp_buf env, int val);
```

### 6.9 总结
### 6.9 练习

## 7 内存分配
### 7.1 在堆上分配内存
#### 7.1.1 调整program break：brk()和sbrk()

``` C
#include <unistd.h>
int brk(void *end_data_segment);
  // Returns 0 on success, or –1 on error

void *sbrk(intptr_t increment);
  // Returns previous program break on success, or (void *) –1 on error
```

#### 7.1.2 在堆上分配内存：malloc()和free()

``` C
#include <stdlib.h>
void *malloc(size_t size);
  // Returns pointer to allocated memory on success, or NULL on erro
```

``` C
#include <stdlib.h>
void free(void *ptr);
```

#### 7.1.3 malloc()和free()的实现
#### 7.1.4 在堆上分配内存的其他方法

``` C
#include <stdlib.h>
void *calloc(size_t numitems, size_t size);
  // Returns pointer to allocated memory on success, or NULL on error
```

``` C
#include <stdlib.h>
void *realloc(void *ptr, size_t size);
  // Returns pointer to allocated memory on success, or NULL on error
```

``` C
#include <malloc.h>
void *memalign(size_t boundary, size_t size);
  // Returns pointer to allocated memory on success, or NULL on error
```

``` C
#include <stdlib.h>
int posix_memalign(void **memptr, size_t alignment, size_t size);
  // Returns 0 on success, or a positive error number on error
```


### 7.2 在堆栈上分配内存：alloca()

``` C
#include <alloca.h>
void *alloca(size_t size);
  // Returns pointer to allocated block of memory
```

### 7.3 总结
### 7.4 练习

## 8 用户和组
### 8.1 密码文件：/etc/passwd
### 8.2 shadow密码文件：/etc/shadow
### 8.3 组文件：/etc/group
### 8.4 获取用户和组的信息
### 8.5 密码加密和用户认证
### 8.6 总结
### 8.7 练习

## 9 进程凭证
### 9.1 实际用户ID和实际组ID
### 9.2 有效用户ID和有效组ID
### 9.3 Set-User-ID和Set-Group-ID程序
### 9.4 保存set-user-ID和保存set-group-ID
### 9.5 文件系统用户ID和组ID
### 9.6 辅助组ID
### 9.7 获取和修改进程凭证
#### 9.7.1 获取和修改实际、有效和保存设置标识
#### 9.7.2 获取和修改文件系统ID
#### 9.7.3 获取和修改辅助组ID
#### 9.7.4 修改进程凭证的系统调用总结
#### 9.7.5 示例：显示进程凭证
### 9.8 总结
### 9.9 习题

## 10 时间
### 10.1 日历时间(Calendar Time)
### 10.2 时间转换函数
#### 10.2.1 将time_t转换为可打印格式
#### 10.2.2 time_t和分解时间之间的转换
#### 10.2.3 分解时间和打印格式之间的转换
### 10.3 时区
### 10.4 地区(Locale)
### 10.5 更新系统时钟
### 10.6 软件时钟(jiffies)
### 10.7 进程时间
### 10.8 总结
### 10.9 练习

## 11 系统限制和选项
### 11.1 系统限制
### 11.2 在运行时获取系统限制(和选项)
### 11.3 运行时获取与文件相关的限制(和选项)
### 11.4 不确定的限制
### 11.5 系统选项
### 11.6 总结
### 11.7 练习

## 12 系统和进程信息
### 12.1 /proc文件系统
#### 12.1.1 获取与进程有关的信息：/proc/PID
#### 12.1.2 /proc 目录下的系统信息
#### 12.1.3 访问/proc文件
### 12.2 系统标识：uname()
### 12.3 总结
### 12.4 练习

## 13 文件I/O缓冲
### 13.1 文件I/O的内核缓冲：缓冲区高速缓存
### 13.2 stdio库的缓冲
### 13.3 控制文件I/O的内核缓冲
### 13.4 I/O缓冲小结
### 13.5 就I/O模式向内核提出建议
### 13.6 绕过缓冲区高速缓存：直接I/O
### 13.7 混合使用库函数和系统调用进行文件I/O
### 13.8 总结
### 13.9 练习

## 14 系统编程概念
### 14.1 设备专用文件(设备文件)
### 14.2 磁盘和分区
### 14.3 文件系统
### 14.4 i节点
### 14.5 虚拟文件系统(VFS)
### 14.6 日志文件系统
### 14.7 单根目录层级和挂载点
### 14.8 文件系统的挂载和卸载
#### 14.8.1 挂载文件系统：mount()
#### 14.8.2 卸载文件系统：umount()和umount2()
### 14.9 高级挂载特性
#### 14.9.1 在多个挂载点挂载文件系统
#### 14.9.2 多次挂载同一挂载点
#### 14.9.3 基于每次挂载的挂载标志
#### 14.9.4 绑定挂载
#### 14.9.5 递归绑定挂载
### 14.10 虚拟内存文件系统：tmpfs
### 14.11 获得与文件系统有关的信息：statvfs()
### 14.12 总结
### 14.13 练习

## 15 文件属性
### 15.1 获取文件信息：stat()
### 15.2 文件时间戳
#### 15.2.1 使用utime()和utimes()来改变文件时间戳
#### 15.2.2 使用utimensat()和futimens()改变文件时间戳
### 15.3 文件属主
#### 15.3.1 新建文件的属主
#### 15.3.2 改变文件属主：chown()、fchown()和lchown()
### 15.4 文件权限
#### 15.4.1 普通文件的权限
#### 15.4.2 目录权限
#### 15.4.3 权限检查算法
#### 15.4.4 检查对文件的访问权限：access()
#### 15.4.5 Set-User-ID、Set-Group-ID和Sticky位
#### 15.4.6 进程的文件模式创建掩码：umask()
#### 15.4.7 更改文件权限：chmod()和fchmod()
### 15.5 I节点标志(ext2扩展文件属性)
### 15.6 总结
### 15.7 练习

## 16 扩展属性
### 16.1 概述
### 16.2 扩展属性的实现细节
### 16.3 操控扩展属性的系统调用
### 16.4 总结
### 16.5 练习

## 17 访问控制列表
### 17.1 概述
### 17.2 ACL权限检查算法
### 17.3 ACL的长、短文本格式
### 17.4 ACL_mask型ACE和ACL组分类
### 17.5 getfacl和setfacl命令
### 17.6 默认ACL与文件创建
### 17.7 ACL在实现方面的限制
### 17.8 ACL API
### 17.9 总结
### 17.10 练习

## 18 目录与链接
### 18.1 目录和(硬)链接
### 18.2 符号(软)链接
### 18.3 创建和移除(硬)链接：link()和 unlink()
### 18.4 更改文件名：rename()
### 18.5 使用符号链接：symlink()和readlink()
### 18.6 创建和移除目录：mkdir()和rmdir()
### 18.7 移除一个文件或目录：remove()
### 18.8 读目录：opendir()和readdir()
### 18.9 文件树遍历：nftw()
### 18.10 进程的当前工作目录
### 18.11 针对目录文件描述符的相关操作
### 18.12 改变进程的根目录：chroot()
### 18.13 解析路径名：realpath()
### 18.14 解析路径名字符串：dirname()和basename()
### 18.15 总结
### 18.16 练习

## 19 监控文件事件
### 19.1 概述
### 19.2 inotify API
### 19.3 inotify事件
### 19.4 读取inotify事件
### 19.5 队列限制和/proc文件
### 19.6 监控文件的旧有系统：dnotify
### 19.7 总结
### 19.8 练习

## 20 信号：基本概念
### 20.1 概念和概述
### 20.2 信号类型和默认行为
### 20.3 改变信号处置：signal()
### 20.4 信号处理器简介
### 20.5 发送信号：kill()
### 20.6 检查进程的存在
### 20.7 发送信号的其他方式：raise()和killpg()
### 20.8 显示信号描述
### 20.9 信号集
### 20.10 信号掩码(阻塞信号传递)
### 20.11 处于等待状态的信号
### 20.12 不对信号进行排队处理
### 20.13 改变信号处置：sigaction ()
### 20.14 等待信号：pause()
### 20.15 总结
### 20.16 练习

## 21 信号：信号处理器函数
### 21.1 设计信号处理器函数
#### 21.1.1 再论信号的非队列化处理
#### 21.1.2 可重入函数和异步信号安全函数
#### 21.1.3 全局变量和sig_atomic_t数据类型
### 21.2 终止信号处理器函数的其他方法
#### 21.2.1 在信号处理器函数中执行非本地跳转
#### 21.2.2 异常终止进程：abort()
### 21.3 在备选栈中处理信号：sigaltstack()
### 21.4 SA_SIGINFO标志
### 21.5 系统调用的中断和重启
### 21.6 总结
### 21.7 练习

## 22 信号：高级特性
### 22.1 核心转储文件
### 22.2 传递、处置及处理的特殊情况
### 22.3 可中断和不可中断的进程睡眠状态
### 22.4 硬件产生的信号
### 22.5 信号的同步生成和异步生成
### 22.6 信号传递的时机与顺序
### 22.7 signal()的实现及可移植性
### 22.8 实时信号
#### 22.8.1 发送实时信号
#### 22.8.2 处理实时信号
### 22.9 使用掩码来等待信号：sigsuspend()
### 22.10 以同步方式等待信号
### 22.11 通过文件描述符来获取信号
### 22.12 利用信号进行进程间通信
### 22.13 早期的信号API(System V和BSD)
### 22.14 总结
### 22.15 练习

## 23 定时器与休眠
### 23.1 间隔定时器
### 23.2 定时器的调度及精度
### 23.3 为阻塞操作设置超时
### 23.4 暂停运行(休眠)一段固定时间
#### 23.4.1 低分辨率休眠：sleep()
#### 23.4.2 高分辨率休眠：nanosleep()
### 23.5 POSIX时钟
#### 23.5.1 获取时钟的值：clock_gettime()
#### 23.5.2 设置时钟的值：clock_settime()
#### 23.5.3 获取特定进程或线程的时钟ID
#### 23.5.4 高分辨率休眠的改进版：clock_nanosleep()
### 23.6 POSIX间隔式定时器
#### 23.6.1 创建定时器：timer_create()
#### 23.6.2 配备和解除定时器：timer_settime()
#### 23.6.3 获取定时器的当前值：timer_gettime()
#### 23.6.4 删除定时器：timer_delete()
#### 23.6.5 通过信号发出通知
#### 23.6.6 定时器溢出
#### 23.6.7 通过线程来通知
### 23.7 利用文件描述符进行通知的定时器：timerfd API
### 23.8 总结
### 23.9 练习

## 24 进程的创建
### 24.1 fork()、exit()、wait()以及execve()的简介
### 24.2 创建新进程：fork()
#### 24.2.1 父、子进程间的文件共享
#### 24.2.2 fork()的内存语义
### 24.3 系统调用vfork()
### 24.4 fork()之后的竞争条件(Race Condition)
### 24.5 同步信号以规避竞争条件
### 24.6 总结
### 24.7 练习

## 25 进程的终止
### 25.1 进程的终止：_exit()和exit()
### 25.2 进程终止的细节
### 25.3 退出处理程序
### 25.4 fork()、stdio缓冲区以及_exit()之间的交互
### 25.5 总结
### 25.6 练习

## 26 监控子进程
### 26.1 等待子进程
#### 26.1.1 系统调用wait()
#### 26.1.2 系统调用waitpid()
#### 26.1.3 等待状态值
#### 26.1.4 从信号处理程序中终止进程
#### 26.1.5 系统调用waitid()
#### 26.1.6 系统调用wait3()和wait4()
### 26.2 孤儿进程与僵尸进程
### 26.3 SIGCHLD信号
#### 26.3.1 为SIGCHLD建立信号处理程序
#### 26.3.2 向已停止的子进程发送SIGCHLD信号
#### 26.3.3 忽略终止的子进程
### 26.4 总结
### 26.5 练习

## 27 程序的执行
### 27.1 执行新程序：execve()
### 27.2 exec()库函数
#### 27.2.1 环境变量PATH
#### 27.2.2 将程序参数指定为列表
#### 27.2.3 将调用者的环境传递给新程序
#### 27.2.4 执行由文件描述符指代的程序：fexecve()
### 27.3 解释器脚本
### 27.4 文件描述符与exec()
### 27.5 信号与exec()
### 27.6 执行shell命令：system()
### 27.7 system()的实现
### 27.8 总结
### 27.9 练习

## 28 详述进程创建和程序执行
### 28.1 进程记账
### 28.2 系统调用clone()
#### 28.2.1 clone()的flags参数
#### 28.2.2 因克隆生成的子进程而对waitpid()进行的扩展
### 28.3 进程的创建速度
### 28.4 exec()和fork()对进程属性的影响
### 28.5 总结
### 28.6 练习

## 29 线程：介绍
### 29.1 概述
### 29.2 Pthreads API的详细背景
### 29.3 创建线程
### 29.4 终止线程
### 29.5 线程ID(Thread ID)
### 29.6 连接(joining)已终止的线程
### 29.7 线程的分离
### 29.8 线程属性
### 29.9 线程VS进程
### 29.10 总结
### 29.11 练习

## 30 线程：线程同步
### 30.1 保护对共享变量的访问：互斥量
#### 30.1.1 静态分配的互斥量
#### 30.1.2 加锁和解锁互斥量
#### 30.1.3 互斥量的性能
#### 30.1.4 互斥量的死锁
#### 30.1.5 动态初始化互斥量
#### 30.1.6 互斥量的属性
#### 30.1.7 互斥量类型
### 30.2 通知状态的改变：条件变量(Condition Variable)
#### 30.2.1 由静态分配的条件变量
#### 30.2.2 通知和等待条件变量
#### 30.2.3 测试条件变量的判断条件(predicate)
#### 30.2.4 示例程序：连接任意已终止线程
#### 30.2.5 经由动态分配的条件变量
### 30.3 总结
### 30.4 练习

## 31 线程：线程安全和每线程存储
### 31.1 线程安全(再论可重入性)
### 31.2 一次性初始化
### 31.3 线程特有数据
#### 31.3.1 库函数视角下的线程特有数据
#### 31.3.2 线程特有数据API概述
#### 31.3.3 线程特有数据API详述
#### 31.3.4 使用线程特有数据API
#### 31.3.5 线程特有数据的实现限制
### 31.4 线程局部存储
### 31.5 总结
### 31.6 练习

## 32 线程：线程取消
### 32.1 取消一个线程
### 32.2 取消状态及类型
### 32.3 取消点
### 32.4 线程可取消性的检测
### 32.5 清理函数(cleanup handler)
### 32.6 异步取消
### 32.7 总结

## 33 线程：更多细节
### 33.1 线程栈
### 33.2 线程和信号
#### 33.2.1 UNIX信号模型如何映射到线程中
#### 33.2.2 操作线程信号掩码
#### 33.2.3 向线程发送信号
#### 33.2.4 妥善处理异步信号
### 33.3 线程和进程控制
### 33.4 线程实现模型
### 33.5 Linux POSIX线程的实现
#### 33.5.1 LinuxThreads
#### 33.5.2 NPTL
#### 33.5.3 哪一种线程实现
### 33.6 Pthread API的高级特性
### 33.7 总结
### 33.8 练习

下册

## 34 进程组、会话和作业控制
### 34.1 概述
### 34.2 进程组
### 34.3 会话
### 34.4 控制终端和控制进程
### 34.5 前台和后台进程组
### 34.6 SIGHUP信号
#### 34.6.1 在shell中处理SIGHUP信号
#### 34.6.2 SIGHUP和控制进程的终止
### 34.7 作业控制
#### 34.7.1 在shell中使用作业控制
#### 34.7.2 实现作业控制
#### 34.7.3 处理作业控制信号
#### 34.7.4 孤儿进程组(SIGHUP回顾)
### 34.8 总结
### 34.9 习题

## 35 进程优先级和调度
### 35.1 进程优先级(nice值)
### 35.2 实时进程调度概述
#### 35.2.1 SCHED_RR策略
#### 35.2.2 SCHED_FIFO策略
#### 35.2.3 SCHED_BATCH和SCHED_IDLE策略
### 35.3 实时进程调用API
#### 35.3.1 实时优先级范围
#### 35.3.2 修改和获取策略和优先级
#### 35.3.3 释放CPU
#### 35.3.4 SCHED_RR时间片
### 35.4 CPU亲和力
### 35.5 总结
### 35.6 习题

## 36 进程资源
### 36.1 进程资源使用
### 36.2 进程资源限制
### 36.3 特定资源限制细节
### 36.4 总结
### 36.5 习题

## 37 DAEMON
### 37.1 概述
### 37.2 创建一个daemon
### 37.3 编写daemon指南
### 37.4 使用SIGHUP重新初始化一个daemon
### 37.5 使用syslog记录消息和错误
#### 37.5.1 概述
#### 37.5.2 syslog API
#### 37.5.3 /etc/syslog.conf文件
### 37.6 总结
### 37.7 习题

## 38 编写安全的特权程序
### 38.1 是否需要一个Set-User-ID或Set-Group-ID程序？
### 38.2 以*小权限操作
### 38.3 小心执行程序
### 38.4 避免暴露敏感信息
### 38.5 确定进程的边界
### 38.6 小心信号和竞争条件
### 38.7 执行文件操作和文件I/O的缺陷
### 38.8 不要完全相信输入和环境
### 38.9 小心缓冲区溢出
### 38.10 小心拒绝服务攻击
### 38.11 检查返回状态和安全地处理失败情况
### 38.12 总结
### 38.13 习题

## 39 能力
### 39.1 能力基本原理
### 39.2 Linux能力
### 39.3 进程和文件能力
#### 39.3.1 进程能力
#### 39.3.2 文件能力
#### 39.3.3 进程许可和有效能力集的目的
#### 39.3.4 文件许可和有效能力集的目的
#### 39.3.5 进程和文件可继承集的目的
#### 39.3.6 在shell中给文件赋予能力和查看文件能力
### 39.4 现代能力实现
### 39.5 在exec()中转变进程能力
#### 39.5.1 能力边界集
#### 39.5.2 保持root语义
### 39.6 改变用户ID对进程能力的影响
### 39.7 用编程的方式改变进程能力
### 39.8 创建仅包含能力的环境
### 39.9 发现程序所需的能力
### 39.10 不具备文件能力的老式内核和系统
### 39.11 总结
### 39.12 习题

## 40 登录记账
### 40.1 utmp和wtmp文件概述
### 40.2 utmpx API
### 40.3 utmpx结构
### 40.4 从utmp和wtmp文件中检索信息
### 40.5 获取登录名称：getlogin()
### 40.6 为登录会话更新utmp和wtmp文件
### 40.7 lastlog文件
### 40.8 总结
### 40.9 习题

## 41 共享库基础
### 41.1 目标库
### 41.2 静态库
### 41.3 共享库概述
### 41.4 创建和使用共享库——首回合
#### 41.4.1 创建一个共享库
#### 41.4.2 位置独立的代码
#### 41.4.3 使用一个共享库
#### 41.4.4 共享库soname
### 41.5 使用共享库的有用工具
### 41.6 共享库版本和命名规则
### 41.7 安装共享库
### 41.8 兼容与不兼容库比较
### 41.9 升级共享库
### 41.10 在目标文件中指定库搜索目录
### 41.11 在运行时找出共享库
### 41.12 运行时符号解析
### 41.13 使用静态库取代共享库
### 41.14 总结
### 41.15 习题

## 42 共享库高级特性
### 42.1 动态加载库
#### 42.1.1 打开共享库：dlopen()
#### 42.1.2 错误诊断：dlerror()
#### 42.1.3 获取符号的地址：dlsym()
#### 42.1.4 关闭共享库：dlclose()
#### 42.1.5 获取与加载的符号相关的信息：dladdr()
#### 42.1.6 在主程序中访问符号
### 42.2 控制符号的可见性
### 42.3 链接器版本脚本
#### 42.3.1 使用版本脚本控制符号的可见性
#### 42.3.2 符号版本化
### 42.4 初始化和终止函数
### 42.5 预加载共享库
### 42.6 监控动态链接器：LD_DEBUG
### 42.7 总结
### 42.8 习题

## 43 进程间通信简介
### 43.1 IPC工具分类
### 43.2 通信工具
### 43.3 同步工具
### 43.4 IPC工具比较
### 43.5 总结
### 43.6 习题

## 44 管道和FIFO
### 44.1 概述
### 44.2 创建和使用管道
### 44.3 将管道作为一种进程同步的方法
### 44.4 使用管道连接过滤器
### 44.5 通过管道与Shell命令进行通信：popen()
### 44.6 管道和stdio缓冲
### 44.7 FIFO
### 44.8 使用管道实现一个客户端/服务器应用程序
### 44.9 非阻塞I/O
### 44.10 管道和FIFO中read()和write()的语义
### 44.11 总结
### 44.12 习题

## 45 System V IPC介绍
### 45.1 概述
### 45.2 IPC Key
### 45.3 关联数据结构和对象权限
### 45.4 IPC标识符和客户端/服务器应用程序
### 45.5 System V IPC get调用使用的算法
### 45.6 ipcs和ipcrm命令
### 45.7 获取所有IPC对象列表
### 45.8 IPC限制
### 45.9 总结
### 45.10 习题

## 46 System V消息队列
### 46.1 创建或打开一个消息队列
### 46.2 交换消息
#### 46.2.1 发送消息
#### 46.2.2 接收消息
### 46.3 消息队列控制操作
### 46.4 消息队列关联数据结构
### 46.5 消息队列的限制
### 46.6 显示系统中所有消息队列
### 46.7 使用消息队列实现客户端/服务器应用程序
### 46.8 使用消息队列实现文件服务器应用程序
### 46.9 System V消息队列的缺点
### 46.10 总结
### 46.11 习题

## 47 System V信号量
### 47.1 概述
### 47.2 创建或打开一个信号量集
### 47.3 信号量控制操作
### 47.4 信号量关联数据结构
### 47.5 信号量初始化
### 47.6 信号量操作
### 47.7 多个阻塞信号量操作的处理
### 47.8 信号量撤销值
### 47.9 实现一个二元信号量协议
### 47.10 信号量限制
### 47.11 System V信号量的缺点
### 47.12 总结
### 47.13 习题

## 48 System V共享内存
### 48.1 概述
### 48.2 创建或打开一个共享内存段
### 48.3 使用共享内存
### 48.4 示例：通过共享内存传输数据
### 48.5 共享内存在虚拟内存中的位置
### 48.6 在共享内存中存储指针
### 48.7 共享内存控制操作
### 48.8 共享内存关联数据结构
### 48.9 共享内存的限制
### 48.10 总结
### 48.11 习题

## 49 内存映射
### 49.1 概述
### 49.2 创建一个映射：mmap()
### 49.3 解除映射区域：munmap()
### 49.4 文件映射
#### 49.4.1 私有文件映射
#### 49.4.2 共享文件映射
#### 49.4.3 边界情况
#### 49.4.4 内存保护和文件访问模式交互
### 49.5 同步映射区域：msync()
### 49.6 其他mmap()标记
### 49.7 匿名映射
### 49.8 重新映射一个映射区域：mremap()
### 49.9 MAP_NORESERVE和过度利用交换空间
### 49.10 MAP_FIXED标记
### 49.11 非线性映射：remap_file_pages()
### 49.12 总结
### 49.13 习题

## 50 虚拟内存操作
### 50.1 改变内存保护：mprotect()
### 50.2 内存锁：mlock()和mlockatt()
### 50.3 确定内存驻留性：mincore()
### 50.4 建议后续的内存使用模式：madvise()
### 50.5 小结
### 50.6 习题

## 51 POSIX IPC介绍
### 51.1 API概述
### 51.2 System V IPC与POSIX IPC比较
### 51.3 总结

## 52 POSIX消息队列
### 52.1 概述
### 52.2 打开、关闭和断开链接消息队列
### 52.3 描述符和消息队列之间的关系
### 52.4 消息队列特性
### 52.5 交换消息
#### 52.5.1 发送消息
#### 52.5.2 接收消息
#### 52.5.3 在发送和接收消息时设置超时时间
### 52.6 消息通知
#### 52.6.1 通过信号接收通知
#### 52.6.2 通过线程接收通知
### 52.7 Linux特有的特性
### 52.8 消息队列限制
### 52.9 POSIX和System V消息队列比较
### 52.10 总结
### 52.11 习题

## 53 POSIX信号量
### 53.1 概述
### 53.2 命名信号量
#### 53.2.1 打开一个命名信号量
#### 53.2.2 关闭一个信号量
#### 53.2.3 删除一个命名信号量
### 53.3 信号量操作
#### 53.3.1 等待一个信号量
#### 53.3.2 发布一个信号量
#### 53.3.3 获取信号量的当前值
### 53.4 未命名信号量
#### 53.4.1 初始化一个未命名信号量
#### 53.4.2 销毁一个未命名信号量
### 53.5 与其他同步技术比较
### 53.6 信号量的限制
### 53.7 总结
### 53.8 习题

## 54 POSIX共享内存
### 54.1 概述
### 54.2 创建共享内存对象
### 54.3 使用共享内存对象
### 54.4 删除共享内存对象
### 54.5 共享内存APIs比较
### 54.6 总结
### 54.7 习题

## 55 文件加锁
### 55.1 概述
### 55.2 使用flock()给文件加锁
#### 55.2.1 锁继承与释放的语义
#### 55.2.2 flock()的限制
### 55.3 使用fcntl()给记录加锁
#### 55.3.1 死锁
#### 55.3.2 示例：一个交互式加锁程序
#### 55.3.3 示例：一个加锁函数库
#### 55.3.4 锁的限制和性能
#### 55.3.5 锁继承和释放的语义
#### 55.3.6 锁定饿死和排队加锁请求的优先级
### 55.4 强制加锁
### 55.5 /proc/locks文件
### 55.6 仅运行一个程序的单个实例
### 55.7 老式加锁技术
### 55.8 总结
### 55.9 习题

## 56 SOCKET：介绍
### 56.1 概述
### 56.2 创建一个socket：socket()
### 56.3 将socket绑定到地址：bind()
### 56.4 通用socket地址结构：struct sockaddr
### 56.5 流socket
#### 56.5.1 监听接入连接：listen()
#### 56.5.2 接受连接：accept()
#### 56.5.3 连接到对等socket：connect()
#### 56.5.4 流socket I/O
#### 56.5.5 连接终止：close()
### 56.6 数据报socket
#### 56.6.1 交换数据报：recvfrom和sendto()
#### 56.6.2 在数据报socket上使用connect()
### 56.7 总结

## 57 SOCKET：UNIX DOMAIN
### 57.1 UNIX domain socket地址：struct sockaddr_un
### 57.2 UNIX domain中的流socket
### 57.3 UNIX domain中的数据报socket
### 57.4 UNIX domain socket权限
### 57.5 创建互联socket对：socketpair()
### 57.6 Linux抽象socket名空间
### 57.7 总结
### 57.8 习题

## 58 SOCKET：TCP/IP网络基础
### 58.1 因特网
### 58.2 联网协议和层
### 58.3 数据链路层
### 58.4 网络层：IP
### 58.5 IP地址
### 58.6 传输层
#### 58.6.1 端口号
#### 58.6.2 用户数据报协议(UDP)
#### 58.6.3 传输控制协议(TCP)
### 58.7 请求注解(RFC)
### 58.8 总结

## 59 SOCKET：Internet DOMAIN
### 59.1 Internet domain socket
### 59.2 网络字节序
### 59.3 数据表示
### 59.4 Internet socket地址
### 59.5 主机和服务转换函数概述
### 59.6 inet_pton()和inet_ntop()函数
### 59.7 客户端-服务器示例(数据报socket)
### 59.8 域名系统(DNS)
### 59.9 /etc/services文件
### 59.10 独立于协议的主机和服务转换
#### 59.10.1 getaddrinfo()函数
#### 59.10.2 释放addrinfo列表：freeaddrinfo()
#### 59.10.3 错误诊断：gai_strerror()
#### 59.10.4 getnameinfo()函数
### 59.11 客户端-服务器示例(流式socket)
### 59.12 Internet domain socket库
### 59.13 过时的主机和服务转换API
#### 59.13.1 inet_aton()和inet_ntoa()函数
#### 59.13.2 gethostbyname()和gethostbyaddr()函数
#### 59.13.3 getserverbyname()和getserverbyport()函数
### 59.14 UNIX与Internet domain socket比较
### 59.15 更多信息
### 59.16 总结
### 59.17 习题

## 60 SOCKET：服务器设计
### 60.1 迭代型和并发型服务器
### 60.2 迭代型UDP echo服务器
### 60.3 并发型TCP echo服务器
### 60.4 并发型服务器的其他设计方案
### 60.5 inetd(Internetchaoji服务器)守护进程
### 60.6 总结
### 60.7 练习

## 61 SOCKET：高级主题
### 61.1 流式套接字上的部分读和部分写
### 61.2 shutdown()系统调用
### 61.3 专用于套接字的I/O系统调用：recv()和send()
### 61.4 sendfile()系统调用
### 61.5 获取套接字地址
### 61.6 深入探讨TCP协议
#### 61.6.1 TCP报文的格式
#### 61.6.2 TCP序列号和确认机制
#### 61.6.3 TCP协议状态机以及状态迁移图
#### 61.6.4 TCP连接的建立
#### 61.6.5 TCP连接的终止
#### 61.6.6 在TCP套接字上调用shutdown()
#### 61.6.7 TIME_WAIT状态
### 61.7 监视套接字：netstat
### 61.8 使用tcpdump来监视TCP流量
### 61.9 套接字选项
### 61.10 SO_REUSEADDR套接字选项
### 61.11 在accept()中继承标记和选项
### 61.12 TCP vs UDP
### 61.13 高级功能
#### 61.13.1 带外数据
#### 61.13.2 sendmsg()和recvmsg()系统调用
#### 61.13.3 传递文件描述符
#### 61.13.4 接收发送端的凭据
#### 61.13.5 顺序数据包套接字
#### 61.13.6 SCTP以及DCCP传输层协议
### 61.14 总结
### 61.15 练习

## 62 终端
### 62.1 整体概览
### 62.2 获取和修改终端属性
### 62.3 stty命令
### 62.4 终端特殊字符
### 62.5 终端标志
### 62.6 终端的I/O模式
#### 62.6.1 规范模式
#### 62.6.2 非规范模式
#### 62.6.3 加工模式、cbreak模式以及原始模式
### 62.7 终端线速(比特率)
### 62.8 终端的行控制
### 62.9 终端窗口大小
### 62.10 终端标识
### 62.11 总结
### 62.12 练习

## 63 其他备选的I/O模型
### 63.1 整体概览
#### 63.1.1 水平触发和边缘触发
#### 63.1.2 在备选的I/O模型中采用非阻塞I/O
### 63.2 I/O多路复用
#### 63.2.1 select()系统调用
#### 63.2.2 poll()系统调用
#### 63.2.3 文件描述符何时就绪？
#### 63.2.4 比较select()和poll()
#### 63.2.5 select()和poll()存在的问题
### 63.3 信号驱动I/O
#### 63.3.1 何时发送“I/O就绪”信号
#### 63.3.2 优化信号驱动I/O的使用
### 63.4 epoll编程接口
#### 63.4.1 创建epoll实例：epoll_create()
#### 63.4.2 修改epoll的兴趣列表：epoll_ctl()
#### 63.4.3 事件等待：epoll_wait()
#### 63.4.4 深入探究epoll的语义
#### 63.4.5 epoll同I/O多路复用的性能对比
#### 63.4.6 边缘触发通知
### 63.5 在信号和文件描述符上等待
#### 63.5.1 pselect()系统调用
#### 63.5.2 self-pipe技巧
### 63.6 总结
### 63.7 练习

## 64 伪终端
### 64.1 整体概览
### 64.2 UNIX98伪终端
#### 64.2.1 打开未使用的主设备：posix_openpt()
#### 64.2.2 修改从设备属主和权限：grantpt()
#### 64.2.3 解锁从设备：unlockpt()
#### 64.2.4 获取从设备名称：ptsname()
### 64.3 打开主设备：ptyMasterOpen()
### 64.4 将进程连接到伪终端：ptyFork()
### 64.5 伪终端I/O
### 64.6 实现script(1)程序
### 64.7 终端属性和窗口大小
### 64.8 BSD风格的伪终端
### 64.9 总结
### 64.10 练习

## 附录A 跟踪系统调用
## 附录B 解析命令行选项
## 附录C 对NULL指针做转型
## 附录D 内核配置
## 附录E 更多信息源
## 附录F 部分习题解答

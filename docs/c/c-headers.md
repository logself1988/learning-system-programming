#  Headers

## C99 Headers

|Section|header|description|
|:---|:---|:---|
|B.1|`<assert.h>`   | 验证程序断言 Diagnostics|
|B.2|`<complex.h>`  | 复数算数运算支持 Complex|
|B.3|`<ctype.h>`    | 字符分类和映射支持 Character handling|
|B.4|`<errno.h>`    | 出错码 Errors|
|B.5|`<fenv.h>`     | 浮点环境 Floating-point environment|
|B.6|`<float.h>`    | 浮点常量和特性 Characteristics of floating types|
|B.7|`<inttypes.h>` | 整形格式变换 Format conversion of integer types|
|B.8|`<iso646.h>`   | 赋值、关系和一元操作符宏 Alternative spellings|
|B.9|`<limits.h>`   | 实现常量 Sizes of integer types|
|B.10|`<locale.h>`  | 本地化类别和相关定义 Localization|
|B.11|`<math.h>`    | 数学函数、类型声明和常量 Mathematics|
|B.12|`<setjmp.h>`  | 非局部goto Nonlocal jumps|
|B.13|`<signal.h>`  | 信号 Signal handling|
|B.14|`<stdarg.h>`  | 可变长度参数表 Variable arguments|
|B.15|`<stdbool.h>` | 布尔类型和值 Boolean type and values|
|B.16|`<stddef.h>`  | 标准定义 Common definitions|
|B.17|`<stdint.h>`  | 整形 Integer types|
|B.18|`<stdio.h>`   | 标准IO库 Input/output|
|B.19|`<stdlib.h>`  | 通用函数 General utilities|
|B.20|`<string.h>`  | 字符串操作 String handling|
|B.21|`<tgmath.h>`  | 通用类型数学宏 Type-generic math|
|B.22|`<time.h>`    | 时间和日期 Date and time|
|B.23|`<wchar.h>`   | 扩充的多字符和宽字符支持 Extended multibyte/wide character utilities|
|B.24|`<wctype.h>`  | 宽字符分类和映射支持 Wide character classification and mapping utilities|


## POSIX.1-2017

### Headers

> The Open Group Base Specifications Issue 7, 2018 edition<br/>
> Topic Index<br/>
> Headers

|header|description|source|
|:---|:---|:---|
|`<aio.h>`          | 异步IO                 ||
|`<arpa/inet.h>`    | 因特网操作定义         ||
|`<assert.h>`       | 验证程序断言           |C标准库|
|`<complex.h>`      | 复数算术               |C标准库|
|`<cpio.h>`         | cpio归档值[^1]         ||
|`<ctype.h>`        | 字符类型               |C标准库|
|`<dirent.h>`       | 目录项                 ||
|`<dlfcn.h>`        | 动态链接               ||
|`<errno.h>`        | 系统错误号             |C标准库|
|`<fcntl.h>`        | 文件控制选项           ||
|`<fenv.h>`         | 浮点数环境             |C标准库|
|`<float.h>`        | 浮点数类型             |C标准库|
|`<fmtmsg.h>`       | 消息显示结构           |XSI可选|
|`<fnmatch.h>`      | 文件名匹配类型         ||
|`<ftw.h>`          | 文件树漫游             |XSI可选|
|`<glob.h>`         | 路径名模式匹配与生成   ||
|`<grp.h>`          | 组文件                 ||
|`<iconv.h>`        | 代码集变换实用程序     ||
|`<inttypes.h>`     | 固定大小的整数类型     |C标准库|
|`<iso646.h>`       | 备选拼写               |C标准库|
|`<langinfo.h>`     | 语言信息常量           ||
|`<libgen.h>`       | 路径名管理函数         |XSI可选|
|`<limits.h>`       | 实现定义的常量         |C标准库|
|`<locale.h>`       | 本地化函数             |C标准库|
|`<math.h>`         | 数学声明               |C标准库|
|`<monetary.h>`     | 货币类型与函数         ||
|`<mqueue.h>`       | 消息队列               |可选|
|`<ndbm.h>`         | 数据库操作             |XSI可选|
|`<net/if.h>`       | 套接字本地接口         ||
|`<netdb.h>`        | 网络数据库操作         ||
|`<netinet/in.h>`   | 因特网地址族           ||
|`<netinet/tcp.h>`  | 传输控制协议定义       ||
|`<nl_types.h>`     | 消息类                 ||
|`<poll.h>`         | `poll()`函数的定义     ||
|`<pthread.h>`      | 线程                   ||
|`<pwd.h>`          | 口令文件               ||
|`<regex.h>`        | 正则表达式             ||
|`<sched.h>`        | 执行调度               ||
|`<search.h>`       | 搜索表                 |XSI可选|
|`<semaphore.h>`    | 信号量                 ||
|`<setjmp.h>`       | 栈环境声明             |C标准库|
|`<signal.h>`       | 信号                   |C标准库|
|`<spawn.h>`        | 实时spawn接口          |可选|
|`<stdarg.h>`       | 处理变长参数列表       |C标准库|
|`<stdbool.h>`      | 布尔类型和值           |C标准库|
|`<stddef.h>`       | 标准类型定义           |C标准库|
|`<stdint.h>`       | 整数类型               |C标准库|
|`<stdio.h>`        | 标准缓冲的输入输出     |C标准库|
|`<stdlib.h>`       | 标准库定义             |C标准库|
|`<string.h>`       | 字符串操作             |C标准库|
|`<strings.h>`      | 字符串操作             ||
|`<stropts.h>`      | STREAMS接口            ||
|`<sys/ipc.h>`      | XSI进程间通信访问结构  |XSI可选|
|`<sys/mman.h>`     | 存储管理声明           ||
|`<sys/msg.h>`      | XSI消息队列            |XSI可选|
|`<sys/resource.h>` | XSI资源操作定义        |XSI可选|
|`<sys/select.h>`   |`select`类型           ||
|`<sys/sem.h>`      | XSI信号量              |XSI可选|
|`<sys/shm.h>`      | XSI共享存储            |XSI可选|
|`<sys/socket.h>`   | 套接字接口             ||
|`<sys/stat.h>`     | 文件状态               ||
|`<sys/statvfs.h>`  | 文件系统信息           ||
|`<sys/time.h>`     | 时间类型               |XSI可选|
|`<sys/times.h>`    | 文件访问和修改时间结构 ||
|`<sys/types.h>`    | 基本系统数据类型       ||
|`<sys/uio.h>`      | 向量IO操作             |XSI可选|
|`<sys/un.h>`       | UNIX域套接字定义       ||
|`<sys/utsname.h>`  | 系统名称结构           ||
|`<sys/wait.h>`     | 进程等待声明           ||
|`<syslog.h>`       | 系统出错日志记录定义   |XSI可选|
|`<tar.h>`          | tar归档值              ||
|`<termios.h>`      | 终端IO                 ||
|`<tgmath.h>`       | 类型泛型宏             |C标准库|
|`<time.h>`         | 时间类型               |C标准库|
|`<trace.h>`        | tracing                ||
|`<ulimit.h>`       | ulimit命令             ||
|`<unistd.h>`       | 标准符号常量和类型     ||
|`<utime.h>`        | 访问和修改时间结构     ||
|`<utmpx.h>`        | 用户账户数据库定义     |XSI可选|
|`<wchar.h>`        | 宽字符处理             |C标准库|
|`<wctype.h>`       | 宽字符分类和映射工具   |C标准库|
|`<wordexp.h>`      | 字扩充类型             ||

[^1]: https://www.systutorials.com/docs/linux/man/1-cpio/


### Signal

```
<signal.h>
```

- T: Abnormal termination of the process.
- A: Abnormal termination of the process with additional actions.
- I: Ignore the signal.
- S: Stop the process.
- C: Continue the process, if it is stopped; otherwise, ignore the signal.

|Signal|Name|Default Action|Description|
|:---|:---|:---|:---|
|SIGABRT    | 异常终止                 |A |Process abort signal.|
|SIGALRM    | 定时器超时               |T |Alarm clock.|
|SIGBUS     | 访问内存对象未定义部分   |A |Access to an undefined portion of a memory object.|
|SIGCHLD    | 子进程终止, 暂停或继续   |I |Child process terminated, stopped, or continued.|
|SIGCONT    | 使暂停进程继续执行       |C |Continue executing, if stopped.|
|SIGFPE     | 算术操作错误             |A |Erroneous arithmetic operation.|
|SIGHUP     | 连接断开                 |T |Hangup.|
|SIGILL     | 非法指令                 |A |Illegal instruction.|
|SIGINT     | 终端中断信号             |T |Terminal interrupt signal.|
|SIGKILL    | 杀死                     |T |Kill (cannot be caught or ignored).|
|SIGPIPE    | 写到无进程读的管道       |T |Write on a pipe with no one to read it.|
|SIGQUIT    | 终端退出信号             |A |Terminal quit signal.|
|SIGSEGV    | 无效内存引用             |A |Invalid memory reference.|
|SIGSTOP    | 停止执行                 |S |Stop executing (cannot be caught or ignored).|
|SIGTERM    | 终止                     |T |Termination signal.|
|SIGTSTP    | 终端停止信号             |S |Terminal stop signal.|
|SIGTTIN    | 后台进程尝试读           |S |Background process attempting read.|
|SIGTTOU    | 后台进程尝试写           |S |Background process attempting write.|
|SIGUSR1    | 用户定义信号1            |T |User-defined signal 1.|
|SIGUSR2    | 用户定义信号2            |T |User-defined signal 2.|
|SIGPOLL    | 可轮询事件               |T |Pollable event.|
|SIGPROF    | 梗概计时器超时           |T |Profiling timer expired.|
|SIGSYS     | 无效系统调用             |A |Bad system call.|
|SIGTRAP    | 跟踪/断点陷阱            |A |Trace/breakpoint trap.|
|SIGURG     | socket上高带宽数据可用   |I |High bandwidth data is available at a socket.|
|SIGVTALRM  | 虚拟定时器超时           |T |Virtual timer expired.|
|SIGXCPU    | 超出CPU时间限制          |A |CPU time limit exceeded.|
|SIGXFSZ    | 超出文件大小限制         |A |File size limit exceeded.|

### async-signal-safe函数

> The Open Group Base Specifications Issue 7, 2018 edition<br/>
> System Interfaces<br/>
> 2.4.3 Signal Actions

|||||
|:---|:---|:---|:---|
|_Exit()             |getppid()           |sendmsg()           |tcgetpgrp()         |
|_exit()             |getsockname()       |sendto()            |tcsendbreak()       |
|abort()             |getsockopt()        |setgid()            |tcsetattr()         |
|accept()            |getuid()            |setpgid()           |tcsetpgrp()         |
|access()            |htonl()             |setsid()            |time()              |
|aio_error()         |htons()             |setsockopt()        |timer_getoverrun()  |
|aio_return()        |kill()              |setuid()            |timer_gettime()     |
|aio_suspend()       |link()              |shutdown()          |timer_settime()     |
|alarm()             |linkat()            |sigaction()         |times()             |
|bind()              |listen()            |sigaddset()         |umask()             |
|cfgetispeed()       |longjmp()           |sigdelset()         |uname()             |
|cfgetospeed()       |lseek()             |sigemptyset()       |unlink()            |
|cfsetispeed()       |lstat()             |sigfillset()        |unlinkat()          |
|cfsetospeed()       |memccpy()           |sigismember()       |utime()             |
|chdir()             |memchr()            |siglongjmp()        |utimensat()         |
|chmod()             |memcmp()            |signal()            |utimes()            |
|chown()             |memcpy()            |sigpause()          |wait()              |
|clock_gettime()     |memmove()           |sigpending()        |waitpid()           |
|close()             |memset()            |sigprocmask()       |wcpcpy()            |
|connect()           |mkdir()             |sigqueue()          |wcpncpy()           |
|creat()             |mkdirat()           |sigset()            |wcscat()            |
|dup()               |mkfifo()            |sigsuspend()        |wcschr()            |
|dup2()              |mkfifoat()          |sleep()             |wcscmp()            |
|execl()             |mknod()             |sockatmark()        |wcscpy()            |
|execle()            |mknodat()           |socket()            |wcscspn()           |
|execv()             |ntohl()             |socketpair()        |wcslen()            |
|execve()            |ntohs()             |stat()              |wcsncat()           |
|faccessat()         |open()              |stpcpy()            |wcsncmp()           |
|fchdir()            |openat()            |stpncpy()           |wcsncpy()           |
|fchmod()            |pause()             |strcat()            |wcsnlen()           |
|fchmodat()          |pipe()              |strchr()            |wcspbrk()           |
|fchown()            |poll()              |strcmp()            |wcsrchr()           |
|fchownat()          |posix_trace_event() |strcpy()            |wcsspn()            |
|fcntl()             |pselect()           |strcspn()           |wcsstr()            |
|fdatasync()         |pthread_kill()      |strlen()            |wcstok()            |
|fexecve()           |pthread_self()      |strncat()           |wmemchr()           |
|ffs()               |pthread_sigmask()   |strncmp()           |wmemcmp()           |
|fork()              |raise()             |strncpy()           |wmemcpy()           |
|fstat()             |read()              |strnlen()           |wmemmove()          |
|fstatat()           |readlink()          |strpbrk()           |wmemset()           |
|fsync()             |readlinkat()        |strrchr()           |write()             |
|ftruncate()         |recv()              |strspn()            ||
|futimens()          |recvfrom()          |strstr()            ||
|getegid()           |recvmsg()           |strtok_r()          ||
|geteuid()           |rename()            |symlink()           ||
|getgid()            |renameat()          |symlinkat()         ||
|getgroups()         |rmdir()             |tcdrain()           ||
|getpeername()       |select()            |tcflow()            ||
|getpgrp()           |sem_post()          |tcflush()           ||
|getpid()            |send()              |tcgetattr()         ||

### Thread Safe函数

> The Open Group Base Specifications Issue 7, 2018 edition<br/>
> System Interfaces<br/>
> 2.9.1 Thread-Safety

All functions defined by this volume of POSIX.1-2017 shall be thread-safe, except that the following functions1 need **not** be thread-safe.

|||||
|:---|:---|:---|:---|
|asctime()           |ftw()               |getutxent()         |putenv()            |
|basename()          |getdate()           |getutxid()          |pututxline()        |
|catgets()           |getenv()            |getutxline()        |rand()              |
|crypt()             |getgrent()          |gmtime()            |readdir()           |
|ctime()             |getgrgid()          |hcreate()           |setenv()            |
|dbm_clearerr()      |getgrnam()          |hdestroy()          |setgrent()          |
|dbm_close()         |gethostent()        |hsearch()           |setkey()            |
|dbm_delete()        |getlogin()          |inet_ntoa()         |setlocale()         |
|dbm_error()         |getnetbyaddr()      |l64a()              |setpwent()          |
|dbm_fetch()         |getnetbyname()      |lgamma()            |setutxent()         |
|dbm_firstkey()      |getnetent()         |lgammaf()           |strerror()          |
|dbm_nextkey()       |getopt()            |lgammal()           |strsignal()         |
|dbm_open()          |getprotobyname()    |localeconv()        |strtok()            |
|dbm_store()         |getprotobynumber()  |localtime()         |system()            |
|dirname()           |getprotoent()       |lrand48()           |ttyname()           |
|dlerror()           |getpwent()          |mblen()             |unsetenv()          |
|drand48()           |getpwnam()          |mbtowc()            |wctomb()            |
|encrypt()           |getpwuid()          |mrand48()           ||
|endgrent()          |getservbyname()     |nftw()              ||
|endpwent()          |getservbyport()     |nl_langinfo()       ||
|endutxent()         |getservent()        |ptsname()           ||

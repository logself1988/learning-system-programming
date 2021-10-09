# Notes of **Linux内核设计与实现** PART 1

### 3 进程管理
#### 3.1 进程

进程是处于执行期的程序, 包含一段可执行程序代码和资源(打开的文件、挂起的信号、内核内部数据、处理器状态、一个或多个具有内存映射的内存地址空间、一个或多个执行线程(thread of execution)).

执行线程(thread)是进程中的活动对象, 拥有一个独立的程序计数器、进程栈和一组进程寄存器.

进程提供了两种虚拟机制: 虚拟处理器和虚拟内存.

相关函数:

- `fork()`: 复制一个现有进程来创建一个全新的进程;
- `exec()`: 创建新的进程;
- `clone()`: 在现代Linux内核中, `fork()`是由`clone()`实现的;
- `exit()`: 退出执行, 终结进程并将其占用的资源释放掉;
- `wait4()`: 查询子进程是否终结.

#### 3.2 进程描述符及任务结构

内核将进程的列表存放在一个双向循环链表(任务队列(task list))中, 链表中每一项是进程描述符`struct task_struct`:

``` c
// include/linux/sched.h

struct task_struct {
  volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
  struct list_head tasks;
	struct task_struct *parent; /* recipient of SIGCHLD, wait4() reports */
  pid_t pid;
  ...
};
```

Linux通过slab分配器分配`struct task_struct`. 只需要在进程内核栈中创建一个`struct thread_info`, 其字段`task`指向实际的`struct task_struct`.

``` c
// arch/x86/include/asm/thread_info.h

struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	__u32			flags;		/* low level flags */
	__u32			status;		/* thread synchronous flags */
	__u32			cpu;		/* current CPU */
	int			preempt_count;	/* 0 => preemptable,
						   <0 => BUG */
	mm_segment_t		addr_limit;
	struct restart_block    restart_block;
	void __user		*sysenter_return;
	int			uaccess_err;
};
```

进程描述符的存放:

- 内核通过一个唯一的PID标识每个进程, 其类型为`pid_t`(`task_struct.pid`);
- 在内核中访问任务需要获得指向其`task_struct`的指针;
- 通过`current`宏查找到当前正在运行进程的进程描述符: x86中通过`current_thread_info()->task`完成.

``` c
// arch/x86/include/asm/thread_info.h

/* how to get the current stack pointer from C */
register unsigned long current_stack_pointer asm("esp") __used;

/* how to get the thread information struct from C */
static inline struct thread_info *current_thread_info(void)
{
	return (struct thread_info *)
		(current_stack_pointer & ~(THREAD_SIZE - 1));
}
```

进程状态(`task_struct.state`):

- `TASK_RUNNING`: 进程可执行, 或者正在执行, 或者在运行队列中等待执行;
- `TASK_INTERRUPTIBLE`: 进程正在睡眠, 等待某些条件的达成. 一旦这些条件达成, 内核将进程状态设置为`TASK_RUNNING`; 也会因为接收到信号而提前被唤醒并准备投入运行;
- `TASK_UNINTERRUPTIBLE`: 与`TASK_INTERRUPTIBLE`类似, 除了接收到信号也不会被唤醒或准备投入运行;
- `__TASK_STOPPED`: 进程停止执行, 没有投入运行也不能投入运行.
- `__TASK_TRACED`: 被其他进程跟踪的进程.

设置当前进程状态: `set_task_state(task, state)`

``` c
// include/linux/sched.h

#define set_task_state(tsk, state_value)		\
	set_mb((tsk)->state, (state_value))
```

进程上下文:

- 当一个程序执行了系统调用或者触发了某个异常, 它就陷入了内核空间; 此时成内核代表进程执行并处于进程上下文中.
- 在内核退出时, 程序恢复在用户空间继续执行, 除非调度器做出了调度更高优先级进程执行的调整.
- 系统调用和异常处理程序是对内核明确定义的接口.

进程家族树:

- Linux中所有进程都是PID为1的init进程的后代.
- 父进程`task_struct.parent`, 子进程`task_struct.children`.
- 通过`task_struct.tasks`便利任意进程.


#### 3.3 进程创建

Unix创建进程的方式:

- `fork()`: 拷贝当前进程创建一个子进程;
- `exec()`: 读取可执行文件并将其载入地址空间开始运行.

Linux `fork()`:

- 使用写时拷贝(copy-on-write)页实现;
- 通过`clone()`系统调用实现`fork()`: `clone()`会调用`do_fork()`.

``` c
// kernel/fork.c

do_fork()
|-- copy_process()
```


#### 3.4 线程在Linux中的实现

Linux对线程和进程并不特别区分, 将线程视为一个与其他进程共享某些资源的进程, 每个线程都拥有自己的`task_struct`.

创建线程时, 在调用`clone()`时传递一些参数标志以指出需要共享的资源:

``` c
// include/linux/sched.h

/*
 * cloning flags:
 */
#define CSIGNAL		0x000000ff	/* signal mask to be sent at exit */
#define CLONE_VM	0x00000100	/* set if VM shared between processes */
#define CLONE_FS	0x00000200	/* set if fs info shared between processes */
#define CLONE_FILES	0x00000400	/* set if open files shared between processes */
...
```

内核线程(kernel thread):

- 独立运行在内核空间的标准进程, 可以被调用被抢占.
- 内核线程只能由其他内核线程创建, 从kthreadd内核进程中衍生出所有新的内核线程;

``` c
// include/linux/kthread.h

struct task_struct *kthread_create()
#define kthread_run(threadfn, data, namefmt, ...) ...
int kthread_stop(struct task_struct *k);
```

#### 3.5 进程终结

进程终结时分开执行:

- 所需的清理工作: `do_exit()`, 此时进程不可运行, 处于`EXIT_ZOMBIE`退出状态;
- 删除进程描述符: `release_task()`.

``` c
// kernel/exit.c

NORET_TYPE void do_exit(long code)
void release_task(struct task_struct * p)
```

孤儿进程:

- 场景: 父进程在子进程之前退出;
- 解决方法: 在当前线程组内给子进程找一个线程作为父亲, 不行的话让init作为父亲.

### 4 进程调度 - TODO

### 5 系统调用
#### 5.1 与内核通信

系统调用在用户空间进程和硬件设备之间添加了一个中间层:

- 为用户空间提供了一种硬件的抽象接口;
- 保证了系统的稳定和安全;
- 保持了进程运行在虚拟系统中的抽象一致性.

在Linux中, 系统调用是用户空间访问内核的唯一手段; 除异常和陷入外, 系统调用是内核唯一的合法入口.

#### 5.2 API、POSIX和C库

Linux尽力与应用编程接口POSIX和SUSv4兼容.

Linux的系统调用作为C库的一部分提供.

#### 5.3 系统调用

要访问系统调用(syscall), 通常通过C库中定义的函数调用来完成.

系统调用号:

``` c
// arch/x86/kernel/syscall_64.c

const sys_call_ptr_t sys_call_table[__NR_syscall_max+1] = {
	/*
	*Smells like a like a compiler bug -- it doesn't work
	*when the & below is removed.
	*/
	[0 ... __NR_syscall_max] = &sys_ni_syscall,
#include <asm/unistd_64.h>
};

// arch/x86/include/asm/unistd_64.h

#define __NR_read				0
__SYSCALL(__NR_read, sys_read)
...

```

系统调用的实现, 以`getpid()`为例:

``` c
// include/linux/syscalls.h

#define SYSCALL_DEFINE0(name)	   asmlinkage long sys_##name(void)
#define SYSCALL_DEFINE1(name, ...) SYSCALL_DEFINEx(1, _##name, __VA_ARGS__)
#define SYSCALL_DEFINE2(name, ...) SYSCALL_DEFINEx(2, _##name, __VA_ARGS__)
#define SYSCALL_DEFINE3(name, ...) SYSCALL_DEFINEx(3, _##name, __VA_ARGS__)
#define SYSCALL_DEFINE4(name, ...) SYSCALL_DEFINEx(4, _##name, __VA_ARGS__)
#define SYSCALL_DEFINE5(name, ...) SYSCALL_DEFINEx(5, _##name, __VA_ARGS__)
#define SYSCALL_DEFINE6(name, ...) SYSCALL_DEFINEx(6, _##name, __VA_ARGS__)

// kernel/timer.c

SYSCALL_DEFINE0(getpid)
{
	return task_tgid_vnr(current);
}
```

#### 5.4 系统调用处理程序

应用程序应该以某种方式通知系统, 告诉内核自己需要执行一个系统调用, 希望系统切换到内核态, 这样内核就可以代表应用程序在内核空间执行系统调用.

通知内核的机制是靠 **软中断** 实现的: 通过引发一个异常来促使系统切换到内核态去执行异常处理程序, 这个异常处理程序实际上就是系统调用处理程序. 在x86中预定义的软中断是中断号128, 通过`int $0x80`指令触发该中断(或`sysenter`指令), 执行异常处理程序`system_call`(见`entry_64.S`).


``` c
// arch/x86/kernel/entry_64.S

/*
 * Register setup:
 * rax  system call number
 * rdi  arg0
 * rcx  return address for syscall/sysret, C arg3
 * rsi  arg1
 * rdx  arg2
 * r10  arg3 	(--> moved to rcx for C)
 * r8   arg4
 * r9   arg5
 * r11  eflags for syscall/sysret, temporary for C
 * r12-r15,rbp,rbx saved by C code, not touched.
 ...
 */
ENTRY(system_call)
...
call *sys_call_table(,%rax,8)  # XXX:	 rip relative
...
END(system_call)
```

#### 5.5 系统调用的实现

实现一个新的Linux系统调用所需的步骤:

- 决定它的用途;
- 确定参数、返回值和错误码;
- 注意可移植性和健壮性.

内核提供了在内核空间与用户空间之间来回拷贝的方法:

- `copy_to_user()`: 向用户空间写入数据;
- `copy_from_user()`: 从用户空间读取数据.

``` c
// arch/alpha/include/asm/uaccess.h

inline long
copy_to_user(void __user *to, const void *from, long n)
{
	return __copy_tofrom_user((__force void *)to, from, n, to);
}

inline long
copy_from_user(void *to, const void __user *from, long n)
{
	return __copy_tofrom_user(to, (__force void *)from, n, from);
}
```

#### 5.6 系统调用上下文

内核在执行系统调用时处于进程上下文. 当系统调用返回时, 控制权仍在`system_call()`中, 它最终会负责切换到用户空间, 并让用户进程继续执行下去.

``` c
// arch/x86/include/asm/unistd_64.h
// kernel/sys.c
// arch/x86/kernel/syscall_table_32.S
```

### 7 中断和中断处理

中断机制: 处理器的速度与外围硬件设备的速度不在一个数量级上, 让硬件在需要的时候向内核发出信号.

#### 7.1 中断

中断是由硬件设备生成的电信号, 直接送入中断控制器的输入引脚中.<br/>
当接收到一个中断后, 中断控制器会给处理器发送一个电信号.<br/>
处理器一经检测到此信号, 便中断自己的当前工作转而处理中断; 此后通知操作系统已经产生中断.

> 中断控制器: 是个电子芯片, 将多路中断管线, 采用复用技术只通过一个和处理器相连接的管线与处理器通信.

每个中断都通过一个唯一的数字标识.

异常(exception)与中断不同, 异常在产生时必须考虑与处理器时钟同步(故异常也成为同步中断).

#### 7.2 中断处理程序

在响应一个特定中断时, 内核会执行一个函数, 该函数称为中断处理程序(interrupt handler)或中断服务例程(interrupt service routine, ISR):

- 对硬件而言, 操作系统能迅速对其中断进行服务非常重要;
- 对系统其他部分而言, 让中断能处理程序在尽可能短的时间内完成运行也同样重要.

#### 7.3 上半部与下半部的对比

中断处理分为:

- 上半部(top half): 中断处理程序接收到一个中断, 立即开始执行, 但只做有严格时限的工作;
- 下半部(bottom half): 能够被允许稍后完成的工作会推迟到下半部去; 此后在合适的实际, 下半部会被开中断执行.

例: 网卡

- 网卡接收到来自网络的数据包时, 通知内核数据包到了;
- 内核通过执行网卡已注册的中断处理程序来做出应答;
- 中断开始执行, 通知硬件拷贝最新的网络数据包到内存, 然后读取网卡更多的数据包;
- 当网络数据包被拷贝到系统内存后, 中断的任务算是完成了, 这时它将控制权交换给系统被中断前原先运行的程序;
- 处理和操作数据包的其他工作在随后的下半部中进行.

#### 7.4 注册中断处理程序

管理硬件的驱动程序通过`request_irq()`函数注册一个中断处理程序, 并激活给定的中断线.

``` c
// include/linux/interrupt.h

typedef irqreturn_t (*irq_handler_t)(int, void *); // irq, dev

int request_irq(
  unsigned int irq,         // 要分配的中断号
  irq_handler_t handler,    // 指向处理这个中断的实际中断处理程序
  unsigned long flags,      // 中断处理程序标志
  const char *name,         // 与中断相关的设备的ASCII文本表示
  void *dev                 // 用于共享中断线
) { ... }
```

- `dev`: 当一个中断处理程序需要释放时, `dev`将提供唯一的标识信息, 以便从共享中断线的诸多中断处理程序中删除指定的哪一个.


卸载驱动程序时, 需要注销相应的中断处理程序, 并释放中断线.

``` c
// kernel/irq/manage.c

void free_irq(unsigned int irq, void *dev_id) { ... }
```


#### 7.5 编写中断处理程序

Linux中的中断处理程序时无须重入的:

- 当一个给定的中断处理程序正在执行时, 相应的中断线在所有处理器上都会被屏蔽掉, 以防止在同一中断线上接收另一个新的中断;
- 通常情况下, 所有其他的中断都是打开的.

例: RTC(Real-Time Clock)驱动程序

``` c
// drivers/char/rtc.c

static irqreturn_t rtc_interrupt(int irq, void *dev_id) { ... }
```

#### 7.6 中断上下文

中断上下文与进程没有关联:

- 不可睡眠: 没有后备进程;
- 不能调用某些函数: 不能使用可睡眠的函数;
- 具有较为严格的时间限制: 中断处理程序必须尽可能的迅速、简洁, 尽量将工作从中断处理程序中分离出来, 放在下半部来执行.

中断栈: 中断处理程序拥有自己的栈, 每个处理器一个, 大小为一页(从版本2.6).

#### 7.7 中断处理机制的实现

Linux中中断处理系统的实现依赖于处理器、所使用的的中断控制器类型、体系结构的设计.

中断从硬件到内核的路由:

(1) 硬件产生中断, 通过总线将电信号发送给中断控制器;<br/>
(2) 如果中断线是激活的, 中断控制器将中断发往处理器(给处理器的特定管脚发送一个信号);<br/>
(3) 除非在处理器上禁止该中断, 否则处理器会立即停止它正在做的事情, 关闭中断系统, 然后跳到内存中预定义的位置开始执行那里的代码; 这个预定义的位置还是内核设置的中断处理程序的入口点;<br/>
对每个中断线, 处理器都会跳到对应的一个唯一的位置, 这样内核可知所接收中断的IRQ号;<br/>
初始入口点在栈中保存这个IRQ号, 并存放当前寄存器的值;<br/>
(4) 内核调用函数`do_IRQ()`, 计算出中断号后, 对所接收的中断进行应答, 禁止这条线上的中断传递; <br/>
(4.1) 如果这条中断线上有一个有效的处理程序, 且该程序已启动但没有执行, 调用`handle_IRQ_event()`来运行为这条中断线安装的冲段处理程序;<br/>
(4.2) 如果没有, 调用`ret_from_intr()`返回内核运行中断的代码.

``` c
// arch/x86/kernel/entry_64.S

	interrupt do_IRQ - ???

ret_from_intr:

// include/linux/irq.h
// kernel/irq/handle.c

irqreturn_t handle_IRQ_event(unsigned int irq, struct irqaction *action) { ... }

// arch/x86/kernel/irq.c

unsigned int do_IRQ(struct pt_regs *regs) { ... }

```


#### 7.8 `/proc/interrupts`

`/proc/interrupts`文件存放系统中与中断相关的统计信息.

#### 7.9 中断控制

Linux内核提供了一组接口用于操作机器上的中断状态, 提供了能力:

- 禁止当前处理器的中断系统;
- 屏蔽掉整个机器的一条中断线的能力.

控制中断系统的原因是需要提供同步:

- 通过禁止中断, 可以确保某个中断处理程序不会抢占当前的代码;
- 禁止中断可以禁止内核抢占.


接口:

(1) 禁止和激活中断: 当前处理器

- `local_irq_disable()`: 禁止本地中断传递;
- `local_irq_enable()`: 激活本地中断传递;
- `local_irq_save()`: 保存本地中断传递的当前状态, 然后禁止本地中断传递;
- `local_irq_restore()`: 恢复本地中断传递到给定的状态;

(2) 禁止指定中断线: 整个系统中一条特定的中断线

- `disable_irq()`: 禁止给定中断线, 并确保改函数返回之前在该中断线上没有处理程序在运行;
- `disable_irq_nosync()`: 禁止给定中断线;
- `enable_irq()`: 激活给定中断线;
- `synchronize_irq()`: 等待一个特定的中断处理程序的退出.

(3) 中断系统的状态

- `irqs_disabled()`: 如果本地处理器上的中断系统被禁止则返回非0, 否则返回0;
- `in_interrupt()`: 如果内核在中断上下文中则返回非0, 如果在进程上下文中则返回0;
- `in_irq()`: 如果内核当前正在执行中断处理程序则返回非0, 否则返回0..

``` c
// arch/x86/include/asm/system.h

#include <linux/irqflags.h>

// include/linux/irqflags.h

#include <asm/irqflags.h>
#define local_irq_enable() ...
#define local_irq_disable() ...
#define local_irq_save(flags) ...
#define local_irq_restore(flags) ...
#define irqs_disabled()	...

// arch/x86/include/asm/irqflags.h


// include/linux/interrupt.h

void disable_irq_nosync(unsigned int irq);
void disable_irq(unsigned int irq);
void enable_irq(unsigned int irq);

// include/linux/hardirq.h

#define in_irq() ...
#define in_interrupt() ...
void synchronize_irq(unsigned int irq);
```

### 8 下半部和推后执行的工作

#### 8.1 下半部

下半部(bottom halves)的任务是执行与中断处理密切相关但中断处理程序本身不执行的工作.

上半部与下半部划分工作的提示:

- 如果任务对时间非常敏感, 将其放在中断处理程序中执行;
- 如果任务和硬件相关, 将其放在中断处理程序汇中执行;
- 如果任务要保证不被其他中断(可以是相同的中断)打断, 将其放在中断处理程序中执行;
- 其他所有任务, 考虑放置在下半部执行.

下半部并不需要指明一个确切时间, 只要把这些任务推迟一点, 让它们在系统不太繁忙并且中断恢复后执行.

在版本2.6中, 内核提供了三种不同形式的下半部实现机制:

- 软中断: 一组静态定义的下半部接口, 可以在所有处理器上同时执行; 版本2.3引入;
- tasklet: 基于软中断实现的动态创建的下半部实现机制, 类型相同的tasklet不能同时执行; 版本2.3引入;
- 工作队列: 先对要推后执行的工作排队, 稍后在进程上下文中执行它们; 版本2.5引入;

#### 8.2 软中断

软中断是在编译期间静态分配的, 由`softirq_action`结构体表示, 被注册的软中断在`softirq_vec`数组中:

``` c
// include/linux/interrupt.h

struct softirq_action
{
	void	(*action)(struct softirq_action *);
};

// kernel/softirq.c

static struct softirq_action softirq_vec[NR_SOFTIRQS];
```

- 一个软中断不会抢占另外一个软中断, 唯一可以抢占软中断的是中断处理程序;
- 其他的软中断可以在其他处理器上同时执行.

软中断处理程序`action`的函数原型:

``` c
void softirq_handler(struct softirq_action *)
```


执行软中断:

- 一个注册的软中断必须在被标记后才会执行, 这称为触发软中断(raising the softirq).
- 通常中断处理程序会在返回前标记它的软中断, 使其在稍后合适的时刻被执行.
- 在这些位置, 待处理的软中断会被检查和执行:<br/>
(1) 从一个硬件中断代码出返回时;<br/>
(2) 在`ksoftirqd`内核线程中;<br/>
(3) 在哪些显式检查和执行待处理的软中断的代码中, 例如网络子系统中.<br/>
- 软中断在`do_softirq()`中执行:

``` c
// kernel/softirq.c

void do_softirq(void)
{
	__u32 pending;
	unsigned long flags;

	if (in_interrupt())
		return;

	local_irq_save(flags);

	pending = local_softirq_pending();

	if (pending)
		__do_softirq();

	local_irq_restore(flags);
}

void __do_softirq(void)
{
	struct softirq_action *h;
	__u32 pending;
	int max_restart = MAX_SOFTIRQ_RESTART;
	int cpu;

	pending = local_softirq_pending();       // 待处理软中断的32位位图

	cpu = smp_processor_id();
restart:
	h = softirq_vec;

	do {
		if (pending & 1) {
      // ...
			h->action(h);
      // ...
		}
		h++;
		pending >>= 1;
	} while (pending);

  pending = local_softirq_pending();
	if (pending && --max_restart)
		goto restart;

	if (pending)
		wakeup_softirqd();
  // ...
}
```

使用软中断:

- 软中断保留给系统中对时间要求最严格以及最重要的下半部使用, 例如直接使用软中断的两个子系统网络和SCSI.

例: 网络子系统的软中断

``` c
// include/linux/interrupt.h

enum
{
	HI_SOFTIRQ=0,
	TIMER_SOFTIRQ,
	NET_TX_SOFTIRQ,          // 发送网络数据包
	NET_RX_SOFTIRQ,          // 接收网络数据包
	BLOCK_SOFTIRQ,
	BLOCK_IOPOLL_SOFTIRQ,
	TASKLET_SOFTIRQ,
	SCHED_SOFTIRQ,
	HRTIMER_SOFTIRQ,
	RCU_SOFTIRQ,	/* Preferable RCU should always be the last softirq */

	NR_SOFTIRQS
};

// net/core/dev.c

static int __init net_dev_init(void)
{
  // ...
  open_softirq(NET_TX_SOFTIRQ, net_tx_action);  // 注册软中断处理程序
	open_softirq(NET_RX_SOFTIRQ, net_rx_action);
  // ...
}

static void net_tx_action(struct softirq_action *h) { ... }
static void net_rx_action(struct softirq_action *h) { ... }


// kernel/softirq.c

void raise_softirq(unsigned int nr) { ... }                 // 触发软中断
inline void raise_softirq_irqoff(unsigned int nr) { ... }
```

#### 8.3 tasklet

tasklet由两类软中断代表: `HI_SOFTIRQ`和`TASKLET_SOFTIRQ`; 用`tasklet_struct`结构体表示:

``` c
// include/linux/interrupt.h

struct tasklet_struct
{
	struct tasklet_struct *next;
	unsigned long state;             // TASKLET_STATE_SCHED, TASKLET_STATE_RUN
	atomic_t count;                  // 引用计数器: 为0时被激活; 不为0时被禁止
	void (*func)(unsigned long);     // tasklet处理函数
	unsigned long data;              // 给tasklet处理函数的参数
};

static inline void tasklet_schedule(struct tasklet_struct *t) { ... }     // 调度普通tasklet
static inline void tasklet_hi_schedule(struct tasklet_struct *t) { ... }  // 调度高优先级的tasklet

// kernel/softirq.c

struct tasklet_head
{
	struct tasklet_struct *head;
	struct tasklet_struct **tail;
};

static DEFINE_PER_CPU(struct tasklet_head, tasklet_vec);    // 普通tasklet
static DEFINE_PER_CPU(struct tasklet_head, tasklet_hi_vec); // 高优先级的tasklet
```

使用tasklet:

``` c
// include/linux/interrupt.h

// 静态创建
#define DECLARE_TASKLET(name, func, data) ...
#define DECLARE_TASKLET_DISABLED(name, func, data) ...
// 动态创建
void tasklet_init(struct tasklet_struct *t,
			 void (*func)(unsigned long), unsigned long data);

// 禁止
static inline void tasklet_disable(struct tasklet_struct *t) { ... }
// 激活
static inline void tasklet_enable(struct tasklet_struct *t) { ... }
```

`ksoftirqd`: 辅助处理软中断的内核线程

``` c
// kernel/softirq.c

static DEFINE_PER_CPU(struct task_struct *, ksoftirqd);
```

#### 8.4 工作队列

工作队列(work queue)可以将工作推后, 交由一个内核线程去执行:

- 这个下半部总是会在进程上下文中执行.
- 允许重新调度和睡眠.

工作队列子系统是一个用于创建内核线程的接口, 这些内核线程称为工作者线程(worker thread), 它们负责执行由内核其他部分排到队列中的任务. 缺省的工作者线程为`events`.


``` c
// include/linux/workqueue.h

struct work_struct {                    // 工作  
	atomic_long_t data;
	struct list_head entry;
	work_func_t func;
};

// kernel/workqueue.c

struct workqueue_struct {               // 工作队列
	struct cpu_workqueue_struct *cpu_wq;
	struct list_head list;
	const char *name;
	int singlethread;
	int freezeable;		/* Freeze threads during suspend */
	int rt;
};

struct cpu_workqueue_struct {           // 每CPU上工作队列

	spinlock_t lock;

	struct list_head worklist;
	wait_queue_head_t more_work;
	struct work_struct *current_work;

	struct workqueue_struct *wq;         // 关联的工作队列
	struct task_struct *thread;          // 关联的线程
};


static int worker_thread(void *__cwq) // 工作者线程的实现函数
{
	struct cpu_workqueue_struct *cwq = __cwq;
	DEFINE_WAIT(wait);

	for (;;) {
		prepare_to_wait(&cwq->more_work, &wait, TASK_INTERRUPTIBLE);
		if (!freezing(current) &&
		    !kthread_should_stop() &&
		    list_empty(&cwq->worklist))
			schedule();
		finish_wait(&cwq->more_work, &wait);

		try_to_freeze();

		if (kthread_should_stop())
			break;

		run_workqueue(cwq);
	}

	return 0;
}
```

#### 8.5 下半部机制的选择

比较:

- 软中断: 在中断上下文中执行, 没有顺序执行保障;
- tasklet: 在中断上下文中执行, 同类型不能同时执行;
- 工作队列: 在进程上下文中执行, 和进程上下文一样被调度;

选择:

- 是否需要一个可调度的实体来执行需要推后完成的工作?
- 是否需要睡眠, 如果需要选择工作队列;
- 否则最要用tasklet;
- 如果需要专注于性能, 则考虑软中断.

#### 8.6 在下半部之间加锁

在使用下半部机制时, 即使是在一个单处理器的系统上, 避免共享数据被同时访问也是至关重要的.

不同类型的tasklet共享同一数据时, 需要争取使用锁机制.

为了本地和SMP的保护并且防止死锁的出现:

- 如果进程上下文和一个下半部共享数据, 在访问这些数据之前, 需要禁止下半部的处理并得到锁的使用权;
- 如果中断上下文和一个下半部共享数据, 在访问数据之前, 需要禁止中断下半部并得到锁的使用权.

任何在工作队列中被共享的数据也需要使用锁机制.

#### 8.7 禁止下半部

一般先得到一个锁后再禁止下半部的处理.

``` c
// kernel/softirq.c

void local_bh_disable(void) { ... }   // 禁止本地处理器的软中断和tasklet的处理
void local_bh_enable(void) { ... }    // 激活本地处理器的软中断和tasklet的处理
```

上面的两个函数不能禁止工作队列的执行.


### 9 内核同步介绍

#### 9.1 临界区和竞争条件

临界区: 访问和操作共享数据的代码段.

竞争条件(race condition): 为避免在临界区中并发访问, 必须保证这些代码原子的执行; 如果两个执行线程都有可能处于同一个临街区中同时执行, 称这种情况是竞争条件.

同步(synchronization): 避免并发和放置竞争条件称为同步.

#### 9.2 加锁

锁是采用原子操作实现的, 原子操作不存在竞争, 其实现是与具体的体系结构密切相关的(测试和设置指令).

伪并发执行:

- 用户空间中用户程序会被调度程序抢占和重新调度: 一个程序正处于临界区中被非自愿的抢占了, 如果新调度的进程随后也进入同一个临界区, 前后两个进程相互之间会产生竞争;
- 信号处理是异步发生的, 单线程的多个进程共享文件, 或者在一个程序内部处理信号, 也有可能产生竞争条件;
- 这种类型的并发操作, 两者并不是真的同时发生, 而是相互交叉进行, 称为伪并发执行.

真并发执行: 如果机器支持对称多处理器, 则两个进程就可以真正的在临界区中同时执行.

内核中造成并发执行的原因:

- 中断;
- 软中断和tasklet;
- 内核抢占;
- 睡眠及与用户空间的同步;
- 对称多处理.

编写内核代码时需要回答的问题:

- 这个数据是不是全局的? 除了当前线程外, 其他线程能不能访问它?
- 这个数据会不会在进程上下文和中断上下文中共享? 它是不是要在两个不同的中断处理程序中共享?
- 进程在访问数据时可不可能被抢占? 新调度的程序会不会访问同一数据?
- 当前进程是不是会睡眠(阻塞)在某些资源上? 如果是, 它会让共享数据处于何种状态?
- 怎样防止数据失控?
- 如果这个函数又在另一个处理器上被调度将会发生什么?
- 如何确保代码原理并发威胁呢?

#### 9.3 死锁

死锁产生的条件:

- 一个或多个执行线程需要访问一个或多个资源;
- 每个线程都在等待其中的一个资源, 但所有的线程都已经被占用了;
- 所有线程都在相互等待, 但它们永远不会释放已经占有的资源.

自死锁:

- 一个执行线程试图去获取一个自己已经持有的锁, 它将不得不等待锁被释放;
- 但它正忙于等待这个锁, 所以自己永远也不会有机会释放锁.

递归锁: 可以被一个执行线程多次请求. (Linux没有提供)

ABBA死锁: 考虑两个线程和两把锁, 如果没有线程都持有一把其他线程需要获取的锁, 那么所有线程都将阻塞的等待它们希望获取的锁重新可用.

死锁避免的简单规则:

- 按顺序加锁: 使用嵌套的锁时必须保证以相同的顺序获取锁;
- 防止发生饥饿: 这个代码的执行是否会一定结束? 如果一个事件不发生, 这里需要一直等待下去吗?
- 不要重复请求同一个锁;
- 设计应力求简单, 越复杂的加锁方案越有可能造成死锁.

#### 9.4 争用和扩展性

锁的争用(lock contention): 当锁正在被占用时, 有其他线程试图获取该锁.

扩展性(scalability): 对系统可扩展程序的一个度量.

### 10 内核同步方法

#### 10.1 原子操作

内核提供了两组原子操作接口:

- 整数操作: 32位整数`atomic_t`, 64位整数`atomic64_t`;
- 单独的位操作: 是对普通内存地址进行操作的, 参数是一个指针和一个位号.

``` c
// include/linux/types.h

typedef struct {
	volatile int counter;
} atomic_t;

typedef struct {
	volatile long counter;
} atomic64_t;

// arch/x86/include/asm/atomic.h

#define ATOMIC_INIT(i)	{ (i) }
int atomic_read(const atomic_t *v) { ... }
void atomic_set(atomic_t *v, int i) { ... }
void atomic_add(int i, atomic_t *v) { ... }
void atomic_sub(int i, atomic_t *v) { ... }
int atomic_sub_and_test(int i, atomic_t *v) { ... }
void atomic_inc(atomic_t *v) { ... }
void atomic_dec(atomic_t *v) { ... }
int atomic_dec_and_test(atomic_t *v) { ... }
int atomic_inc_and_test(atomic_t *v) { ... }
int atomic_add_negative(int i, atomic_t *v) { ... }
int atomic_add_return(int i, atomic_t *v) { ... }
int atomic_sub_return(int i, atomic_t *v) { ... }
int atomic_cmpxchg(atomic_t *v, int old, int new) { ... }
int atomic_xchg(atomic_t *v, int new) { ... }
int atomic_add_unless(atomic_t *v, int a, int u) { ... }

// arch/x86/include/asm/atomic64_64.h

long atomic64_read(const atomic64_t *v) { ... }
void atomic64_set(atomic64_t *v, long i) { ... }
void atomic64_add(long i, atomic64_t *v) { ... }
void atomic64_sub(long i, atomic64_t *v) { ... }
int atomic64_sub_and_test(long i, atomic64_t *v) { ... }
void atomic64_inc(atomic64_t *v) { ... }
void atomic64_dec(atomic64_t *v) { ... }
int atomic64_dec_and_test(atomic64_t *v) { ... }
int atomic64_inc_and_test(atomic64_t *v) { ... }
int atomic64_add_negative(long i, atomic64_t *v) { ... }
long atomic64_add_return(long i, atomic64_t *v) { ... }
long atomic64_sub_return(long i, atomic64_t *v) { ... }
long atomic64_cmpxchg(atomic64_t *v, long old, long new) { ... }
long atomic64_xchg(atomic64_t *v, long new) { ... }
int atomic64_add_unless(atomic64_t *v, long a, long u) { ... }

// arch/x86/include/asm/bitops.h

void set_bit(unsigned int nr, volatile unsigned long *addr) { ... }
void clear_bit(int nr, volatile unsigned long *addr) { ... }
void change_bit(int nr, volatile unsigned long *addr) { ... }
int test_and_set_bit(int nr, volatile unsigned long *addr) { ... }
int test_and_clear_bit(int nr, volatile unsigned long *addr) { ... }
int test_and_change_bit(int nr, volatile unsigned long *addr) { ... }
int variable_test_bit(int nr, volatile const unsigned long *addr) { ... }
#define test_bit(nr, addr) ...
```

#### 10.2 自旋锁

自旋锁(spin lock):

- 自旋锁最多只能被一个可执行线程持有;
- 如果一个执行线程试图获取一个被已经持有的自旋锁, 那么该线程会一直执行忙循环-旋转-等待锁重新可用;
- 要是锁未被争用, 请求锁的执行线程便能立刻获取它, 继续执行.
- 初衷: 在短期内进行轻量级加锁.


``` c
// include/linux/spinlock_types.h

typedef struct spinlock {
	union {
		struct raw_spinlock rlock;
    // ...
	};
} spinlock_t;

typedef struct raw_spinlock {
	arch_spinlock_t raw_lock;
  // ...
} raw_spinlock_t;

#define DEFINE_SPINLOCK(x) ...

// include/linux/spinlock.h

#define spin_lock_init(_lock) ...
void spin_lock(spinlock_t *lock)
void spin_lock_bh(spinlock_t *lock)
int spin_trylock(spinlock_t *lock)
#define spin_lock_nested(lock, subclass) ...
#define spin_lock_nest_lock(lock, nest_lock) ...
void spin_lock_irq(spinlock_t *lock)
#define spin_lock_irqsave(lock, flags) ...
#define spin_lock_irqsave_nested(lock, flags, subclass) ...
void spin_unlock(spinlock_t *lock)
void spin_unlock_bh(spinlock_t *lock)
void spin_unlock_irq(spinlock_t *lock)
void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
int spin_trylock_bh(spinlock_t *lock)
int spin_trylock_irq(spinlock_t *lock)
#define spin_trylock_irqsave(lock, flags) ...
void spin_unlock_wait(spinlock_t *lock)
int spin_is_locked(spinlock_t *lock)
int spin_is_contended(spinlock_t *lock)
int spin_can_lock(spinlock_t *lock)
void assert_spin_locked(spinlock_t *lock)

// arch/x86/include/asm/spinlock_types.h

typedef struct arch_spinlock {
	unsigned int slock;
} arch_spinlock_t;

// arch/x86/include/asm/spinlock.h

arch_*(...)
```

#### 10.3 读-写自旋锁


为读和写分别提供了不同的锁:

- 一个或多个读任务可以并发的持有读者锁;
- 用于写的锁最多只能被一个写任务持有, 而且此时不能有并发的读操作.

``` c
// include/linux/rwlock_types.h

typedef struct {
	arch_rwlock_t raw_lock;
} rwlock_t;

#define DEFINE_RWLOCK(x) ...

// include/linux/rwlock.h

#define read_can_lock(rwlock) ...
#define read_trylock(lock) ...
#define read_lock(lock) ...
#define read_lock_irqsave(lock, flags) ...
#define read_lock_irqsave(lock, flags) ...
#define read_lock_irq(lock) ...
#define read_lock_bh(lock) ...
#define read_unlock(lock) ...
#define read_unlock_irq(lock) ...
#define read_unlock_irqrestore(lock, flags) ...
#define read_unlock_bh(lock) ...

#define write_can_lock(rwlock) ...
#define write_trylock(lock) ...
#define write_lock(lock) ...
#define write_lock_irqsave(lock, flags) ...
#define write_lock_irqsave(lock, flags) ...
#define write_lock_irq(lock) ...
#define write_lock_bh(lock) ...
#define write_unlock(lock) ...
#define write_unlock_irq(lock) ...
#define write_unlock_irqrestore(lock, flags) ...
#define write_unlock_bh(lock) ...
#define write_trylock_irqsave(lock, flags) ...

// arch/x86/include/asm/rwlock.h

/* Actual code is in asm/spinlock.h or in arch/x86/lib/rwlock.S */
```


#### 10.4 信号量

Linux中的信号量是一种睡眠锁:

- 如果有一个任务试图获取一个已经被占用的信号量时, 信号量会将其推进一个等待队列, 然后让其睡眠; 这时处理器重获自有, 从而可以去执行其他代码;
- 当持有的信号量被释放后, 处于等待队里中的那个任务将被唤醒, 并获得该信号量.
- 适用于锁会被长时间持有的情况;
- 只能在进程上下文中获取信号量锁: 因执行线程在锁被争用时会睡眠;
- 可以在持有信号量时去睡眠;
- 占用信号量的同时不能占用自旋锁: 等待信号时可能会睡眠.


计数信号量(couting semaphore): 信号量同时允许任意数量的锁持有者, 这个数量称为使用者数量(usage count).

二值信号量/互斥信号量: 信号量在一个时刻只允许一个锁持有者.

两个基本操作:

- `down()`: 对信号量计数减一来请求获取信号量, 如果结果是非负数, 则获得信号量锁; 所有结果是负数, 任务会被放入等待队列;
- `up()`: 当临界区中的操作完成后, 用来释放信号量, 会增加信号量的计数值; 如果该信号量上的等待队列不为空, 那么处于队列中等待的任务在被唤醒的同时会获得该信号量.


``` c
// include/linux/semaphore.h

struct semaphore {
	spinlock_t		lock;
	unsigned int		count;
	struct list_head	wait_list;
};

#define DECLARE_MUTEX(name) ...
void sema_init(struct semaphore *sem, int val) { ... }
#define init_MUTEX(sem) ...
#define init_MUTEX_LOCKED(sem) ...

void down(struct semaphore *sem);
int down_interruptible(struct semaphore *sem);
int down_killable(struct semaphore *sem);
int down_trylock(struct semaphore *sem);
int down_timeout(struct semaphore *sem, long jiffies);
void up(struct semaphore *sem);
```

#### 10.5 读-写信号量

信号量也可以区分读-写访问:

``` c
// include/linux/rwsem.h

struct rw_semaphore;

void down_read(struct rw_semaphore *sem);
int down_read_trylock(struct rw_semaphore *sem);
void down_write(struct rw_semaphore *sem);
int down_write_trylock(struct rw_semaphore *sem);
void up_read(struct rw_semaphore *sem);
void up_write(struct rw_semaphore *sem);
void downgrade_write(struct rw_semaphore *sem);

void down_read_nested(struct rw_semaphore *sem, int subclass);
void down_write_nested(struct rw_semaphore *sem, int subclass);
void down_read_non_owner(struct rw_semaphore *sem);
void up_read_non_owner(struct rw_semaphore *sem);

// arch/x86/include/asm/rwsem.h

struct rw_semaphore {
	rwsem_count_t		count;
	spinlock_t		wait_lock;
	struct list_head	wait_list;
};

#define DECLARE_RWSEM(name)	 ...
#define init_rwsem(sem)	...

```

#### 10.6 互斥体

互斥体(mutext): 任何可以睡眠的强制互斥锁, 比如使用计数是1的信号量. 与信号量相比, 互斥体有更多的受限性.

``` c
// include/linux/mutex.h

struct mutex {
	/* 1: unlocked, 0: locked, negative: locked, possible waiters */
	atomic_t		count;
	spinlock_t		wait_lock;
	struct list_head	wait_list;
};

# define mutex_init(mutex) ...
# define mutex_destroy(mutex) ...

int mutex_is_locked(struct mutex *lock) { ... }
void mutex_lock(struct mutex *lock);
int mutex_lock_interruptible(struct mutex *lock);
int mutex_lock_killable(struct mutex *lock);
# define mutex_lock_nested(lock, subclass) ...
# define mutex_lock_interruptible_nested(lock, subclass) ...
# define mutex_lock_killable_nested(lock, subclass) ...
int mutex_trylock(struct mutex *lock);
void mutex_unlock(struct mutex *lock);
int atomic_dec_and_mutex_lock(atomic_t *cnt, struct mutex *lock);
```

#### 10.7 完成变量

完成变量(completion variable): 两个任务同步的简单方法, 一个任务执行一些工作时, 另一个任务在完成变量上等待, 当这个任务完成后会使用完成变量去唤醒在等待的任务.

``` c
// include/linux/completion.h

struct completion {
	unsigned int done;
	wait_queue_head_t wait;
};

#define DECLARE_COMPLETION(work) ...
void init_completion(struct completion *x) { ... }

void wait_for_completion(struct completion *);
int wait_for_completion_interruptible(struct completion *x);
int wait_for_completion_killable(struct completion *x);
unsigned long wait_for_completion_timeout(
  struct completion *x, unsigned long timeout);
unsigned long wait_for_completion_interruptible_timeout(
  struct completion *x, unsigned long timeout);
bool try_wait_for_completion(struct completion *x);
bool completion_done(struct completion *x);

void complete(struct completion *);
void complete_all(struct completion *);
```

#### 10.8 BKL: 大内核锁

BKL是一个全局自旋锁, 是为了方便实现从Linux最初的SMP过渡到细粒度的加锁机制.

#### 10.9 seq锁

seq锁:

- 版本2.6引入, 用于读写共享数据;
- 实现依赖一个序列计数器, 写入时会得到一个锁并且序列值会增加; 在读取数据之前和之后序列号都被读取, 如果读取的序列号值相同, 则说明在读操作进行的过程中没有被写操作打断过;
- 锁的初值是0, 写锁会使值成为奇数, 释放后变为偶数. 如果读取的值是偶数, 则说明写操作没有发生.
- 适用于读者很多写者很少, 且不允许读者让写者饥饿的场景.


``` c
// include/linux/seqlock.h

typedef struct {
	unsigned sequence;
	spinlock_t lock;
} seqlock_t;

void write_seqlock(seqlock_t *sl) { ... }
void write_sequnlock(seqlock_t *sl) { ... }
int write_tryseqlock(seqlock_t *sl) { ... }

unsigned read_seqbegin(const seqlock_t *sl) { ... }
int read_seqretry(const seqlock_t *sl, unsigned start) { ... }
```

#### 10.10 禁止抢占

内核是抢占性的, 内核中的进程在任何时刻都可能停下来以便另一个具有更高优先权的进程运行, 这意味着一个任务与被抢占的任务可能会在同一个临界区内运行. 为避免这种情况, 内核抢占代码使用自旋锁作为非抢占区域的标记: 如果一个自旋锁被持有, 内核变不能进行抢占.

禁止内核抢占:

- `preempt_disable()`: 禁止内核抢占, 可以嵌套调用, 每次调用都必须有一个相应的`preempt_enable()`调用;
- 当最后一个`preempt_enable()`被调用后, 内核抢占才重新启用.

``` c
// include/linux/preempt.h

#define preempt_disable() ...
#define preempt_enable_no_resched() ...
#define preempt_enable() ...
#define preempt_count()	(current_thread_info()->preempt_count)
```


``` c
// include/linux/smp.h

#define get_cpu()		({ preempt_disable(); smp_processor_id(); })
#define put_cpu()		preempt_enable()
```

对每个处理器上独立的变量, 可能就不需要锁:

``` c
int cpu;
cpu = get_cpu();
// 对每个处理器的数据进行操作
put_cpu();
```

#### 10.11 顺序和屏障

顺序:

- 当处理多处理器之间或硬件设备之间的同步问题时, 有时需要在程序代码中以指定的顺序发出读内存和写内存指令.
- 编译器和处理器为了提高效率, 可能会对读和写重新排序.

屏障(barrier):

- 体系结构提供了机器指令来确保顺序要求;
- 可以指示编译器不要对给定点周围的指令进行重排序.


``` c
// arch/x86/include/asm/system.h

#ifdef CONFIG_X86_32
#define mb() alternative("lock; addl $0,0(%%esp)", "mfence", X86_FEATURE_XMM2)
#define rmb() alternative("lock; addl $0,0(%%esp)", "lfence", X86_FEATURE_XMM2)
#define wmb() alternative("lock; addl $0,0(%%esp)", "sfence", X86_FEATURE_XMM)
#else
#define mb() 	asm volatile("mfence":::"memory")
#define rmb()	asm volatile("lfence":::"memory")
#define wmb()	asm volatile("sfence" ::: "memory")
#endif
#define read_barrier_depends()	do { } while (0)

#define smp_mb()	mb()
#ifdef CONFIG_X86_PPRO_FENCE
#define smp_rmb()	rmb()
#else
#define smp_rmb()	barrier()
#endif
#ifdef CONFIG_X86_OOSTORE
#define smp_wmb() 	wmb()
#else
#define smp_wmb()	barrier()
#endif
#define smp_read_barrier_depends()	read_barrier_depends()

// include/linux/compiler.h

#define barrier() __memory_barrier()

// include/linux/compiler-gcc.h

#define barrier() __asm__ __volatile__("": : :"memory")
```

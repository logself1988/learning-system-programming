# Notes of **Linux内核设计与实现**


|时间|内容|
|:---|:---|
|20190513|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

- 中断
- 抢占
- SMP: symmetrical multirocessing/shared-memory multiprocessing, 对称多处理. https://en.wikipedia.org/wiki/Symmetric_multiprocessing
- SCSI: Small Computer System Interface,  a set of standards for physically connecting and transferring data between computers and peripheral devices. https://en.wikipedia.org/wiki/SCSI

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

基于Linux 2.6.34内核版本, 提供足够多的关于Linux内核设计与实现的信息.

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1 Linux内核简介

> skip

### 2 从内核出发
#### 2.1 获取内核源码
#### 2.2 内核源码树

```
├── Documentation     内核源码文档
├── arch              特定体系结构的源码
├── block             块设备I/O层
├── crypto            加密API
├── drivers           设备驱动程序
├── firmware          使用某些驱动程序而需要的设备固件
├── fs                VFS和各种文件系统
├── include           内核头文件
├── init              内核引导和初始化
├── ipc               进程间通信代码
├── kernel            核心子系统, 例如调度程序等
├── lib               通用内核函数
├── mm                内存管理子系统和VM
├── net               网络子系统
├── samples           示例代码
├── scripts           编译内核所用的脚本
├── security          Linux安全模块
├── sound             语音子系统
├── tools             在Linux开发中有用的工具
├── usr               早期用户空间代码(initramfs)
└── virt              虚拟化基础结构
```

#### 2.3 编译内核
#### 2.4 内核开发的特点

与在用户空间内应用程序的开发的差异:

- 内核编程时不能访问C库和标准的C头文件;
- 内核编程时必须使用GNU C;
- 内核编程时缺乏像用户空间那样的内存保护机制;
- 内核编程时难以执行浮点运算;
- 内核给每个内核进程一个很小的定长堆栈;
- 由于内核支持异步中断、抢占和SMP, 必须时刻注意同步与并发;
- 需要考虑可移植性.

### [> 3 进程管理](/kernel/kernel-dev/kernel-dev1/#3)
### [> 4 进程调度](/kernel/kernel-dev/kernel-dev1/#4)
### [> 5 系统调用](/kernel/kernel-dev/kernel-dev1/#5)

### 6 内核数据结构
#### 6.1 链表

环形双向链表:

``` c
// include/linux/list.h

struct list_head {
	struct list_head *next, *prev;
};
```

由结构成员定位父结构:

``` c
// include/linux/kernel.h

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

// include/linux/list.h

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
```

(1) 定义链表

``` c
struct fox {
  unsigned long tail_length;
  unsigned long weight;
  bool is_fantastic;
  struct list_head list;      /* 所有fox结构体形成链表 */
}
```

运行时初始化链表:

``` c
struct fox *red_fox;
red_fox = kmalloc(sieof(*ref_fox), GFP_KERNEL);
red_fox->tail_length = 40;
red_fox->weight = 6;
red_fox->is_fantastic = false;
INIT_LIST_HEAD(&ref_fox->list);
```

在编译器静态创建:

``` c
struct fox red_fox = {
  .tail_length = 40,
  .weight = 6,
  .list = LIST_HEAD_INIT(red_fox.list),
};
```

链表头:

``` c
static LIST_HEAD(fox_list);   /* 定义并初始化了一个名为fox_list的链表 */
```

(2) 操作链表

- `list_add()`: 向链表中添加一个节点;
- `list_del()`: 从链表中删除一个节点;
- `list_move()`、`list_move_tail()`: 把节点从一个链表移到另一个链表;
- `list_empty()`: 检查链表是否为空;
- `list_splice()`: 把两个未连接的链表合并在一起;

(3) 遍历链表

- 宏`list_for_each()`;
- 宏`list_for_each_entry()`;
- 宏`list_for_each_entry_reverse()`: 反向遍历链表;
- 宏`list_for_each_entry_safe()`: 遍历的同时删除.

#### 6.2 队列

``` c
// include/linux/kfifo.h

struct kfifo {
	unsigned char *buffer;	/* the buffer holding the data */
	unsigned int size;	    /* the size of the allocated buffer */
	unsigned int in;	      /* data is added at offset (in % size) */
	unsigned int out;	      /* data is extracted from off. (out % size) */
};
```

操作:

- `kfifo_alloc()`: 定义和初始化kfifo;
- `kfifo_in()`: 推入数据;
- `kfifo_out()`: 摘取数据;
- `kfifo_out_peek()`: 偷窥数据, 但不删除;

#### 6.3 映射

Linux内核的映射数据结构: 映射一个唯一的标识数UID到一个指针. 这个映射被命名为idr.

``` c
// include/linux/idr.h

struct idr_layer {
	unsigned long		 bitmap; /* A zero bit means "space here" */
	struct idr_layer	*ary[1<<IDR_BITS];
	int			 count;	 /* When zero, we can release it */
	int			 layer;	 /* distance from leaf */
	struct rcu_head		 rcu_head;
};

struct idr {
	struct idr_layer *top;
	struct idr_layer *id_free;
	int		  layers; /* only valid without concurrent changes */
	int		  id_free_cnt;
	spinlock_t	  lock;
};
```

- `idr_int()`: 初始化idr;
- `idr_pre_get()`: 告知需要分配新的UID, 必要时调整后备树大小;
- `idr_get_new()`: 实际执行获取新的UID;
- `idr_get_new_abover()`: 指定一个最小的UID返回值;
- `idr_find()`: 查找UID;
- `idr_remove()`: 删除UID;
- `idr_destroy()`: 撤销idr;
- `idr_remove_all()`: 强制删除所有UID;

#### 6.4 二叉树

Linux实现的红黑树成为rbtree:

``` c
// include/linux/rbtree.h

struct rb_node
{
	unsigned long  rb_parent_color;
#define	RB_RED		0
#define	RB_BLACK	1
	struct rb_node *rb_right;
	struct rb_node *rb_left;
};

struct rb_root
{
	struct rb_node *rb_node;
};
```

rbtree的实现没有提供搜索和插入例程, 这些例程希望由rbtree的用户自己定义.

#### 6.5 数据结构以及选择

> skip

#### 6.6 算法复杂度

> skip

### [> 7 中断和中断处理](/kernel/kernel-dev/kernel-dev1/#7)
### [> 8 下半部和推后执行的工作](/kernel/kernel-dev/kernel-dev1/#8)
### [> 9 内核同步介绍](/kernel/kernel-dev/kernel-dev1/#9)
### [> 10 内核同步方法](/kernel/kernel-dev/kernel-dev1/#10)

### [> 11 定时器和时间管理](/kernel/kernel-dev/kernel-dev2/#11)
### [> 12 内存管理](/kernel/kernel-dev/kernel-dev2/#12)
### [> 13 虚拟文件系统](/kernel/kernel-dev/kernel-dev2/#13)
### [> 14 块I/O层](/kernel/kernel-dev/kernel-dev2/#14)
### [> 15 进程地址空间](/kernel/kernel-dev/kernel-dev2/#15)
### [> 16 页高速缓存和页回写](/kernel/kernel-dev/kernel-dev2/#16)
### [> 17 设备与模块](/kernel/kernel-dev/kernel-dev2/#17)
### [> 18 调试](/kernel/kernel-dev/kernel-dev2/#18)
### [> 19 可移植性](/kernel/kernel-dev/kernel-dev2/#19)
### [> 20 补丁、开发和社区](/kernel/kernel-dev/kernel-dev2/#20)

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

Rebert Love. **Linux Kernel Development**, Third Edition. 2010.

## 其他备注

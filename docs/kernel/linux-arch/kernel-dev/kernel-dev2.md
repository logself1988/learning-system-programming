# Notes of **Linux内核设计与实现** PART 2

### 11 定时器和时间管理 - TODO
### 12 内存管理 - TODO

#### 12.1 页
#### 12.2 区
#### 12.3 获得页
#### 12.4 `kmalloc()`
#### 12.5 `vmalloc()`
#### 12.6 slab层
#### 12.7 在栈上的静态分配
#### 12.8 高端内存的映射
#### 12.9 每个CPU的分配
#### 12.10 新的每个CPU接口
#### 12.11 使用每个CPU数据的原因
#### 12.12 分配函数的选择

### 13 虚拟文件系统 - TODO
### 14 块I/O层 - TODO
### 15 进程地址空间 - TODO

#### 15.1 地址空间
#### 15.2 内存描述符
#### 15.3 虚拟内存区域
#### 15.4 操作内存区域
#### 15.5 `mmap()`和`do_mmap()`: 创建地址区间
#### 15.6 `mummap()`和`do_mummap()`: 删除地址区间
#### 15.7 页表

### 16 页高速缓存和页回写 - TODO

#### 16.1 缓存手段
#### 16.2 Linux页高速缓存
#### 16.3 缓冲区高速缓存
#### 16.4 flusher线程

### 17 设备与模块 - TODO

#### 17.1 设备类型

设备被分为以下类型:

- 块设备(blkdev): 以块为单位的可寻址设备, 通常支持对数据的随机访问; 通过块设备节点特殊文件访问块设备, 通常被挂载为文件系统. 例: 硬盘、蓝光光碟、Flash.
- 字符设备(cdev): 不可寻址, 仅提供数据流式访问的设备, 即逐个字符或字节. 例: 键盘、鼠标、打印机、大部分伪设备.
- 网络设备: 通过一个物理适配器和一种特定的协议, 提供网络访问的设备. 例: 以太网设备.
- 杂项设备(miscdev): 针对单个任务而非通用的设备, 实际上是个简化的字符设备.
- 伪设备(pseudo device): 不表示物理设备, 仅提供访问内核功能的虚拟设备. 例: 内核随机数发生器/dev/random和/dev/urandom、空设备/dev/null、零设备/dev/zero、满设备/dev/full、内存设备/dev/mem.

#### 17.2 模块 - TODO
#### 17.3 设备模型

2.6内核引入了统一设备模型(device model): 提供了一个独立的机制专门来表示设备, 并描述其在系统中的拓扑结构.

- `kobject`: kernel object

使用`kobject`可以创建对象的层次结构, 通常被嵌入到其他结构中.

``` c
// include/linux/kobject.h

struct kobject {
	const char		*name;                         // 名称
	struct list_head	entry;
	struct kobject		*parent;                   // 父对象
	struct kset		*kset;
	struct kobj_type	*ktype;
	struct sysfs_dirent	*sd;                   // 指向表示该kobject的一个inode
	struct kref		kref;                         // 引用计数
	unsigned int state_initialized:1;
	unsigned int state_in_sysfs:1;
	unsigned int state_add_uevent_sent:1;
	unsigned int state_remove_uevent_sent:1;
	unsigned int uevent_suppress:1;
};

void kobject_init(struct kobject *kobj, struct kobj_type *ktype); // 初始化
struct kobject * kobject_create(void);                            // 创建

// include/linux/cdev.h

struct cdev {
	struct kobject kobj;                       // 被嵌入
	struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
};
```

引用计数:

``` c
// include/linux/kref.h

struct kref {
	atomic_t refcount;
};

void kref_get(struct kref *kref);                                     // +1
int kref_put(struct kref *kref, void (*release) (struct kref *kref)); // -1

// include/linux/kobject.h

struct kobject *kobject_get(struct kobject *kobj); // +1
void kobject_put(struct kobject *kobj);            // -1
```


- `ktype`: kernel object type

`ktype`用于描述一族`kobject`所具有的普遍特性.

``` c
// include/linux/kobject.h

struct kobj_type {
	void (*release)(struct kobject *kobj);     // 引用计数为0时的析构函数
	const struct sysfs_ops *sysfs_ops;         // 指向描述sysfs文件读写特性的结构体
	struct attribute **default_attrs;          // kobject相关的默认属性
};
```

- `kset`

`kset`是`kobject`对象的容器.

``` c
// include/linux/kobject.h

struct kset {
	struct list_head list;                     // 连接容器中所有kobject对象
	spinlock_t list_lock;                      // 保护list
	struct kobject kobj;                       // 该容器的kobject对象
	const struct kset_uevent_ops *uevent_ops;  // 处理容器中kobject对象的热插拔操作
};
```

#### 17.4 sysfs - TODO

### 18 调试 - TODO
### 19 可移植性 - TODO
### 20 补丁、开发和社区 - TODO

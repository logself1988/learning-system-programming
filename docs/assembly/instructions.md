# Instructions

> TODO 2022-06-20 move to `architecture` folders.

## IA32 in AT&T

```
l: 4B, 双字
w: 2B, 字
b: 1B, 字节

s: single precision, 单精度
l: double precision, 双精度
```

### EFLAGS

```
+---+---+...+---+---+
| 31| 30|   |  1|  0|
+---+---+...+---+---+
```

|#|Scope|Name/Value|Description|
|:---|:---|:---|:---|
|0    |Status Flag  |CF: Carry Flag                 ||
|1    |Reserved     |1                              ||
|2    |Status Flag  |PF: Parity Flag                ||
|3    |Reserved     |0                              ||
|4    |Status Flag  |AF: Auxiliary Carry Flag       ||
|5    |Reserved     |0                              ||
|6    |Status Flag  |ZF: Zero Flag                  ||
|7    |Status Flag  |SF: Sign Flag                  ||
|8    |System Flag  |TF: Trap Flag                  ||
|9    |System Flag  |IF: Interrupt Enable Flag      ||
|10   |System Flag  |DF: Direction Flag             ||
|11   |System Flag  |OF: Overflow Flag              ||
|12-13|System Flag  |IOPL: I/O Privilege Level      ||
|14   |System Flag  |NT: Nested Task                ||
|15   |Reserved     |0                              ||
|16   |System Flag  |RF: Resume Flag                ||
|17   |System Flag  |VM: Virtual-8086 Mode          ||
|18   |System Flag  |AC: Alignment Check            ||
|19   |System Flag  |VIF: Virtual Interrupt Flag    ||
|20   |System Flag  |VIP: Virtual Interrupt Pending ||
|21   |System Flag  |ID: ID Flag                    ||
|22-31|Reserved     |0                              ||

修改进位标志CF的指令:

- `clc`: 设置CF为0;
- `cmc`: 对CF求反;
- `stc`: 设置CF为1.

### 布尔逻辑操作

``` asm
and source, destination
or source, destination
xor source, destination

not operand
```

- `source`: 8/16/32位立即值/寄存器或内存值;
- `destination`: 8/16/32位寄存器或内存值;
- `source`与`destination`不能同时为内存值;
- `not`使用单一操作数, 即是源值也是目标值.

### cmp

``` asm
cmp operand1, operand2
```

- 执行减法操作`operand2 - operand1`, 设置EFLAGS寄存器

``` asm
cmp $20, %ebx      # 比较ebx与立即数20
cmp data, %ebx     # 比较ebx与内存中的值
cmp (%edi), %ebx   # 比较ebx与EDI指向的值


  movl $15, %eax
  movl $10, %ebx
  cmp %eax, %ebx
  jge greater
  # here %ebx < %eax
greater:
  # here %ebx >= %eax
```

### jxx

``` asm
jxx address

a: above
b: below
g: greater
l: less

c: CF
s: SF
o: OF
p: PF
z: ZF
```

- `ja`: 如果>则跳转; CF=0与ZF=0.
- `jae`: 如果>=则跳转; CF=0.
- `jb`: 如果<则跳转; CF=1.
- `jbe`: 如果<=则跳转; CF=1或ZF=1.
- `jc`: 如果进位则跳转; CF=1.
- `jcxz`: 如果cx寄存器为0则跳转.
- `jecxz`: 如果ecx寄存器为0则跳转.
- `je`: 如果=则跳转; ZF=1.
- `jg`: 如果>则跳转; ZF=0与SF=OF.
- `jge`: 如果>=则跳转; SF=OF.
- `jl`: 如果<则跳转; SF != OF.
- `jle`: 如果<=则跳转; ZF=1或 SF != OF.
- `jna`: 如果<=则跳转; CF=1或ZF=1.
- `jnae`: 如果<则跳转; CF=1.
- `jnb`: 如果>=则跳转; CF=1.
- `jnbe`: 如果>则跳转; CF=0与ZF=0.
- `jnc`: 如果无进位则跳转; CF=0.
- `jne`: 如果!=则跳转; ZF=0.
- `jng`: 如果<=则跳转; ZF=1或SF != OF.
- `jnge`: 如果<则跳转; SF != OF.
- `jnl`: 如果>=则跳转; SF=OF.
- `jnle`: 如果>则跳转; ZF=0与SF=OF.
- `jno`: 如果不溢出则跳转; OF=0.
- `jnp`: 如果不奇偶校验则跳转; PF=0.
- `jns`: 如果无符号则跳转; SF=0.
- `jnz`: 如果非零则跳转; ZF=0.
- `jo`: 如果溢出则跳转; OF=1.
- `jp`: 如果奇偶校验则跳转; PF=1.
- `jpe`: 如果偶校验则跳转; PF=1.
- `jpo`: 如果奇校验则跳转; PF=0.
- `js`: 如果带符号则跳转; SF=1.
- `jz`: 如果为零则跳转; ZF=1.

### loop

```
loop address

loope
loopz
loopne
loopnz
```

### test

``` asm
; logical compare
test operand1, operand2
```

- `operand1`: 8/16/32位立即数或寄存器值;
- `operand2`: 8/16/32位寄存器或内存值;
- 逐位计算`operand1`与`operand2`的逻辑与, 根据结果设置SF、ZF和PF状态标志. 丢弃结果.

```
TEMP ← SRC1 AND SRC2;
SF ← MSB(TEMP);
IF TEMP = 0
THEN ZF ← 1;
ELSE ZF ← 0;
FI:
PF ← BitwiseXNOR(TEMP[0:7]);
CF ← 0;
OF ← 0;
(*AF is Undefined*)
```

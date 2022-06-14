# RISC-V Simulators

## Windows

### Resources

- [Prebuilt RISC‑V GCC Toolchain and Emulator](https://www.sifive.com/software): SiFive
- [RISC-V from scratch 2: Hardware layouts, linker scripts, and C runtimes](https://twilco.github.io/riscv-from-scratch/2019/04/27/riscv-from-scratch-2.html): 2019-04-27
- [Hello, RISC-V and QEMU](https://mth.st/blog/riscv-qemu/): 2020-10-28

### Steps

1. add file `hello.s`

```
.section .init
.global _start
_start:
    li s1, 0x10000000 # s1 := 0x1000_0000
    la s2, message    # s2 := <message>
    addi s3, s2, 14   # s3 := s2 + 14
1:
    lb s4, 0(s2)      # s4 := (s2)
    sb s4, 0(s1)      # (s1) := s4
    addi s2, s2, 1    # s2 := s2 + 1
    blt s2, s3, 1b    # if s2 < s3, branch back to 1

.section .data
message:
  .string "Hello, world!\n"
```


2. assembly `hello.s`

```
riscv64-unknown-elf-as hello.s -g -o hello.elf
```

3. link

```
riscv64-unknown-elf-ld --verbose > riscv64-virt.ld
```

view system:

```
# dtb: devicetree blob
qemu-system-riscv64 -machine virt,dumpdtb=qemu-riscv64-virt.dtb

# dtc: devicetree compiler
dtc -I dtb -O dts -o riscv64-virt.dts riscv64-virt.dtb

grep "memory" riscv64-virt.dts -A 3
        memory@80000000 {
                device_type = "memory";
                reg = <0x00 0x80000000 0x00 0x8000000>;
        };
```

edit `riscv64-virt.ld`

```
OUTPUT_ARCH(riscv)
/* === ADD START */
MEMORY
{
   /* qemu-system-risc64 virt machine */
   RAM (rwx)  : ORIGIN = 0x80000000, LENGTH = 128M
}
/* === ADD END */
ENTRY(_start)


SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x10000)); . = SEGMENT_START("text-segment", 0x10000) + SIZEOF_HEADERS;
  /* === ADD START */
  PROVIDE(__stack_top = ORIGIN(RAM) + LENGTH(RAM));
  /* === ADD END */
  .interp         : { *(.interp) }
```


```
riscv64-unknown-elf-ld -T riscv64-virt.ld -o hello.linked.elf hello.elf
```

4. start

```
# shell 1
qemu-system-riscv64 -machine virt -m 128M -gdb tcp::1234 -S -kernel hello.linked.elf -bios none -nographic
```

5. debug

```
# shell 2
riscv64-unknown-elf-gdb hello.linked.elf
(gdb) target remote :1234
Remote debugging using :1234
0x0000000000001000 in ?? ()
(gdb) b _start
Breakpoint 1 at 0x80000000: file hello.s, line 4.
(gdb) c
Continuing.

Breakpoint 1, _start () at hello.s:4
4           li s1, 0x10000000 # s1 := 0x1000_0000
(gdb) c
Continuing.
```

6. stop

```
# shell 1
Hello, world!
[Press Ctrl+C]

# shell 2
[Inferior 1 (process 1) exited normally]
(gdb) q
```

## MacOS


### Resources

- [riscv-software-src/homebrew-riscv](https://github.com/riscv-software-src/homebrew-riscv)

### Steps

1. use brew

```
➜  brew tap riscv-software-src/riscv
➜  brew install riscv-tools
```

stuck on:

```
==> Installing dependencies for riscv-software-src/riscv/riscv-tools: riscv-gnu-toolchain, dtc, riscv-isa-sim and riscv-pk
==> Installing riscv-software-src/riscv/riscv-tools dependency: riscv-gnu-toolchain
Warning: Your Xcode (12.1) is outdated.
Please update to Xcode 12.4 (or delete it).
Xcode can be updated from the App Store.

==> sed -i .bak s/.*=host-darwin.o$// riscv-gcc/gcc/config.host
==> sed -i .bak s/.* x-darwin.$// riscv-gcc/gcc/config.host
==> ./configure --prefix=/usr/local/Cellar/riscv-gnu-toolchain/main --with-cmodel=medany --enable-multilib
==> make
```

Homebrew Caches: `~/Library/Caches/Homebrew/` `riscv-gnu-toolchain--git`,  `riscv-isa-sim--git` and `riscv-pk--git`.

3. build and install riscv-gnu-toolchain

```
➜  ./configure --prefix=/opt/riscv
➜  make

# a long time to wait
```

in `~/.zshrc` add:

```
# RISCV
export RISCV=/opt/riscv
export PATH=$RISCV/bin:$PATH
```

test:

```
➜  source ~/.zshrc

➜  riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-gcc (g5964b5cd727) 11.1.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

4. build and install riscv-pk

```
➜  mkdir build
➜  cd build
➜  ../configure --prefix=$RISCV --host=riscv64-unknown-elf
➜  make
➜  sudo make install
```

5. build and install riscv-isa-sim

```
➜  brew info dtc

➜  mkdir build
➜  cd build
➜  ../configure --prefix=$RISCV
➜  make
➜  sudo make install
```

6. test

```
➜  cat hello.c
#include <stdio.h>

int main()
{
	printf("Hello, world\n");
	return 0;
}

➜  riscv64-unknown-elf-gcc -o hello hello.c
➜  spike pk hello
bbl loader
Hello, world
```

### Spike Interactive Debug Mode

```
✗ spike -d pk hello     
: help
Interactive commands:
reg <core> [reg]                # Display [reg] (all if omitted) in <core>
freg <core> <reg>               # Display float <reg> in <core> as hex
fregh <core> <reg>              # Display half precision <reg> in <core>
fregs <core> <reg>              # Display single precision <reg> in <core>
fregd <core> <reg>              # Display double precision <reg> in <core>
vreg <core> [reg]               # Display vector [reg] (all if omitted) in <core>
pc <core>                       # Show current PC in <core>
mem <hex addr>                  # Show contents of physical memory
str <core> <hex addr>           # Show NUL-terminated C string at <hex addr> in core <core>
until reg <core> <reg> <val>    # Stop when <reg> in <core> hits <val>
until pc <core> <val>           # Stop when PC in <core> hits <val>
untiln pc <core> <val>          # Run noisy and stop when PC in <core> hits <val>
until mem <addr> <val>          # Stop when memory <addr> becomes <val>
while reg <core> <reg> <val>    # Run while <reg> in <core> is <val>
while pc <core> <val>           # Run while PC in <core> is <val>
while mem <addr> <val>          # Run while memory <addr> is <val>
run [count]                     # Resume noisy execution (until CTRL+C, or [count] insns)
r [count]                         Alias for run
rs [count]                      # Resume silent execution (until CTRL+C, or [count] insns)
quit                            # End the simulation
q                                 Alias for quit
help                            # This screen!
h                                 Alias for help
Note: Hitting enter is the same as: run 1
: while pc 0 a0 0
bbl loader
Hello, world
```

### Spike Debugging With Gdb


```
# shell 1

➜ cat rot13.c
char text[] = "Vafgehpgvba frgf jnag gb or serr!";

// Don't use the stack, because sp isn't set up.
volatile int wait = 1;

int main()
{
    while (wait)
        ;

    // Doesn't actually go on the stack, because there are lots of GPRs.
    int i = 0;
    while (text[i]) {
        char lower = text[i] | 32;
        if (lower >= 'a' && lower <= 'm')
            text[i] += 13;
        else if (lower > 'm' && lower <= 'z')
            text[i] -= 13;
        i++;
    }

done:
    while (!wait)
        ;
}

➜ cat spike.lds

OUTPUT_ARCH( "riscv" )

SECTIONS
{
  . = 0x10010000;
  .text : { *(.text) }
  .data : { *(.data) }
}

➜ riscv64-unknown-elf-gcc -g -Og -o rot13-64.o -c rot13.c
➜ riscv64-unknown-elf-gcc -g -Og -T spike.lds -nostartfiles -o rot13-64 rot13-64.o
➜ spike --rbb-port=9824 -m0x10000000:0x20000 rot13-64
Listening for remote bitbang connection on port 9824.
warning: tohost and fromhost symbols not in ELF; can't communicate with target
```

```
# shell 2

➜ brew install riscv-openocd
➜ echo 'export PATH="/usr/local/opt/riscv-openocd/bin:$PATH"' >> ~/.zshrc
➜ source ~/.zshrc

➜ openocd -f spike.cfg
Open On-Chip Debugger 0.11.0+dev-02365-ga2da82218 (2022-06-14-03:04)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
DEPRECATED! use 'adapter driver' not 'interface'
Info : only one transport option; autoselect 'jtag'
DEPRECATED! use 'remote_bitbang host' not 'remote_bitbang_host'
DEPRECATED! use 'remote_bitbang port' not 'remote_bitbang_port'
Info : Initializing remote_bitbang driver
Info : Connecting to localhost:9824
Info : remote_bitbang driver initialized
Info : This adapter doesn't support configurable speed
Info : JTAG tap: riscv.cpu tap/device found: 0xdeadbeef (mfg: 0x777 (<unknown>), part: 0xeadb, ver: 0xd)
Warn : JTAG tap: riscv.cpu       UNEXPECTED: 0xdeadbeef (mfg: 0x777 (<unknown>), part: 0xeadb, ver: 0xd)
Error: JTAG tap: riscv.cpu  expected 1 of 1: 0x10e31913 (mfg: 0x489 (SiFive Inc), part: 0x0e31, ver: 0x1)
Error: Trying to use configured scan chain anyway...
Warn : Bypassing JTAG setup events due to errors
Info : [riscv.cpu] datacount=2 progbufsize=2
Info : Examined RISC-V core; found 1 harts
Info :  hart 0: XLEN=64, misa=0x800000000014112d
[riscv.cpu] Target successfully examined.
Info : starting gdb server for riscv.cpu on 3333
Info : Listening on port 3333 for gdb connections
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```


```
# shell 3


➜  riscv riscv64-unknown-elf-gdb rot13-64
GNU gdb (GDB) 10.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin19.6.0 --target=riscv64-unknown-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
/Users/zhang/.gdbinit:1: Error in sourced command file:
No symbol table is loaded.  Use the "file" command.
Reading symbols from rot13-64...
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
0x0000000010010004 in main () at rot13.c:8
8	    while (wait)
(gdb) print wait
$1 = 1
(gdb) print wait=0
$2 = 0
(gdb) print text
$3 = "Vafgehpgvba frgf jnag gb or serr!"
(gdb) list
3	// Don't use the stack, because sp isn't set up.
4	volatile int wait = 1;
5
6	int main()
7	{
8	    while (wait)
9	        ;
10
11	    // Doesn't actually go on the stack, because there are lots of GPRs.
12	    int i = 0;
(gdb) b done
Breakpoint 1 at 0x10010062: file rot13.c, line 22.
(gdb) c
Continuing.

Breakpoint 1, main () at rot13.c:23
23	    while (!wait)
(gdb) print wait
$4 = 0
(gdb) print text
$5 = "Instruction sets want to be free!"
(gdb) q
A debugging session is active.

	Inferior 1 [Remote target] will be detached.

Quit anyway? (y or n) y
Detaching from program: /Users/zhang/workspace/riscv/rot13-64, Remote target
Ending remote debugging.
[Inferior 1 (Remote target) detached]
```

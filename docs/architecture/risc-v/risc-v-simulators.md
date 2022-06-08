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

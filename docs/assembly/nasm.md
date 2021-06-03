# Notes of **NASM – The Netwide Assembler**


|时间|内容|
|:---|:---|
|20210926|kick off.|

## 术语

<!-- 记录阅读过程中出现的关键字及其简单的解释. -->

## 介绍

<!-- 描述书籍阐述观点的来源、拟解决的关键性问题和采用的方法论等. -->

## 动机

<!-- 描述阅读书籍的动机, 要达到什么目的等. -->

## 概念结构

<!-- 描述书籍的行文结构, 核心主题和子主题的内容结构和关系. -->

### 1. Introduction
#### 1.1 What Is NASM?

### 2. Running NASM
#### 2.1 NASM Command-Line Syntax
#### 2.2 Quick Start for MASM Users

### 3. The NASM Language
#### 3.1 Layout of a NASM Source Line

``` asm
label:  instruction operands      ; comment
```

- `\`: line continuation character;
- colon `:` after a label is optional;
- valid characters: letters, numbers, `_`, `$`, `#`, `@`, `~`, `.`, `?`;
- first character of an identifier: letters, `.`, `_`, `?`;
- identifier prefixed with `$`: an identifier, not a reserved word, for example `$eax`.

`instruction operands` forms:

- register: `ax`, `bp`, `ebx`, `cr0`;
- effective addresses;
- constants;
- expressions.

#### 3.2 Pseudo-Instructions

``` asm
DB                          ; declare initialized data
DW
DD
DQ
DT
DO
DY
DZ

RESB                        ; declare uninitialized data
RESW
RESD
RESQ
REST
RESO
RESY
RESZ

INCBIN                      ; include external binary files
EQU                         ; define constants
TIMES                       ; repeat instructions for data
```

#### 3.3 Effective Addresses

> Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 1: Basic Architecture > 3.7.5 Specifying an Offset

Effective Address (or Offset) Computation:

```
Offset = Base + (Index * Scale) + Displacement
```

- `Base`: EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
- `Index`: EAX, EBX, ECX, EDX, EBP, ESI, EDI
- `Scale`: 1, 2, 4, 8
- `Displacement`: None, 8-bit, 16-bit, 32-bit

common combinations of address components:

```
Displacement
Base
Base + Displacement
(Index * Scale) + Displacement
Base + Index + Displacement
Base + (Index * Scale) + Displacement

RIP + Displacement                      // 64-bit mode
```


#### 3.4 Constants

- numeric constants: suffix `H` `X` `D` `T` `Q` `O` `B` `Y`, prefix `0x`;
- character strings: `''`, `""`, ``` `` ```; Unicode `\u` `\U`;
- character constants: a string up to 8 bytes long, little-endian order;
- string constants
- unicode strings

``` asm
__?utf16?__ __?utf16le?__ __?utf16be?__
__?utf32?__ __?utf32le?__ __?utf32be?__
```

- floating-point constants

``` asm
; sign:exponent:mantissa

__?float8?__
__?float16?__
__?bfloat16?__
__?float32?__
__?float64?__
__?float80m?__
__?float80e?__
__?float128l?__
__?float128h?__
```

- packeted BCD constants: suffix `p`, prefix `0p`.

#### 3.5 Expressions

Expressions are evaluated as 64-bit integers, which are then adjusted to the appropriate size.

- `$`: the assembly position at the beginning of the line containing the expression;
- `$$`: the beginning of the current section.

arithmetic operators, in increasing order of precedence:

```
?:                          ; conditional operator
||                          ; boolean OR operator
^^                          ; boolean XOR operator
&&                          ; boolean AND operator
= ==                        ; compare for equality
!= <>                       ; compare for inequality
<                           ; compare signed less than
<=                          ; compare signed less than or equal
>                           ; compare signed greater than
>=                          ; compare signed greater than or equal
<=>                         ; do a signed comparison, return -1, 0, 1
|                           ; bitwise OR operator
^                           ; bitwise XOR operator
&                           ; bitwise AND operator
<<                          ; bit-shift to the left
>>                          ; unsigned (logical) bit-shift to the right
<<<                         ; same as <<        
>>>                         ; signed (arithmetic) bit-shift to the right
+                           ; addition operator
-                           ; subtraction operator
*                           ; multiplication operator
/                           ; unsigned division operator
//                          ; signed division operator
%                           ; unsigned modulo operator
%%                          ; signed modulo operator
-                           ; unary negation operator
+                           ; unary positive operator
~                           ; bitwise negation operator
!                           ; boolean negation operator
SEG                         ; provide the segment address of its operand
__...___                    ; implement the integer functions in ifun macro package
```

#### 3.6 `SEG` and `WRT`

`SEG` operator: evalueate to the preferred segment base of a symbol, defined as the segment base relative to which the offset of the symbol make sense.

`WRT`: with reference to

``` asm
mov ax, seg symbol
mov es, ax
mov bx, symbol                ; ES:BX


mov ax, weird_seg             ; weird_seg is a segment base
mov es, ax
mov bx, symbol wrt weird_seg  ; ES:BX
```

far calls and jumps: inter segments

```
call (seg procedure):procedure
call weird_seg:(procedure wrt weird_seg)


call far procedure
jmp far label
```


#### 3.7 `STRICT`: Inhibiting Optimization

`STRICT`: inhibit optimization and force a particular operand to be emitted in the specified size.

``` asm
push strict dword 33
```

#### 3.8 Critical Expressions

Critical expressions: some expressions which must be resolvable on the first pass in NASM.

The first pass is used to determine the size of all the assembled code and data.

#### 3.9 Local Labels

local label: a label beginning with a single period `.`; it is associated with the previous non-local label.

NASM allows accessing to local labels from other parts of the code:

``` asm
label1  ; some code
.loop
        ; some more code
        jne .loop
        ret

label2  ; some code
.loop   
        ; some more code
        jne .loop
        ret

label3  ; somemorecode
        jmp label1.loop
```

`..@`: if a label begins with `..@`, then it does nothing to the local label mechanism:

``` asm
label1:
.local:                   ; label1.local
..@foo:                   ; a special symbol
label2:
.local:                   ; label2.local
          jmp ..@foo      ; jmp to foo
```

### 4. The NASM Preprocessor
#### 4.1 Single-Line Macros

``` asm
%define %idefine
%xdefine %ixdefine          ; resolve %define
%[...]                      ; macro indirection
%+                          ; concatenate single line macro tokens
%? %??                      ; the macro name itself
%*? %*??                    ; the single-line macro name
%undef                      ; undefine single-line macro
%assign                     ; preprocessor variables
%defstr                     ; define strings
%deftok %ideftok            ; define tokens
%defalias                   ; define aliases
%,                          ; conditional comma operator
```

#### 4.2 String Manipulation in Macros

``` asm
%strcat                     ; concatenate strings
%strlen                     ; string length
%substr                     ; extract substrings
```

#### 4.3 Multi-Line Macros: `%macro`

``` asm
%macro prologue 1           ; definition
      push ebp
      mov ebp, esp
      sub esp, %1           ; first parameter
%endmacro

myfunc: prologue 12         ; invoke the macro

myfunc: push ebp            ; expand to
        mov ebp, esp
        sub esp, 12
```

- overload: with different numbers of parameters
- marco-local labels: prefix `%%` to the label name
- greedy macro parameters: define the last parameter of a macro to be greedy
- macro parameters range: `%{x:y}`
- default macro parameters
- macro parameter counter: `%0`
- label preceeding macro: `%00`
- rotate macro parameters: `%rotate`
- concatenate macro parameters: `foo%1`, `%1foo`, `%{1}1`, `%{%foo}bar`
- condition codes as macro parameters: `%+1`, `%-1`
- disable listing expansion: `.nolist`
- undefine multi-line macros: `%unmacro`

#### 4.4 Conditional Assembly

``` asm
%if
%elif
%else
%endif

%if %ifn %elif %elifn

%ifdef %ifndef %elifdef %elifndef
%ifmacro %ifnmacro %elifmacro %elifnmacro
%ifctx %ifnctx %elifctx %elifnctx
%ifidn %ifnidn %elifidn %elifnidn
%iftoken %ifntoken %eliftoken %elifntoken
%ifempty %ifnempty %elifempty %elifnempty
%ifenv %ifnenv %elifenv %elifnenv
```

``` asm
%ifdef                      ; test single-line macro existence
%ifmacro                    ; test multi-line macro existence
%ifctx                      ; test the context stack
%if                         ; test arbitrary numeric expressions
%ifidn                      ; test exact text identity
%ifidni                     ; test exact text identity, case-insensitive
%ifid                       ; test token type: identifier
%ifnum                      ; test token type: numeric constant
%ifstr                      ; test token type: string
%iftoken                    ; test for a single token
%ifempty                    ; test for empty expansion
%ifenv                      ; test if environment variable exists
```

#### 4.5 Preprocessor Loops: `%rep`
#### 4.6 Source Files and Dependencies
#### 4.7 The Context Stack
#### 4.8 Stack Relative Preprocessor Directives
#### 4.9 Reporting User-Defined Errors: `%error`, `%warning`, `%fatal`
#### 4.10 `%pragma`: Setting Options
#### 4.11 Other Preprocessor Directives

### 5. Standard Macros
#### 5.1 NASM Version Macros
#### 5.2 `__?FILE?__` and `__?LINE?__`: File Name and Line Number
#### 5.3 `__?BITS?__`: Current Code Generation Mode
#### 5.4 `__?OUTPUT_FORMAT?__`: Current Output Format
#### 5.5 `__?DEBUG_FORMAT?__`: Current Debug Format
#### 5.6 Assembly Date and Time Macros
#### 5.7 `__?USE_package?__`: Package Include Test
#### 5.8 `__?PASS?__`: Assembly Pass
#### 5.9 Structure Data Types
#### 5.10 Alignment Control

### 6. Standard Macro Packages
#### 6.1 `altreg`: Alternate Register Names
#### 6.2 `smartalign`: Smart ALIGN Macro
#### 6.3 `fp`: Floating-point macros
#### 6.4 `ifunc`: Integer functions
#### 6.5 `masm`: MASM compatibility

### 7. Assembler Directives
#### 7.1 `BITS`: Specifying Target Processor Mode
#### 7.2 `DEFAULT`: Change the assembler defaults
#### 7.3 `SECTION` or `SEGMENT`: Changing and Defining Sections
#### 7.4 `ABSOLUTE`: Defining Absolute Labels
#### 7.5 `EXTERN`: Importing Symbols from Other Modules
#### 7.6 `REQUIRED`: Unconditionally Importing Symbols from Other Modules
#### 7.7 `GLOBAL`: Exporting Symbols to Other Modules
#### 7.8 `COMMON`: Defining Common Data Areas
#### 7.9 `STATIC`: Local Symbols within Modules
#### 7.10 `(G|L)PREFIX`, `(G|L)POSTFIX`: Mangling Symbols
#### 7.11 `CPU`: Defining CPU Dependencies
#### 7.12 `FLOAT`: Handling of floating-point constants
#### 7.13 `[WARNING]`: Enable or disable warnings

### 8. Output Formats
#### 8.1 `bin`: Flat-Form Binary Output
#### 8.2 `ith`: Intel Hex Output
#### 8.3 `srec`: Motorola S-Records Output
#### 8.4 `obj`: Microsoft OMF Object Files
#### 8.5 `win32`: Microsoft Win32 Object Files
#### 8.6 `win64`: Microsoft Win64 Object Files
#### 8.7 `coff`: Common Object File Format
#### 8.8 `macho32` and `macho64`: Mach Object File Format
#### 8.9 `elf32`, `elf64`, `elfx32`: Executable and Linkable Format Object Files
#### 8.10 `aout`: Linux a.out Object Files
#### 8.11 `aoutb`: NetBSD/FreeBSD/OpenBSD a.out Object Files
#### 8.12 `as86`: Minix/Linux as86 Object Files
#### 8.13 `rdf`: Relocatable Dynamic Object File Format (deprecated)
#### 8.14 `dbg`: Debugging Format

### 9. Writing 16-bit Code (DOS, Windows 3/3.1)
#### 9.1 Producing .EXE Files
#### 9.2 Producing .COM Files
#### 9.3 Producing .SYS Files
#### 9.4 Interfacing to 16-bit C Programs
#### 9.5 Interfacing to Borland Pascal Programs

### 10. Writing 32-bit Code (Unix, Win32, DJGPP)
#### 10.1 Interfacing to 32-bit C Programs
#### 10.2 Writing NetBSD/FreeBSD/OpenBSD and Linux/ELF Shared Libraries

### 11. Mixing 16- and 32-bit Code
#### 11.1 Mixed-Size Jumps
#### 11.2 Addressing Between Different-Size Segments
#### 11.3 Other Mixed-Size Instructions

### 12. Writing 64-bit Code (Unix, Win64)
#### 12.1 Register Names in 64-bit Mode
#### 12.2 Immediates and Displacements in 64-bit Mode
#### 12.3 Interfacing to 64-bit C Programs (Unix)
#### 12.4 Interfacing to 64-bit C Programs (Win64)

### 13. Troubleshooting
#### 13.1 Common Problems

### Appendix A: Ndisasm
#### A.1 Introduction
#### A.2 Running NDISASM

### Appendix B: Instruction List
#### B.1 Introduction

### Appendix C: NASM Version History
#### C.1 NASM 2 Series
#### C.2 NASM 0.98 Series
#### C.3 NASM 0.9 Series

### Appendix D: Building NASM from Source
#### D.1 Building from a Source Archive
#### D.2 Building from the git Repository
#### D.3 Building the documentation

### Appendix E: Contact Information
#### E.1 Website
#### E.2 Reporting Bugs

## 总结

<!-- 概要记录书籍中如何解决关键性问题的. -->

## 应用

<!-- 记录如何使用书籍中方法论解决你自己的问题. -->

## 文献引用

<!-- 记录相关的和进一步阅读资料: 文献、网页链接等. -->

- NASM – The Netwide Assembler, version 2.15.05.

## 其他备注

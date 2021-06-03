# An example of using C style functions

/*
|                   | in-direct addressing
|func arg3          |16  (%ebp)
|func arg2          |12  (%ebp)
|func arg1          |8   (%ebp)
|func rtn address   |4   (%ebp)
|old EBP            |    (%ebp)
|local var1         |-4  (%ebp)
|local var2         |-8  (%ebp)
|local var3         |-12 (%ebp) <- ESP
|                   |
*/

.section .data
precision:
    .byte 0x7f, 0x00

.section .bss
    .lcomm result, 4

.section .text
.globl _start
_start:
    finit
    fldcw precision

    pushl $10
    call area
    addl $4, %esp
    movl %eax, result

    pushl $2
    call area
    addl $4, %esp
    movl %eax, result

    pushl $120
    call area
    addl $4, %esp
    movl %eax, result

    movl $1, %eax
    movl $0, %ebx
    int $0x80

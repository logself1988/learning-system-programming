# An example of using ZF

.section .text
.globl _start
_start:
    movl $30, %eax
    subl $30, %eax
    jz overthere

    movl $1, %eax
    movl $1, %ebx
    int $0x80

overthere:

    movl $1, %eax
    movl $0, %ebx
    int $0x80

# An example of using CF

.section .text
.globl _start
_start:
    movl $0xffffffff, %ebx
    addl $1, %ebx
    jc overflow

    movl $1, %eax
    int $0x80

overflow:

    movl $1, %eax
    movl $0, %ebx
    int $0x80

# An example of using PF

.section .text
.globl _start
_start:
    movl $1, %eax
    movl $4, %ebx
    subl $1, %ebx       # 0000 0011
    jp overthere
    int $0x80

overthere:
    movl $0, %ebx
    int $0x80

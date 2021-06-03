# An example of using OF

.section .text
.globl _start
_start:
    movl $1, %eax
    movb $0x7f, %bl
    addb $10, %bl
    jo overthere
    int $0x80

overthere:
    movl $0, %ebx
    int $0x80

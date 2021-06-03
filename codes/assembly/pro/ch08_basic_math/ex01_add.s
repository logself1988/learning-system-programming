# An example of the ADD instruction

.section .data
data:
    .int 40

.section .text
.globl _start
_start:
    movl $0, %eax
    movl $0, %ebx
    movl $0, %ecx
    movb $20, %al
    addb $10, %al

    movsx %al, %eax     # eax = 30
    movw $100, %cx      # cx = 100
    addw %cx, %bx       # bx = 100

    movsx %bx, %ebx     # ebx = 100
    movl $100, %edx     # edx = 100
    addl %edx, %edx     # edx = 200
    addl data, %eax     # eax = 70
    addl %eax, data     # data = 110

    movl $1, %eax
    movl $0, %ebx
    int $0x80

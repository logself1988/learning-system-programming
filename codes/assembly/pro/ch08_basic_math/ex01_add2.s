# An example of the ADD instruction and negative numbers

.section .data
data:
    .int -40

.section .bss
    .lcomm buffer, 10

.section .text
.globl _start
_start:
    movl $-10, %eax     # eax = -10
    movl $-200, %ebx    # ebx = -200
    movl $80, %ecx      # ecx = 80
    addl data, %eax     # eax = -50
    addl %ecx, %eax     # eax = 30
    addl %ebx, %eax     # eax = -170
    addl %eax, data     # data = -210
    addl $210, data     # data = 0

    movl $1, %eax
    movl $0, %ebx
    int $0x80

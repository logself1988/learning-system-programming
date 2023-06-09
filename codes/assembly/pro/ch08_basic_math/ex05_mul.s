# An example of using the MUL instruction

.section .data
data1:
    .int 315814
data2:
    .int 165432
result:
    .quad 0
output:
    .asciz "The result is %qd\n"

.section .text
.globl _start
_start:
    movl data1, %eax
    mull data2
    movl %eax, result
    movl %edx, result+4

    pushl %edx
    pushl %eax
    pushl $output
    call printf
    addl $12, %esp

    pushl $0
    call exit

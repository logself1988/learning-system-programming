# An example of detecting an overflow condition

.section .data
output:
    .asciz "The result is %d\n"

.section .bss
    .lcomm buffer, 10

.section .text
.globl _start
_start:
    movl $-1590876934, %ebx
    movl $-1259239143, %eax
    addl %eax, %ebx
    jo over

    pushl %ebx
    pushl $output
    call printf
    addl $8, %esp

    pushl $0
    call exit

over:
    pushl $0
    pushl $output
    call printf
    addl $8, %esp

    pushl $0
    call exit

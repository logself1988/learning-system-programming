# Listing command line arguments

/*
|ENV, CMD ARGS  |
|ENV ptrs       |
|0x0000000      |
|CMD ARG3 ptr   |
|CMD ARG2 ptr   |
|CMD ARG1 ptr   |
|PROGRAM NAME   |            <- EBP
|CMD ARGS COUNT | <- ESP
*/


.section .data
output1:
    .asciz "There are %d parameters:\n"
output2:
    .asciz "%s\n"

.section .text
.globl _start
_start:
    movl (%esp), %ecx       # cmd arguments count

    pushl %ecx
    pushl $output1
    call printf
    addl $4, %esp
    popl %ecx

    movl %esp, %ebp
    addl $4, %ebp

loop1:
    pushl %ecx
    pushl (%ebp)
    pushl $output2
    call printf
    addl $8, %esp
    popl %ecx
    
    addl $4, %ebp
    loop loop1

    pushl $0
    call exit

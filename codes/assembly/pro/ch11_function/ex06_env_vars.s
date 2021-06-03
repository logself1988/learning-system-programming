# Listing system environment variables

/*
|ENV, CMD ARGS  |
|ENV ptrs       | 12            <- EBP
|0x0000000      | 8
|PROGRAM NAME   | 4           
|CMD ARGS COUNT | <- ESP
*/

.section .data
output:
    .asciz "%s\n"

.section .text
.globl _start
_start:
    movl %esp, %ebp
    addl $12, %ebp      # without command line arguments

loop1:
    cmpl $0, (%ebp)     # end with NULL string
    je endit

    pushl (%ebp)
    pushl $output
    call printf
    addl $8, %esp

    addl $4, %ebp       # next env ptr
    loop loop1

endit:
    pushl $0
    call exit

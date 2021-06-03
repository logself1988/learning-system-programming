# An example of using functions

.section .data
precision:
    .byte 0x7f, 0x00

.section .bss
    .lcomm value, 4

.section .text
.globl _start
_start:
    finit
    fldcw precision

    movl $10, %ebx
    call area

    movl $2, %ebx
    call area

    movl $120, %ebx
    call area

    movl $1, %eax
    movl $0, %ebx
    int $0x80

# input: %ebx
# mem: value
# output: ST(0)
.type area, @function
area:
    fldpi
    imull %ebx, %ebx
    movl %ebx, value
    filds value
    fmulp %st(0), %st(1)
    ret

# An example of reading input values wrong
.section .text
.type testfunc, @function
.globl testfunc
testfunc:
    pushl %ebp
    movl %esp, %ebp

    fldl 8(%ebp)        # double precision, 64 bit
    fimul 16(%ebp) 

    movl %ebp, %esp
    popl %ebp
    ret

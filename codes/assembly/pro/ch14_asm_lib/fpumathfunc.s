# An example of reading multiple input values
# (( 43.65 / 22) + (76.34 * 3.1)) / ((12.43 * 6) - (140.2 / 94.21))

.section .text
.type fpumathfunc, @function
.globl fpumathfunc
fpumathfunc:
    pushl %ebp
    movl %esp, %ebp

    flds 8(%ebp)                # 43.65
    fidiv 12(%ebp)              # 22
    flds 16(%ebp)               # 76.34
    flds 20(%ebp)               # 3.1
    fmul %st(1), %st(0)
    fadd %st(2), %st(0)
    flds 24(%ebp)               # 12.43
    fimul 28(%ebp)              # 6
    flds 32(%ebp)               # 140.2
    flds 36(%ebp)               # 94.21
    fdivrp
    fsubr %st(1), %st(0)
    fdivr %st(2), %st(0)
    

    movl %ebp, %esp
    popl %ebp
    ret

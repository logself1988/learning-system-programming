# An example of a function that returns an integer value

.type square, @function
.globl square
square:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax      # read first argument
    imull %eax, %eax

    movl %ebp, %esp
    popl %ebp
    ret

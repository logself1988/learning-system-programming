# An example of setting the precision bits int he Control Register

.section .data
newvalue:
    .int 0x7f, 0x00

.section .bss
    .lcomm control, 10

.section .text
.globl _start
_start:
    fstcw control
    fldcw newvalue
    fstcw control

    movl $1, %eax
    movl $0, %ebx
    int $0x80

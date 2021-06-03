# An example of the CMOV instructions

.section .data
output:
    .asciz "The largest value is %d\n"
values:
    .int 105, 235, 61, 315, 134, 221, 53, 145, 117, 5

.section .text
.globl _start
_start:
    movl values, %ebx             # first element; hold the largest value
    movl $1, %edi

loop:
    movl values(, %edi, 4), %eax
    cmp %ebx, %eax               # calc %eax-%ebx, set EFLAGS
    cmova %eax, %ebx             # if %eax > %ebx, then %ebx = %eax
    inc %edi
    cmp $10, %edi
    jne loop

    pushl %ebx
    pushl $output
    call printf
    addl $8, %esp

    pushl $0
    call exit

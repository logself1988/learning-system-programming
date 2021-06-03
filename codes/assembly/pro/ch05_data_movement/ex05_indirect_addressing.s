# An example of indirect addressing

.section .data
values:
    .int 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60

.section .text
.globl _start
_start:
    movl values, %eax                   # %eax = 10
    movl $values, %edi                  # %edi = address of values
    movl $100, 4(%edi)                  # 15 => 100
    movl $1, %edi
    movl values(, %edi, 4), %ebx        # 100

    movl $1, %eax
    int $0x80

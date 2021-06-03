/*
Sample Program to extract the processor Vendor ID
*/

/* .section __DATA,__data */
.section .data
output:
  .ascii "The processor Vendor ID is 'xxxxxxxxxxxx'\n"

/* .section __TEXT,__text */
.section .text
.globl _start
_start:
    movl $0, %eax
    cpuid

    /* input */
    movl $output, %edi
    movl %ebx, 28(%edi)
    movl %edx, 32(%edi)
    movl %ecx, 36(%edi)

    /* write */
    movl $4, %eax
    movl $1, %ebx
    movl $output, %ecx
    movl $42, %edx
    int $0x80

    /* exit */
    movl $1, %eax
    movl $0, %ebx
    int $0x80

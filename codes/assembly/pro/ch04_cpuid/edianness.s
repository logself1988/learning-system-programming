/* view endianess in memory and register */
.section .data
value:
    .byte 0x01, 0x02, 0x03, 0x04    /* x/4xb &value */

.section .text
.globl _start
_start:

    movl value, %ecx                /* print/x $ecx */
    
    movl $1, %eax
    movl $0, %ebx
    int $0x80

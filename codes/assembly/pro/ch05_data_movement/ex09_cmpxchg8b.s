.section .data
data:
    .byte 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88

.section .text
.globl _start
_start:
  movl $0x44332211, %eax
  movl $0x88776655, %edx
  movl $0x11223344, %ebx
  movl $0x55667788, %ecx

  cmpxchg8b data

  movl $1, %eax
  movl $0, %ebx
  int $0x80

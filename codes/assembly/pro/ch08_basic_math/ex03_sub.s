# An example of the SUB instruction

.section .data
data:
    .int 40

.section .text
.globl _start
_start:
    movl $0, %eax
    movl $0, %ebx
    movl $0, %ecx
    movb $20, %al
    subb $10, %al       # al = 10

    movsx %al, %eax     # eax = 10
    movw $100, %cx      # cx = 100
    subw %cx, %bx       # bx = -100

    movl $100, %edx     # edx = 100
    subl %eax, %edx     # edx = 90
    subl data, %eax     # eax = -30
    subl %eax, data     # data = 70

    movl $1, %eax
    movl $0, %ebx
    int $0x80

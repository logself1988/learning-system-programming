.section .data
.HELLO:
    .string "Hello, world!"

.section .text
.globl main
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    addi s0, sp, 16
    
    lui a5, %hi(.HELLO)
    addi a0, a5, %lo(.HELLO)
    call puts

    li a5, 0
    mv a0, a5

    ld ra, 8(sp)
    ld s0, 0(sp)
    addi sp, sp, 16

    jr ra

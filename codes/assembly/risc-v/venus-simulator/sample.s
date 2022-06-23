.data
greeting: .asciiz "hello, venus!"

.text
.globl start
start: 
  # print_string
  addi a0 x0 4
  la a1 greeting
  ecall

  # exit
  li a0 10
  ecall

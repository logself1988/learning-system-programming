section .data
message: db 'hello, world!', 0

section .text

; external function in lib.o
extern print_string
extern print_newline
extern exit

global _start
_start:
  mov rdi, message
  call print_string
  call print_newline
  call exit
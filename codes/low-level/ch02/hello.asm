%include "../lib/syscall.inc"
section .data
message: db 'hello, world!', 10

section .text
global _start
_start:
  mov rax, NR_WRITE
  mov rdi, 1          ; argument #1: stdout
  mov rsi, message    ; argument #2: string address
  mov rdx, 14         ; argument #3: string length in bytes
  syscall

  mov rax, NR_EXIT
  xor rdi, rdi
  syscall

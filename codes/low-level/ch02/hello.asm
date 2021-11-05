section .data
message: db 'hello, world!', 10

section .text
global _start
_start:
  mov rax, 1          ; system call: write
  mov rdi, 1          ; argument #1: stdout
  mov rsi, message    ; argument #2: string address
  mov rdx, 14         ; argument #3: string length in bytes
  syscall

  mov rax, 60         ; system call: exit
  xor rdi, rdi
  syscall

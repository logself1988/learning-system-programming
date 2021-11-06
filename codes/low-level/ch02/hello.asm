section .data
message: db 'hello, world!', 10

section .text
global _start
_start:
%ifdef MACOS
  mov rax, 0x2000004  ; system call: write
%else
  mov rax, 1          ; system call: write
%endif
  mov rdi, 1          ; argument #1: stdout
  mov rsi, message    ; argument #2: string address
  mov rdx, 14         ; argument #3: string length in bytes
  syscall

%ifdef MACOS
  mov rax, 0x2000001  ; system call: exit
%else  
  mov rax, 60         ; system call: exit
%endif
  xor rdi, rdi
  syscall

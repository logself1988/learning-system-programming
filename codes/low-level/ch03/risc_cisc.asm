; modify eax: disacard rax upper 32bits to eliminate data interdependency
; modify ax: does not affect operations with their smaller parts for the sake of compatibility
section .data

section .text
global _start
_start:
  mov rax, 0x1122334455667788
  mov eax, 0x42                 ; rax: 0x42

  mov rax, 0x1122334455667788
  mov ax, 0x9999                ; rax: 0x1122334455669999

  mov rax, 0x1122334455667788
  xor eax, eax                  ; rax: 0x0

  mov rax, 60         ; system call: exit
  xor rdi, rdi
  syscall

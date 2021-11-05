section .data
test_string: db "abcdef", 0

section .text
global _start

strlen:
  xor rax, rax            ; rax with hold string length
.loop:
  cmp byte [rdi+rax], 0
  je .end
  inc rax
  jmp .loop
.end:
  ret

_start:
  ; syscall arguments: rax, rdi, rsi, rdx, r10, r8, r9
  ; syscall changes: rcx, r11
  mov rdi, test_string
  call strlen
  mov rdi, rax

  mov rax, 60         ; system call: exit
  syscall

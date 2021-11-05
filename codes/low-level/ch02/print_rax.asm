; output rax value in hexadecimal format

section .data
codes: db '0123456789ABCDEF'

section .text
global _start
_start:
  ; syscall arguments: rax, rdi, rsi, rdx, r10, r8, r9
  ; syscall changes: rcx, r11
  mov rax, 0x1122334455667788

  mov rdi, 1
  mov rdx, 1
  mov rcx, 64

.loop:
  push rax
  sub rcx, 4              ; 4 bits
  sar rax, cl
  and rax, 0xf

  lea rsi, [codes+rax]
  mov rax, 1              ; system call: write

  push rcx                ; syscall changes rcx
  syscall
  pop rcx

  pop rax

  test rcx, rcx           ; is zero?
  jnz .loop
  
  
  mov rax, 60             ; system call: exit
  xor rdi, rdi
  syscall


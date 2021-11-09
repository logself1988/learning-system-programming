%include "../lib/syscall.inc"
default rel             ; use relative addressing
; output rax value in hexadecimal format

section .data
codes: db "0123456789ABCDEF"
newline_char: db 10

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

; WARN: effective address in MACOS
%ifdef MACOS
  lea rsi, [codes]
  add rsi, rax
%else
  lea rsi, [codes+rax]
%endif

  mov rax, NR_WRITE

  push rcx                ; syscall changes rcx
; WARN: system call in MACOS: pass the parameters again
%ifdef MACOS
  mov rdi, 1
  mov rdx, 1
%endif
  syscall
  pop rcx

  pop rax

  test rcx, rcx           ; is zero?
  jnz .loop


  mov rax, NR_WRITE
  mov rdi, 1
  mov rdx, 1
  lea rsi, [newline_char]
  syscall

  mov rax, NR_EXIT
  xor rdi, rdi
  syscall


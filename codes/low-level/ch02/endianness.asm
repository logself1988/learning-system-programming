section .data
newline_char: db 10
codes: db '0123456789abcdef'
demo1: dq 0x0123456789abcdef
demo2: db 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
; Intel 64 follows the littile endian convention

section .text
global _start

; tow function same as print_call.asm
print_newline:
%ifdef MACOS
  mov rax, 0x2000004  ; system call: write
%else
  mov rax, 1          ; system call: write
%endif
  mov rdi, 1
  mov rsi, newline_char
  mov rdx, 1
  syscall
  ret

print_hex:
  mov rax, rdi
  mov rdi, 1
  mov rdx, 1
  mov rcx, 64
iterate:
  push rax
  sub rcx, 4              ; 4 bits
  sar rax, cl

  and rax, 0xf
%ifdef MACOS
  lea rsi, [rel codes]
  add rsi, rax
%else
  lea rsi, [codes+rax]
%endif

%ifdef MACOS
  mov rax, 0x2000004  ; system call: write
%else
  mov rax, 1          ; system call: write
%endif

  push rcx
%ifdef MACOS
  mov rdi, 1
  mov rdx, 1
%endif
  syscall
  pop rcx

  pop rax
  test rcx, rcx
  jnz iterate

  ret

_start:
  mov rdi, [rel demo1]
  call print_hex
  call print_newline

  mov rdi, [rel demo2]
  call print_hex
  call print_newline
  
%ifdef MACOS
  mov rax, 0x2000001  ; system call: exit
%else  
  mov rax, 60         ; system call: exit
%endif  
  xor rdi, rdi
  syscall

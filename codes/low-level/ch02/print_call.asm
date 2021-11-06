; function calls:
; call <address>
; ret
;
; arguments:
; first six: rdi, rsi, rdx, rcx, r8, r9
; rest: to the stack in reverse order
;
; return values:
; rax, rdx
;
; convention:
; callee-saved registers: rbx, rbp, rsp, r12-r15

section .data
newline_char: db 10
codes: db '0123456789abcdef'

section .text
global _start

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
  lea rsi, [rel codes]    ; use relative addressing
  add rsi, rax
%else
  lea rsi, [codes+rax]
%endif

%ifdef MACOS
  mov rax, 0x2000004  ; system call: write
  mov rdi, 1
  mov rdx, 1
%else
  mov rax, 1          ; system call: write
%endif

  push rcx
  syscall
  pop rcx

  pop rax
  test rcx, rcx
  jnz iterate

  ret

_start:
  mov rdi, 0x1122334455667788
  call print_hex
  call print_newline

%ifdef MACOS
  mov rax, 0x2000001  ; system call: exit
%else  
  mov rax, 60         ; system call: exit
%endif
  xor rdi, rdi
  syscall

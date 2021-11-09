%include "../lib/syscall.inc"

%define O_RDONLY 0
%define PROT_READ 0x01
%define MAP_PRIVATE 0x0002

section .data
fname: db './ch04/runs.txt', 0

section .text
global _start

print_string: ; print newline terminated string
  push rdi
  call string_length
  pop rsi
  mov rdx, rax
  mov rax, NR_WRITE
  mov rdi, 1
  syscall
  ret
string_length:
  xor rax, rax
.loop:
  cmp byte [rdi+rax], 10 ; newline
  je .end
  inc rax
  jmp .loop
.end:
  inc rax
  ret

_start:
  mov rax, NR_OPEN
  mov rdi, fname        ; #1
  mov rsi, O_RDONLY     ; #2
  mov rdx, 0            ; #3
  syscall

  ;  MACOS: 197	AUE_MMAP	ALL	{ user_addr_t mmap(caddr_t addr, size_t len, int prot, int flags, int fd, off_t pos); } 
  mov r8, rax           ; #5, rax holds fd
  mov rax, NR_MMAP
  mov rdi, 0            ; #1
  mov rsi, 4096         ; #2
  mov rdx, PROT_READ    ; #3
  mov r10, MAP_PRIVATE  ; #4
  mov r9, 0             ; #6, offset in file
  syscall               ; rax point to mapped location

  mov rdi, rax

  call print_string
  
  mov rax, NR_EXIT
  xor rdi, rdi
  syscall

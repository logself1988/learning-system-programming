%include "../lib/syscall.inc"

section .text
global _start
_start:

%ifdef MACOS
  mov rax, [0x100004000-1]
%else
  mov rax, [0x400000-1]
%endif

  mov rax, NR_EXIT
  xor rdi, rdi
  syscall

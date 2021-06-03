; An example of sandbox
SECTION .data

SECTION .text

global _start
_start:
    
    mov eax, 1
    mov ebx, 0
    int 80H

SECTION .bss

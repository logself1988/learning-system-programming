; An example of 
SECTION .data

SECTION .bss
BUFFLEN equ 1024
Buff: resb BUFFLEN

SECTION .text

global _start
_start:

; read from stdin to buffer    
Read:
    mov eax, 3
    mov ebx, 0
    mov ecx, Buff
    mov edx, BUFFLEN
    int 80H
    
    mov esi, eax
    cmp eax, 0
    je Done
    
    mov ecx, esi
    mov ebp, Buff
    dec ebp

; scan buffer
Scan:
    cmp byte [ebp+ecx], 61H         ; 'a'
    jb Next

    cmp byte [ebp+ecx], 7AH         ; 'z'
    ja Next

    sub byte [ebp+ecx], 20H         ; uppercase

Next:
    dec ecx
    jnz Scan

; write to stdout
Write:
    mov eax, 4
    mov ebx, 1
    mov ecx, Buff
    mov edx, esi
    int 80H
    jmp Read                        ; read again

Done:
    mov eax, 1
    mov ebx, 0
    int 80H

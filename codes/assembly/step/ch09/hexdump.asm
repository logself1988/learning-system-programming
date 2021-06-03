; An example of hexdump a file
SECTION .data
HexStr: db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00", 10   ; item: _00
HEXLEN equ $-HexStr
Digits: db "0123456789ABCDEF"

SECTION .bss
BUFFLEN equ 16
Buff: resb BUFFLEN
NL: resb 1

SECTION .text

global _start
_start:

Read:
    mov eax, 3                              ; read from stdin
    mov ebx, 0
    mov ecx, Buff
    mov edx, BUFFLEN
    int 80H

    mov ebp, eax
    cmp eax, 0
    je Done

    mov esi, Buff
    mov edi, HexStr
    xor ecx, ecx

Scan:
    xor eax, eax

    mov edx, ecx                            ; ecx * 3
    shl edx, 1
    add edx, ecx

    mov al, byte [esi+ecx]
    mov ebx, eax

    and al, 0FH
    mov al, byte [Digits+eax]
    mov byte [HexStr+edx+2], al

    shr bl, 4
    mov bl, byte [Digits+ebx]
    mov byte [HexStr+edx+1], bl

    inc ecx
    cmp ecx, ebp
    jna Scan

    mov eax, 4                              ; write to stdout
    mov ebx, 1
    mov ecx, HexStr
    mov edx, HEXLEN
    int 80H
    
    jmp Read

Done:
    mov eax, 1
    mov ebx, 0
    int 80H

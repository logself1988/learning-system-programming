; An example of call Linux system call
SECTION .data
EatMsg: db "Eat at Joe's!", 10, "Ten million files can't ALL be wrong!", 10
EatLen: equ $-EatMsg

SECTION .text

global _start
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, EatMsg
    mov edx, EatLen
    int 80H

    mov eax, 1
    mov ebx, 0
    int 80H

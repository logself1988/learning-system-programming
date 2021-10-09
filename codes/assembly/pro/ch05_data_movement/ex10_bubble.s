# An example of the XCHG instruction

# bubble sort
#
# for(out = len-1; out > 0; out--)
#   for(in = 0; in < out; i++)
#       if (arr[in] > arr[in+1])
#           swap(arr[i], arr[in+1]);
#


.section .data
values:
    .int 105, 235, 61, 315, 134, 221, 53, 145, 117, 5

.section .text
.globl _start
_start:
    movl $values, %esi
    movl $9, %ecx
    movl $9, %ebx

loop:
    movl (%esi), %eax
    cmp %eax, 4(%esi)
    jge skip
    xchg %eax, 4(%esi)
    movl %eax, (%esi)
skip:
    add $4, %esi
    dec %ebx
    jnz loop
    dec %ecx
    jz end

    movl $values, %esi
    movl %ecx, %ebx
    jmp loop
end:
    movl $1, %eax
    movl $0, %ebx
    int $0x80
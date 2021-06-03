/*
View the CPUID Vendor ID string using C library calls
*/

.section .data
output:
  .asciz "The processor Vendor ID is '%s'\n"

.section .bss
.lcomm buffer, 12

.section .text
.globl _start
_start:
  mov $0, %eax
  cpuid

  mov $buffer, %edi
  mov %ebx, (%edi)
  mov %edx, 4(%edi)
  mov %ecx, 8(%edi)

  mov $output, %rdi
  mov $buffer, %rsi
  call printf

  push $0
  call exit

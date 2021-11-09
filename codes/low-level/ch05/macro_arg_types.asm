%macro print 1
  %ifid %1
    mov rdi, %1
    call print_string
  %else
    %ifnum %1
      mov rdi, %1
      call print_uint
    %else
      %error "string literals are not supported yet"
    %endif
  %endif
%endmacro

myhello: db 'hello', 10, 0
_start:
  print myhello
  print 42
  mov rax, NR_EXIT
  xor rdi, rdi
  syscall
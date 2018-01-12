%define stdout      1
%define sys_write   4

global the_beginning

section .code
the_beginning:

    call do_stuff

    mov     al, 1                           ; sys_exit kernel opcode
    mov     bl, 42                          ; exit code 42
    int     0x80                            ; poke the kernel

do_stuff:
    mov     eax, sys_write
    mov     ebx, stdout
    mov     ecx, msg
    mov     edx, msg.len
    int     0x80
    ret

section .vars
msg:            db      "Hey there babycakes!", 0x0A, 0x00
.len:           equ     $ - msg

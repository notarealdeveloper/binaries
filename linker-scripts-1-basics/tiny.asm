section .text
global _start
_start:
    %define stdout      1
    %define sys_exit    1
    %define sys_write   4

    mov     eax, sys_write
    mov     ebx, stdout
    mov     ecx, msg
    mov     edx, msg.len
    int     0x80

    mov     al, sys_exit
    mov     bl, 42
    int     0x80

section .data
msg:            db      "Hey there babycakes!", 0x0a, 0x00
.len:           equ     $ - msg

section .bss

global _start
_start:
    jmp ender
    starter:

    xor rax, rax
    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx

    mov al, 1                       ; syscall write
    inc rdi                         ; stdout is 1
    pop rsi                         ; get string address from stack
    mov dl, msg.len                 ; length of the string
    syscall

    xor rax, rax
    xor rdi, rdi
    mov al, 60                      ; exit syscall
    syscall

    ender:
    call starter	                ; put string address on the stack
    msg:    db      'hello', 0x0A
    .len:   equ     $-msg

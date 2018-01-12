global _start
section .text
_start:
    needle0: 
    jmp there
    here: 
    pop rdi
    xor rax, rax
    xor rsi, rsi
    xor rdx, rdx
    mov al, 83
    mov si, 0o777
    syscall
    xor rax, rax
    mov al, 60
    xor rdi, rdi
    syscall
    there: call here
    db          "evildir"

global _start

_start:

jmp message
begin:
mov     rax, 1
mov     rdi, 1
pop     rsi
mov     rdx, 21
syscall

mov     rax, 60
mov     rdi, 0
syscall

message:
call begin
db      "Hey there babycakes!", 0x0A



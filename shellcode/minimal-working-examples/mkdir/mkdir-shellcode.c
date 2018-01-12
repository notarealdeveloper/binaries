#include <stdio.h>
#include <string.h>

/* OMG it works! :D
 * Note: This was my first shellcode thing where I wrote 
 * the position-independent assembly, extracted the shellcode
 * from an objdump of that assembly, and ran the code from a C program.
 * Hot diggity damn this is fun. ;)
 */

char *shellcode = 
    "\xeb\x1c\x5f\x48\x31\xc0\x48\x31\xf6\x48\x31\xd2\xb0"
    "\x53\x66\xbe\xff\x01\x0f\x05\x48\x31\xc0\xb0\x3c\x48"
    "\x31\xff\x0f\x05\xe8\xdf\xff\xff\xff\x65\x76\x69\x6c\x64\x69\x72";

int main(void)
{
    printf("Length: %d\n", strlen(shellcode));
    ((void(*)()) shellcode)();
    // asm("jmp %0\n"::"r"(shellcode):);    // This works too
    return 0;
}


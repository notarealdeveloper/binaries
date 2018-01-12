#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Helpful ROP link:
 * http://codearcana.com/posts/2013/05/28/introduction-to-return-oriented-programming-rop.html
 */

/* Let's just jump into libc to make sure we have the basics down. */

/* Remember to turn ASLR off or else this is gonna be totally fucked. */

void boop(void) {
    puts("Sup bitches?");
}

char *str = "Hey there babycakes";
char *lol = "Omg it worked!";
char *dst;

int main(int argc, char *argv[])
{
    unsigned long libc_address = 0x00007ffff7a3f000;
    unsigned long puts_offset  = 0x0000000000067d60;    /* obtained from running nm -D /lib64/libc.so.6 | grep puts */
    unsigned long puts_address = libc_address + puts_offset;

    asm("mov %1, %0\n\t"
        "add $1, %0"
        : "=r" (dst)
        : "r" (str));

    printf("%s\n", dst);

    asm("mov %1, %%rsi\n\t"
        : "=S" (dst)
        : "r" (str));

    printf("%s\n", dst);

    asm("mov %1, %%rsi\n\t"
        : "=S" (dst)
        : "r" (str));

    // We get to 0x00007ffff7aa6d60
    (*(void(*)())0x0000000000400506)();

    asm("mov %1, %%rdi\n\t"
        : "=a" (dst)
        : "r" (lol));

    /* Jump into libc at the puts offset! */
    (*(void(*)())puts_address)();

    /* Let's do it again, but now with the raw pointer value ;) */
    asm("mov %1, %%rdi\n\t"
        : "=a" (dst)
        : "r" (lol));

    /* Jump into libc at the puts offset! */
    (*(void(*)())0x00007ffff7aa6d60)();

    /* This works too. Makes the assembly simpler. */
    asm("mov %0, %%rdi\n\t"
        :
        : "r" (lol));

    /* Jump into libc at the puts offset! */
    (*(void(*)())0x00007ffff7aa6d60)();


    return 0;
}

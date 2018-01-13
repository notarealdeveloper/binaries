#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>

char data_chr = 1;
int  data_int = 2;

char bss_chr;
int  bss_int;

int main(int argc, char *argv[])
{
    bss_chr = 3;
    bss_int = 4;

    char *heap_chr = malloc(sizeof(char));
    int  *heap_int = malloc(sizeof(int));
    *heap_chr = 5;
    *heap_int = 6;

    char stack_chr = 7;
    int  stack_int = 8;


    printf("data_chr  is @ 0x%08x, val = %d\n",   &data_chr, data_chr);
    printf("data_int  is @ 0x%08x, val = %d\n\n", &data_int, data_int);

    printf("bss_chr   is @ 0x%08x, val = %d\n",   &bss_chr, bss_chr);
    printf("bss_int   is @ 0x%08x, val = %d\n\n", &bss_int, bss_int);

    printf("heap_chr  is @ 0x%08x, val = %d\n",   heap_chr, *heap_chr);
    printf("heap_int  is @ 0x%08x, val = %d\n\n", heap_int, *heap_int);

    printf("stack_chr is @ 0x%08x, val = %d\n",   &stack_chr, stack_chr);
    printf("stack_int is @ 0x%08x, val = %d\n\n", &stack_int, stack_int);

    printf("All four of these segments are vulnerable to overflows,\n" 
           "as we will now demonstrate. We'll change all four ints by\n"
           "using only statements involving the char variables.\n\n");

    *((&data_chr)  + 0x04)  = 66;
    *((&bss_chr)   + 0x04)  = 77;
    *(heap_chr     + 0x20)  = 88;
    *((&stack_chr) - 0x07)  = 99;

    printf("data_int  is @ 0x%08x, val = %d\n", &data_int,  data_int);
    printf("bss_int   is @ 0x%08x, val = %d\n", &bss_int,   bss_int);
    printf("heap_int  is @ 0x%08x, val = %d\n", heap_int,  *heap_int);
    printf("stack_int is @ 0x%08x, val = %d\n", &stack_int, stack_int);

    free(heap_chr);
    free(heap_int);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

/* Remember that memory can only be addressed in multiples of the word
 * size.  A word in our case is 8 bytes, or 64 bits. So a 9 byte buffer is
 * really going to take 16 bytes (2 words) of memory.
 */

void (*evil())
{
    exit(printf("haha gotcha bitch!\n"));
}

int function(int a, int b, int c) 
{
    char buf[8] = {0,1,2,3,4,5,6,7};

    buf[24] = ((long)evil >> 0)  & 0xff;
    buf[25] = ((long)evil >> 8)  & 0xff;
    buf[26] = ((long)evil >> 16) & 0xff;
    buf[27] = ((long)evil >> 24) & 0xff;

    printf("Derp derp code\n");

    return 0;
}

void main() {
    function(1,2,3);
}

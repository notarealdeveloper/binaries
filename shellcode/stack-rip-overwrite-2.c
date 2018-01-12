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

    long *newrip = (long *)(buf + 24);
    *newrip = (long)evil;

    printf("Derp derp code\n");

    return 0;
}

void main() {
    function(1,2,3);
}

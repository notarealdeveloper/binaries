#include <stdio.h>
#include <stdlib.h>

void function(int a, int b, int c) {
    char sex = 'm';
    char buf[8] = {0,1,2,3,4,5,6,7};
    buf[15] = 0x66;
    buf[16] = 0x65;
    buf[17] = 0x6d;
    buf[18] = 0x61;
    buf[19] = 0x6c;
    buf[20] = 0x65;
    buf[21] = 0x21;
    buf[22] = 0x00;
    printf("Your sex is %s\n", (&sex));
}

void main() {
    function(1,2,3);
}

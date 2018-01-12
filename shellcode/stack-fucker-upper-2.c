#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
char *str = "haha!";

void function(int a, int b, int c) {
    char *sex = "male";
    char buf[8] = {0,1,2,3,4,5,6,7};
    buf[8]  = (((long)str >> 0)  & 0xff);
    buf[9]  = (((long)str >> 8)  & 0xff);
    buf[10] = (((long)str >> 16) & 0xff);
    buf[11] = (((long)str >> 24) & 0xff);
    printf("Your sex is %s\n", sex);
}

void main() {
    function(1,2,3);
}

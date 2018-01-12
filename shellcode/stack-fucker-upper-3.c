#include <stdio.h>
#include <stdlib.h>

typedef unsigned char u8;
char *str = "haha gotcha bitch!";

void function(int a, int b, int c) {
    char *name = "jason";
    char buf[8] = {0,1,2,3,4,5,6,7};
    buf[8] = (long)str;
    printf("Your name is %s\n", name);
}

void main() {
    function(1,2,3);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "boop.h"

int main() {
    double x;
    int i;
    for (i = 0; i < 3; i++) {
		x = i * 69;
        printf("boop(%f) == %f\n", x, boop(x));
    }
    return 0;
}


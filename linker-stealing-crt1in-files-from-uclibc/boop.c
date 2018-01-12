#include <stdio.h>
#include "boop.h"

double boop(double x) {
    double y;
    printf("It's working!\n");
    y = cos(cos(cos(x)));
    return y;
}

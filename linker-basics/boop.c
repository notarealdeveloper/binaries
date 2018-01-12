#include "boop.h"

double boop(double x) {
    double y;
    //printf("pre-booped value: %f\n", x);
    y = cos(cos(cos(x)));
    //printf("post-booped value: %f\n", y);
    return y;
}

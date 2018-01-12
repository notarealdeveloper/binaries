#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
        puts(argv[1]);
    else
        puts("Hello world!");

    /*
    puts("hello");
    puts("Hello");  // This one fails!!! XD
    puts("jello");
    puts("Jello");
    */
    return 0;
}

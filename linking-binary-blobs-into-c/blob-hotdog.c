#include <stdio.h>
 
extern unsigned char hotdog_start;
extern unsigned char hotdog_end;
extern unsigned char hotdog_size;

int main() {

    unsigned char *pblob = &hotdog_start;

    while (pblob < &hotdog_end) {
        printf("%lu: %02X\n", pblob - &hotdog_start, *pblob);
        pblob++;
    }
    printf("size: %p\n", &hotdog_size);

    return 0;
}

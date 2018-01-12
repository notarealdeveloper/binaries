#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>          /* For open, O_RDONLY, etc. */
#include <sys/mman.h>       /* For mmap, munmap, etc. */

/* Note: Remember to enable execstack after you compile, so we don't SEGV
 * f=mmap-execution && gcc -g -o "$f"{,.c} && execstack -s "$f" && ./"$f"
 */

#define     start   0
#define     prot    PROT_READ | PROT_WRITE | PROT_EXEC
#define     length  1
#define     flags   MAP_SHARED /* Needed to be able to use msync() */
#define     offset  0

int main(int argc, char *argv[])
{
    int fd;
    char *p;

    fd = open("hello", O_RDWR);
    p = mmap(start, length, prot, flags, fd, offset);
    p += 0x80;

    int i = 0;
    char *instructions = (char *)malloc(50);
    while (i < 0xba-0x80) {
        printf("%02x ", (unsigned char)*p);
        *(instructions + i) = *p;
        i++;
        *p++;
    }
    ((void (*)())instructions)();

    free(instructions);
    return 0;
}


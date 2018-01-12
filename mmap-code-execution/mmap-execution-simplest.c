#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>          /* For open, O_RDONLY, etc. */
#include <sys/mman.h>       /* For mmap, munmap, etc. */

/* Note: Remember to enable execstack after you compile, so we don't SEGV
 */

#define     start   0
#define     prot    PROT_READ | PROT_WRITE | PROT_EXEC
#define     length  1
#define     flags   MAP_SHARED /* Needed to be able to use msync() */
#define     offset  0

int main(int argc, char *argv[])
{
    int fd = open("hello", O_RDWR);
    void (*code)() = 0x80 + mmap(start, length, prot, flags, fd, offset);
    code();
    return 0;
}


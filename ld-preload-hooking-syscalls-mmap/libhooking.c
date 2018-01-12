#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/mman.h>

/* Note: this *is* working, but apparently not that many programs use mmap.
 * The way I print the buffer to a logfile is lazy, and terminates at soon
 * as we hit a zero, but in testing, most programs didn't even get an empty
 * entry saying MMAP SYSCALL INVOKED. Interesting. 
 */
void *mmap(void *addr,size_t len,int prot,int flags,int fildes,off_t off)
{
    /* Declare the pointer function */
    ssize_t (*real_mmap)(void *addr, size_t len, int prot, 
                         int flags, int fildes, off_t off);

    /* Define the wrapper function */
    real_mmap = dlsym(RTLD_NEXT, "mmap");

    /* Call it for them ;) */
    char *p = (char *)real_mmap(addr, len, prot, flags, fildes, off);

    FILE *logfile = fopen("logfile", "a+");
    fprintf(logfile, "MMAP SYSCALL INVOKED:\n%s\n\n", p);
    fclose(logfile);

    /* Let 'em have the pointer */
    return (void *)p;
}

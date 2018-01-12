#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/mman.h>

ssize_t read(int fildes, void *buf, size_t nbyte)
{
    /* Declare the pointer function */
    ssize_t (*real_read)(int fildes, void *buf, size_t nbyte);

    /* Define the wrapper function */
    real_read = dlsym(RTLD_NEXT, "read");

    if (nbyte > 0) {
        FILE *logfile = fopen("logfile", "a+");
        fprintf(logfile, "READ SYSCALL INVOKED:\n%s\n\n", (char *)buf);
        fclose(logfile);
    }

    return real_read(fildes, buf, nbyte);
}

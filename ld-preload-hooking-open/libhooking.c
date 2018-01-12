#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Note: We ignore the varargs "..." thing at the end because I forget the details of how to use that.
 * This seems to make the open call fail once we start calling applications that open odd kinds of files,
 * (for example, dconf seems to do this, and calling eog with this LD_PRELOAD library loaded eventually
 * causes some pretty serious fuckery until we reboot and start over.
 */

int open(const char *pathname, int flags, ...) {
    int ret;

    int (*new_open)(const char *pathname, int flags);
    new_open = dlsym(RTLD_NEXT, "open");

    // ret = new_open("/etc/hosts", flags);
    printf("OPENED: %s\n", pathname);
    ret = new_open(pathname, flags);
    return ret;
}

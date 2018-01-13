#include <sys/ptrace.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/syscall.h>

/* 
 * How to run this:
 * ./target             # Prints "Hi\nSup Guys?\n"
 * ./tracer ./target    # Prints "Hi\n"
 */


/* 
 * Ooh these are clever.
 * http://www.exploit-db.com/papers/13061/
 */

int main(int argc, char *argv[]) {

    if (argc < 2) {
	    printf("Usage: %s <progname>\n", argv[0]);
	    exit(1);
	}

    int orig_syscall = 0;
    int status;
    struct user_regs_struct regs;
    pid_t pid;

    pid = fork();

    /* child */
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl(argv[1], argv[1], NULL);

    /* parent */
    } else {
        wait (&status); /* wait for the child */
	    while(1) {
            /* restart the stopped child and send a SIGTRAP when */
            /* a syscall is called to inspect the arguments */
	        ptrace(PTRACE_SYSCALL, pid, 0, 0);
	        wait(&status);                  /* wait for the child */
	        ptrace(PTRACE_GETREGS, pid, 0, &regs);
	        orig_syscall = regs.orig_rax;   /* get the syscall number */

		    if (orig_syscall == SYS_write) {
		        regs.rdx = 3;
		        ptrace(PTRACE_SETREGS, pid, 0, &regs);
                break; /* Prevents it from hanging */
		    }
		}
	}

	ptrace(PTRACE_DETACH, pid, NULL, NULL);
	return 0;

}

/* end of tracer1.c */

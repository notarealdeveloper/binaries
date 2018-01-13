#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* 
 * Use with: ./micro-strace ./dummy
 * or more generally, 
 * ./micro-strace <progname>
 */

int main(int argc, char* argv[]) {   
    pid_t child;
    int status;

    if (argc == 1) {
        printf("Yo, call me with a program name as an argument\n");
        exit(0);
    }

    child = fork();
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(argv[1], argv+1);
    } else {
        while (waitpid(child, &status, 0) && ! WIFEXITED(status)) {
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, child, NULL, &regs);
            printf("syscall %ld from pid %d\n", regs.orig_rax, child);
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }
    exit(0);
}

/*
    ptrace(PTRACE_PEEKDATA, pid, addr, NULL)

    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    waitpid(pid, &status, 0);
    // wait(NULL);

    ptrace(PTRACE_GETREGS, pid, NULL, &regs);

    ret = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, NULL);
    printf("RIP: %lx Instruction executed: %lx\n", regs.rip, ret);

    ret = ptrace(PTRACE_PEEKTEXT, pid, regs.rax, NULL);
    printf("RAX: %lx The RAX register is: %lx\n", regs.rax, ret);

    ptrace(PTRACE_DETACH, pid, NULL, NULL);
*/

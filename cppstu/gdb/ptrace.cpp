#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>

int main() {
    pid_t child;
    struct user_regs_struct regs;

    child = fork();
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl("/bin/ls", "ls", nullptr);
        getchar();
    } else {
        wait(nullptr);
        ptrace(PTRACE_GETREGS, child, nullptr, &regs);
        printf("Register: rdi[%llu], rsi[%llu], rdx[%llu], rax[%llu], orig_rax[%llu]\n", regs.rdi,
               regs.rsi, regs.rdx, regs.rax, regs.orig_rax);
        getchar();
        ptrace(PTRACE_CONT, child, nullptr, nullptr);
    }

    return 0;
}
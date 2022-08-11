#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;

constexpr int kStackSize = 40960;

int func(void *arg) {
    printf("thread(%d) enter.\n", gettid());
    sleep(1);
    printf("thread(%d) exit.\n", gettid());

    return 0;
}

int main() {
    int thread_pid;
    int status;
    int w;

    while (true) {
        auto before = chrono::steady_clock::now();
        void *addr = mmap(nullptr, kStackSize, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
        if (!addr) {
            perror("mmap");
            goto error;
        }
        auto take = chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now() - before)
                        .count();
        printf("mmap take %ldns\n", take);
        printf("create new thread ...\n");
        thread_pid = clone(&func, (void *)((char *)addr + kStackSize),
                           CLONE_SIGHAND | CLONE_FS | CLONE_VM | CLONE_FILES, nullptr);
        if (thread_pid != 1) {
            do {
                w = waitpid(-1, nullptr, __WCLONE | __WALL);
                if (w == -1) {
                    perror("waitpid");
                    goto error;
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        sleep(10);
    }

error:
    return 0;
}
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void* f(void*) {
    int pid = getpid();
    int ppid = getppid();
    int id = gettid();
    int gid = getgid();
    printf("th: tid=%d, gid=%d, pid=%d, ppid=%d\n", id, gid, pid, ppid);
    return nullptr;
}

int main() {
    int pid = getpid();
    int ppid = getppid();
    int id = gettid();
    int gid = getgid();
    printf("main: tid=%d, gid=%d, pid=%d, ppid=%d\n", id, gid, pid, ppid);

    pthread_t tid;
    int ret = pthread_create(&tid, nullptr, f, nullptr);

    pthread_join(tid, nullptr);

    return 0;
}
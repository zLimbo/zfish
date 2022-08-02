#include <unistd.h>

#include <cstdio>

int main() {
    execlp("/bin/ls", "ls", nullptr);
    getchar();
    return 0;
}
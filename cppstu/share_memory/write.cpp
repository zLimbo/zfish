#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr int kMapSize = 4096;

int main() {
    int fd = open("tmp.log", O_CREAT | O_RDWR, 0644);
    void *res = mmap(nullptr, kMapSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (res == MAP_FAILED) {
        printf("mapped failed\n");
        exit(1);
    }
    struct stat st;
    fstat(fd, &st);
    printf("size: %ld\n", (long)st.st_size);
    int n = ftruncate(fd, 200);

    char *p = (char *)res;
    for (int i = 0; i < 200; ++i) {
        p[i] = 'f';
    }
    printf("\nwrite ok\n");
    getchar();
    msync(res, kMapSize, 0);
    getchar();
    printf("\ndone.\n");

    return 0;
}
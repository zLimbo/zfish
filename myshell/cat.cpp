#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

constexpr int kBufSize = 1024;

void cat(int fd) {
    char buf[kBufSize];
    int n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if ((n = write(1, buf, n)) < 0) {
            fprintf(stderr, "write 1 error.\n");
            exit(-1);
        }
    }
    if (n < 0) {
        fprintf(stderr, "read %d error.\n", fd);
        exit(-1);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cat(0);
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        if (int fd = open(argv[i], O_RDONLY); fd >= 0) {
            cat(fd);
        } else {
            fprintf(stderr, "open %s fail.\n", argv[i]);
        }
    }
    return 0;
}
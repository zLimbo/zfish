#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string_view>

constexpr int kBufSize = 1024;

void cat(int fd) {
    char buf[kBufSize];
    int n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if ((n = write(1, buf, n)) < 0) {
            constexpr std::string_view msg = "write error";
            write(2, msg.data(), msg.size());
        }
    }
    if (n < 0) {
        constexpr std::string_view msg = "read error";
        write(2, msg.data(), msg.size());
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
        }
    }
    return 0;
}
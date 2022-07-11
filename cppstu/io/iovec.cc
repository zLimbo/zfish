#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/uio.h>
using namespace std;

int main() {
    char buf[10][32];
    memset(buf, 0, sizeof(buf));

    struct iovec iov[10];
    for (int i = 0; i < 10; ++i) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = 30;
    }
    {
        string tmp;
        for (int i = 0; i < 1000; ++i) {
            tmp += " " + to_string(i);
        }
        ofstream fs{"/tmp/fish.txt"};
        fs << tmp;
        printf("write %d bytes\n", (int)tmp.size());
    }
    int fd = open("/tmp/fish.txt", O_RDONLY);
    int n = readv(fd, iov, 10);
    printf("n: %d\n", n);
    for (int i = 0; i < 10; ++i) {
        printf("buf[%d]: %s\n", i, buf[i]);
        n -= strlen(buf[i]);
        if (n <= 0) {
            break;
        }
    }

    return 0;
}
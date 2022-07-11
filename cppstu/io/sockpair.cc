#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <thread>

using namespace std;

int main() {
    struct sockaddr_un addr;
    string path{"/tmp/fish"};
    strncpy(addr.sun_path, path.c_str(), path.size());
    addr.sun_family = AF_UNIX;

    int fd[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

    close(STDOUT_FILENO);
    int out_fd = dup(fd[1]);
    assert(out_fd == STDOUT_FILENO);

    auto f1 = async(launch::async, [&] {
        for (int i = 0; i < 3; ++i) {
            char buf[10];
            snprintf(buf, sizeof(buf), "t1 %d", i);
            write(fd[0], buf, strlen(buf));
            int n = read(fd[0], buf, sizeof(buf));
            // printf("t1 read: %s\n", buf);
            fprintf(stderr, "t1 read: %s\n", buf);
        }
        fprintf(stderr, "t1 close fd[0]\n");
        close(fd[0]);
    });

    auto f2 = async(launch::async, [&] {
        while (true) {
            char buf[10];
            int n = read(fd[1], buf, sizeof(buf));
            assert(n >= 0);
            if (n == 0) {
                fprintf(stderr, "t2 close fd[1]\n");
                close(fd[1]);
                break;
            }
            // printf("t2 read: %s\n", buf);
            fprintf(stderr, "t2 read: %s\n", buf);
            snprintf(buf, sizeof(buf), "t2 %s", buf + 3);
            // write(fd[1], buf, strlen(buf));
        }
    });

    return 0;
}
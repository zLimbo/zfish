#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

const char *kSockPath = "/tmp/tmp.sock";
const int kListenLen = 5;
const int kBufSize = 1024;

int main() {
    pid_t pid = getpid();

    printf("%d | tcpsockserver\n", pid);

    int listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    assert(listenfd > 0);

    sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, kSockPath);

    int ret = bind(listenfd, (const sockaddr *)&addr, sizeof(addr));
    assert(ret >= 0);

    ret = listen(listenfd, kListenLen);
    assert(ret >= 0);

    printf("%d | listen ...\n", pid);
    while (true) {
        sockaddr_un cliaddr;
        socklen_t len;
        int connfd = accept(listenfd, (sockaddr *)&cliaddr, &len);
        printf("%d | connfd: %d\n", pid, connfd);
        assert(connfd >= 0);

        pid_t pid = fork();
        // 进入子进程
        if (pid == 0) {
            pid = getpid();
            printf("%d | build connect, ppid: %d\n", pid, getppid());
            while (true) {
                char buf[kBufSize];
                bzero(buf, sizeof(buf));
                auto nbytes = recv(connfd, buf, kBufSize, MSG_WAITALL);
                if (nbytes == 0) break;
                printf("%d | read: %s\n", pid, buf);
            }
            printf("%d | close connect\n", pid);
            close(connfd);
            return 0;
        }
    }

    close(listenfd);
    unlink(kSockPath);

    return 0;
}
#include <cstdio>
#include <cassert>
#include <sys/unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>

const char *kSockPath = "/tmp/tmp.sock";
const int kBufSize = 1024;

int main() {
    int connfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, kSockPath);

    int ret = connect(connfd, (const sockaddr *)&addr, sizeof(addr));
    assert(ret >= 0);

    printf("connect success\n");
    char buf[kBufSize];
    while (true) {
        printf(">>> ");
        if (nullptr == fgets(buf, kBufSize, stdin)) {
            break;
        }
        auto nbytes = send(connfd, buf, strlen(buf), MSG_WAITALL);
        assert(nbytes >= 0);
    }
    printf("close connect\n");
    close(connfd);

    return 0;
}
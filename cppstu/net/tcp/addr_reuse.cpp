#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int start_server(__uint32_t host) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("%s:%d: bind socket error: %s(errno: %d)\n", __FILE__, __LINE__, strerror(errno),
               errno);
        close(listenfd);
        exit(-1);
    }
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on))) {
        printf("%s:%d: bind socket error: %s(errno: %d)\n", __FILE__, __LINE__, strerror(errno),
               errno);
        close(listenfd);
        exit(-1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = host;
    servaddr.sin_port = htons(6666);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        printf("%s:%d: bind socket error: %s(errno: %d)\n", __FILE__, __LINE__, strerror(errno),
               errno);
        close(listenfd);
        exit(-1);
    }

    return listenfd;
}
int main() {
    int fd1 = start_server(htonl(INADDR_ANY));
    printf("1\n");
    int fd2 = start_server(htonl(INADDR_ANY));
    printf("2\n");

    if (listen(fd1, 10) == -1) {
        printf("%s:%d: bind socket error: %s(errno: %d)\n", __FILE__, __LINE__, strerror(errno),
               errno);
        close(fd1);
        exit(-1);
    }

    if (listen(fd2, 10) == -1) {
        printf("%s:%d: bind socket error: %s(errno: %d)\n", __FILE__, __LINE__, strerror(errno),
               errno);
        close(fd2);
        exit(-1);
    }

    getchar();
}
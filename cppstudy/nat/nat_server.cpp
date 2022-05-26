
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <cstring>
#include <cassert>

using namespace std;

int main(int argc, char **argv) {
    assert(argc >= 2);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(stoi(argv[1]));

    struct sockaddr_in xaddr, yaddr;
    socklen_t xlen = sizeof(xaddr), ylen = sizeof(yaddr);
    bzero(&xaddr, sizeof(xaddr));
    bzero(&yaddr, sizeof(yaddr));

    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret =
        bind(server_fd, (const sockaddr *)&server_addr, sizeof(server_addr));
    assert(ret >= 0);

    printf("listen | %s:%d\n", inet_ntoa(server_addr.sin_addr),
           ntohs(server_addr.sin_port));

    char xbuf[256], ybuf[256];
    bzero(xbuf, sizeof(xbuf));
    bzero(ybuf, sizeof(ybuf));

    recvfrom(server_fd, xbuf, 256, 0, (sockaddr *)&xaddr, &xlen);
    char *xip = inet_ntoa(xaddr.sin_addr);
    int xport = ntohs(xaddr.sin_port);
    printf("x %s:%d | msg: %s\n", xip, xport, xbuf);

    recvfrom(server_fd, ybuf, 256, 0, (sockaddr *)&yaddr, &ylen);
    char *yip = inet_ntoa(yaddr.sin_addr);
    int yport = ntohs(yaddr.sin_port);
    printf("y %s:%d | msg: %s\n", yip, yport, ybuf);

    bzero(xbuf, sizeof(xbuf));
    bzero(ybuf, sizeof(ybuf));
    snprintf(xbuf, 256, "%s %d", yip, yport);
    snprintf(ybuf, 256, "%s %d", xip, xport);

    printf("send to %s:%d | msg: %s\n", xip, xport, xbuf);
    sendto(server_fd, xbuf, strlen(xbuf), 0, (sockaddr *)&xaddr, sizeof(xaddr));
    printf("send to %s:%d | msg: %s\n", yip, yport, ybuf);
    sendto(server_fd, ybuf, strlen(ybuf), 0, (sockaddr *)&yaddr, sizeof(yaddr));

    getchar();

    return 0;
}
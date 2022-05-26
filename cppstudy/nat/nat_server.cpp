
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

const int kBufLen = 256;

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

    char xbuf[kBufLen], ybuf[kBufLen];
    bzero(xbuf, kBufLen);
    bzero(ybuf, kBufLen);

    recvfrom(server_fd, xbuf, kBufLen, 0, (sockaddr *)&xaddr, &xlen);
    const char *xip = string(inet_ntoa(xaddr.sin_addr)).c_str();
    int xport = ntohs(xaddr.sin_port);
    printf("x %s:%d | msg: %s\n", xip, xport, xbuf);

    recvfrom(server_fd, ybuf, kBufLen, 0, (sockaddr *)&yaddr, &ylen);
    const char *yip = string(inet_ntoa(yaddr.sin_addr)).c_str();
    int yport = ntohs(yaddr.sin_port);
    printf("y %s:%d | msg: %s\n", yip, yport, ybuf);

    bzero(xbuf, kBufLen);
    bzero(ybuf, kBufLen);
    snprintf(xbuf, kBufLen, "%s %d", yip, yport);
    snprintf(ybuf, kBufLen, "%s %d", xip, xport);

    printf("send to %s:%d | msg: %s\n", xip, xport, xbuf);
    sendto(server_fd, xbuf, strlen(xbuf), 0, (sockaddr *)&xaddr, sizeof(xaddr));
    printf("send to %s:%d | msg: %s\n", yip, yport, ybuf);
    sendto(server_fd, ybuf, strlen(ybuf), 0, (sockaddr *)&yaddr, sizeof(yaddr));

    getchar();

    return 0;
}
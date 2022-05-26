
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
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    assert(argc >= 5);
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);
    client_addr.sin_port = htons(stoi(argv[2]));

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[3]);
    server_addr.sin_port = htons(stoi(argv[4]));

    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(client_fd, (const sockaddr *)&client_addr, sizeof(client_addr));

    const char *hello = "hello";
    printf("%s:%s => %s:%s | msg: %s\n", argv[1], argv[2], argv[3], argv[4],
           hello);
    int ret = sendto(client_fd, hello, strlen(hello), 0,
                     (sockaddr *)&server_addr, sizeof(server_addr));
    assert(ret != -1);

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    socklen_t len = sizeof(addr);
    char buf[256];
    bzero(buf, sizeof(buf));
    recvfrom(client_fd, buf, 256, 0, (sockaddr *)&addr, &len);

    char *ip = inet_ntoa(addr.sin_addr);
    int port = ntohs(addr.sin_port);
    printf("%s:%d | msg: %s\n", ip, port, buf);

    sscanf(buf, "%s %d", ip, &port);

    struct sockaddr_in peer_addr;
    bzero(&peer_addr, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = inet_addr(ip);
    peer_addr.sin_port = htons(port);

    printf("try connect %s:%d\n", ip, port);
    sendto(client_fd, hello, strlen(hello), 0, (const sockaddr *)&peer_addr,
           sizeof(peer_addr));
    getchar();
    sendto(client_fd, hello, strlen(hello), 0, (const sockaddr *)&peer_addr,
           sizeof(peer_addr));
    bzero(buf, sizeof(buf));
    recvfrom(client_fd, buf, 256, 0, (sockaddr *)&peer_addr, &len);
    ip = inet_ntoa(peer_addr.sin_addr);
    port = ntohs(peer_addr.sin_port);
    printf("%s:%d | msg: %s\n", ip, port, buf);
    getchar();

    return 0;
}
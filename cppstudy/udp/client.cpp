
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <cassert>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <cstring>

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
    bind(client_fd, (sockaddr *)&client_addr, sizeof(client_addr));

    const char *buf = "hello";
    printf("%s:%s => %s:%s | msg: %s\n", argv[1], argv[2], argv[3], argv[4],
           buf);
    sendto(client_fd, buf, strlen(buf), 0, (sockaddr *)&server_addr,
           sizeof(server_addr));

    printf("listen %s:%s\n", argv[1], argv[2]);
    while (true) {
        struct sockaddr_in client_addr2;
        bzero(&client_addr2, sizeof(client_addr2));
        socklen_t len;
        char buf[1024];
        bzero(buf, sizeof(buf));
        recvfrom(client_fd, buf, 1024, 0, (sockaddr *)&client_addr2, &len);

        printf("from %s:%d | msg: %s\n", inet_ntoa(client_addr2.sin_addr),
               ntohs(client_addr2.sin_port), buf);
    }
    // getchar();

    return 0;
}
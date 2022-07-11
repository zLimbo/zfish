
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

using namespace std;

int main(int argc, char **argv) {
    assert(argc >= 3);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(stoi(argv[2]));

    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr));

    printf("server %s:%s\n", argv[1], argv[2]);
    while (true) {
        struct sockaddr_in client_addr;
        bzero(&client_addr, sizeof(client_addr));
        socklen_t len;
        char buf[1024];
        bzero(buf, sizeof(buf));
        recvfrom(server_fd, buf, 1024, 0, (sockaddr *)&client_addr, &len);

        printf("from %s:%d | msg: %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), buf);

        sendto(client_fd, buf, strlen(buf), 0, (sockaddr *)&client_addr,
               sizeof(client_addr));
    }

    return 0;
}
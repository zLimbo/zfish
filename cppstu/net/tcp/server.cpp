
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <cassert>
#include <cstdio>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    assert(argc >= 3);
    char *ip = argv[1];
    int port = std::stoi(argv[2]);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
               sizeof(opt));
    int ret =
        bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        perror("err: ");
        exit(-1);
    }
    assert(ret >= 0);
    ret = listen(listenfd, 20);
    assert(ret >= 0);

    const char *saddr = inet_ntoa(server_addr.sin_addr);
    int sport = ntohs(server_addr.sin_port);
    printf("server %s:%d\n", saddr, sport);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t slen = sizeof(client_addr);
        printf("accpet ...\n");
        int clientfd = accept(listenfd, (struct sockaddr *)&client_addr, &slen);
        assert(clientfd >= 0);
        const char *addr = inet_ntoa(client_addr.sin_addr);
        int port = ntohs(client_addr.sin_port);
        printf("client %s:%d\n", addr, port);

        close(clientfd);
    }

    close(listenfd);

    return 0;
}
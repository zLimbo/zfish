
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
using namespace std;

int main() {
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8001);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    int ret = bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    assert(ret >= 0);
    ret = listen(listenfd, 20);
    assert(ret >= 0);

    const char *server_addr = inet_ntoa(addr.sin_addr);
    int server_port = ntohs(addr.sin_port);
    printf("server %s:%d\n", server_addr, server_port);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t slen = sizeof(client_addr);
        printf("accpet ...\n");
        int clientfd = accept(listenfd, (struct sockaddr *)&client_addr, &slen);
        assert(clientfd >= 0);
        const char *addr = inet_ntoa(client_addr.sin_addr);
        int port = ntohs(client_addr.sin_port);
        printf("client %s:%d\n", addr, port);
    }

    return 0;
}
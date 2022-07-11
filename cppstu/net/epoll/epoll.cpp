
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/file.h>
#include <cstring>
#include <cassert>

using namespace std;

int SetNonblocking(int fd) {
    int old_flag = fcntl(fd, F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_flag);
    return old_flag;
}

void EpollAddFd(int ep_fd, int fd, bool et) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (et) {
        event.events |= EPOLLET;
    }
    epoll_ctl(ep_fd, EPOLL_CTL_ADD, FD, &event);
}

void EpollServer(int port, bool et) {
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(port);

    int srv_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(srv_fd > 0);
    int ret = bind(srv_fd, (const sockaddr *)&srv_addr, sizeof(srv_addr));
    assert(ret >= 0);
    ret = listen(srv_fd, 20);
    assert(ret >= 0);

    int ep_fd = epoll_create(20);
    assert(ep_fd >= 0);

    EpollAddFd(ep_fd, srv_fd, false);
    
}

int main(int argc, char **argv) {
    assert(argc >= 2);
    EpollServer(stoi(argv[1]), true);

    return 0;
}
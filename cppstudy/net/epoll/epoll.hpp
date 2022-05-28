#ifndef EPOLL_H
#define EPOLL_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>
#include <cstring>

class EpollServer {
public:
    EpollServer(int port, bool et) : port_(port), et_(et) {
        struct sockaddr_in srv_addr;
        bzero(srv_addr, sizeof(srv_addr));
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        srv_addr.sin_port = htons(port);

        srvfd_ = socket(AF_INET, SOCK_STREAM, 0);
        assert(srvfd_ > 0);
        int ret = bind(srvfd_, (const sockaddr *)&srv_addr, sizeof(srv_addr));
        assert(ret >= 0);
        ret = listen(srvfd_, 20);
        assert(ret >= 0);

        epfd_ = epoll_create(20);
        assert(epfd_ >= 0);

        EpollAddFd(srvfd_, false);

        struct epoll_event events[kMaxEventNum];
        while (true) {
            int nevent = epoll_wait(epfd_, events, kMaxEventNum, -1);
            assert(nevent >= 0);
            printf("epoll wait %d events\n", nevent);
            for (int i = 0; i < nevent; ++i) {
                struct epoll_event &event = events[i];
                if (event.data.fd == srvfd_) {
                    HandleConnect();
                }
            }
        }
    }

    void HandleConnect() {
        struct sockaddr_in cli_addr;
        struct socklen_t len = sizeof(cli_addr);
        bzero(&cli_addr, sizeof(cli_addr));
        int clifd = accept(srvfd_, (sockaddr *)&cli_addr, &len);
        assert(clifd >= 0);
        
    }

    int SetNonblocking(int fd) {
        int old_flag = fcntl(fd, F_GETFL);
        int new_flag = old_flag | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_flag);
        return old_flag;
    }

    void EpollAddFd(int fd, bool et) {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN;
        if (et) {
            event.events |= EPOLLET;
        }
        epoll_ctl(epfd_, EPOLL_CTL_ADD, FD, &event);
    }

private:
    bool et_;
    int port_;
    int epfd_;
    int srvfd_;

    constexpr static int kMaxEventNum = 1024;
};

#endif  // EPOLL_H
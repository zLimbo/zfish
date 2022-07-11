#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

constexpr int MAX_EVENT_NUMBER = 1024;
constexpr int BUFFER_SIZE = 5;

enum TRIGGER_MODE { LT, ET };

int setNonblocking(int fd) {
    int oldFlag = fcntl(fd, F_GETFL);
    int newFlag = oldFlag | O_NONBLOCK;
    fcntl(fd, F_SETFL, newFlag);
    return oldFlag;
}

void addFd(int epollFd, int fd, bool enableET) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enableET) {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
    setNonblocking(fd);
}

void readLT(int eventFd) {
    static int accessCount = 0;
    printf("readLT() accessCount = %d\n", ++accessCount);
    char buf[BUFFER_SIZE];
    bzero(buf, BUFFER_SIZE);
    int ret = read(eventFd, buf, BUFFER_SIZE - 1);
    if (ret <= 0) {
        printf("read finish\n");
        close(eventFd);
        return;
    }
    printf("read %d bytes, text: %s\n", ret, buf);
}

void readET(int eventFd) {
    static int accessCount = 0;
    printf("readET() accessCount = %d\n", ++accessCount);
    char buf[BUFFER_SIZE];
    while (true) {
        bzero(buf, BUFFER_SIZE);
        int ret = read(eventFd, buf, BUFFER_SIZE - 1);
        if (ret < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("read finish\n");
                close(eventFd);
                return;
            }
        } else if (ret == 0) {
            close(eventFd);
            return;
        }
        printf("read %d bytes, text: %s\n", ret, buf);
    }
}

void handle(struct epoll_event *events, int num, int epollFd, int listenFd,
            TRIGGER_MODE triggerMode) {
    for (int i = 0; i < num; ++i) {
        int eventFd = events[i].data.fd;
        if (eventFd == listenFd) {
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientFd =
                accept(listenFd, (sockaddr *)&clientAddr, &clientAddrLen);
            static int connectCount = 0;
            printf("[connect %d] %s:%d\n", ++connectCount,
                   inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
            addFd(epollFd, clientFd, TRIGGER_MODE::ET == triggerMode);
        } else if (events[i].events & EPOLLIN) {
            switch (triggerMode) {
                case TRIGGER_MODE::LT:
                    readLT(eventFd);
                    break;
                case TRIGGER_MODE::ET:
                    readET(eventFd);
                    break;
                default:
                    break;
            }
        } else {
            printf("wait handle.");
        }
    }
}

void epollServer(int port, TRIGGER_MODE triggerMode) {
    struct sockaddr_in listenAddr;
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenAddr.sin_port = htons(port);

    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenFd >= 0);
    int ret =
        bind(listenFd, (struct sockaddr *)&listenAddr, sizeof(listenAddr));
    assert(ret >= 0);
    ret = listen(listenFd, 5);
    assert(ret >= 0);

    int epollFd = epoll_create(5);
    assert(epollFd >= 0);
    addFd(epollFd, listenFd, false);

    struct epoll_event events[MAX_EVENT_NUMBER];
    while (true) {
        printf("epoll wait ...\n");
        int ret = epoll_wait(epollFd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            break;
        }
        handle(events, ret, epollFd, listenFd, triggerMode);
    }
    close(epollFd);
}

int main(int argc, char *argv[]) {
    assert(argc >= 3);
    int port = atoi(argv[1]);
    TRIGGER_MODE triggerMode = TRIGGER_MODE::LT;
    if (0 == strcmp("et", argv[2]) || 0 == strcmp("ET", argv[2])) {
        triggerMode = TRIGGER_MODE::ET;
    }
    printf("port: %d, trigger mode: %s\n", port,
           TRIGGER_MODE::LT == triggerMode ? "LT" : "ET");
    epollServer(port, triggerMode);

    return 0;
}
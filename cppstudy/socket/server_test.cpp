#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <string>
#include <thread>

int main(int argc, char **argv) {
    assert(argc >= 3);
    char *ip = argv[1];
    int port = std::stoi(argv[2]);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(server_fd >= 0);
    int ret = bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr));
    assert(ret >= 0);
    ret = listen(server_fd, 20);
    assert(ret >= 0);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        printf("accept ...\n");
        int client_fd =
            accept(server_fd, (sockaddr *)&client_addr, &client_addr_len);
        assert(client_fd >= 0);
        printf("[connect] %s:%d\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        std::thread th([&]() {
            char buf[1024];
            while (true) {
                int len = read(client_fd, buf, sizeof(buf));
                printf("recv: %s\n", buf);
                len = write(client_fd, buf, strlen(buf));
                if (0 == strncmp("Bye", buf, 3)) {
                    break;
                }
            }
            close(client_fd);
            printf("[close] %s:%d\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
        });

        th.detach();
    }

    close(server_fd);

    return 0;
}
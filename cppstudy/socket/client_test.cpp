#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    assert(argc >= 3);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(std::stoi(argv[2]));

    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf("connect ...\n");
    int ret = connect(client_fd, (sockaddr *)&server_addr, sizeof(server_addr));
    assert(ret >= 0);

    printf("connect success!\n");
    char buf[1024];
    while (true) {
        printf("> ");
        // scanf("%s", buf);
        std::cin >> buf;
        // fgets(buf, sizeof(buf), stdin);
        ret = write(client_fd, buf, strlen(buf));

        ret = read(client_fd, buf, sizeof(buf));

        printf("server: %s\n", buf);
        if (0 == strncmp(buf, "Bye", 3)) {
            break;
        }
        break;
    }
    close(client_fd);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd_one;
    int err_log;
    sockfd_one = socket(AF_INET, SOCK_STREAM, 0);  //创建UDP套接字one
    if (sockfd_one < 0) {
        perror("sockfd_one");
        exit(-1);
    }

    // 设置本地网络信息
    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8000);  // 端口为8000
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 在sockfd_one绑定bind之前，设置其端口复用
    int opt = 1;
    // setsockopt(sockfd_one, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
    //            sizeof(opt));

    // 绑定，端口为8000
    err_log = bind(sockfd_one, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (err_log != 0) {
        perror("bind sockfd_one");
        close(sockfd_one);
        exit(-1);
    }

    int sockfd_two;
    sockfd_two = socket(AF_INET, SOCK_STREAM, 0);  //创建UDP套接字two
    if (sockfd_two < 0) {
        perror("sockfd_two");
        exit(-1);
    }

    // 在sockfd_two绑定bind之前，设置其端口复用
    opt = 1;
    // setsockopt(sockfd_two, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
    //            sizeof(opt));

    my_addr.sin_addr.s_addr = htonl(LOCALHO);
    // 新套接字sockfd_two，继续绑定8000端口，成功
    err_log = bind(sockfd_two, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (err_log != 0) {
        perror("bind sockfd_two");
        close(sockfd_two);
        exit(-1);
    }

    close(sockfd_one);
    close(sockfd_two);

    printf("wait ...");
    getchar();

    return 0;
}
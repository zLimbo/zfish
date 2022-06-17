
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cassert>
using namespace std;

int main(int argc, char **argv) {
    assert(argc >= 2);
    hostent *h = gethostbyname(argv[1]);

    if (!h) {
        puts("Get Ip address failed!");
        exit(0);
    }

    printf("name: %s\n", h->h_name);
    printf("alias:\n");
    for (int i = 0; h->h_aliases[i]; ++i) {
        printf("\t%d %s\n", i, h->h_aliases[i]);
    }
    printf("type: %s\n", h->h_addrtype == AF_INET ? "ipv4" : "ipv6");
    printf("ip addrs:\n");
    for (int i = 0; h->h_addr_list[i]; ++i) {
        in_addr in = *(in_addr *)h->h_addr_list[i];
        printf("\t%d %s\n", i, inet_ntoa(in));
    }

    return 0;
}
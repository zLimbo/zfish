
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void byteorder() {
    struct nest {
        union {
            short data;
            char bytes[sizeof(short)];
        };
    };
    nest x = {0x1234};
    if (x.bytes[0] == 1) {
        printf("big endian\n");
    } else {
        printf("little endian\n");
    }
}

int main() {
    byteorder();
    return 0;
}
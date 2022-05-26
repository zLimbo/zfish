
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    char buf[100];
    memset(buf, 0, sizeof(buf));

    if (getcwd(buf, 100) != nullptr) {
        printf("cwd: %s\n", buf);
    }

    return 0;
}
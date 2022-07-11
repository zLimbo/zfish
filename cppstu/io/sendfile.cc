#include <bits/stdc++.h>
#include <sys/file.h>
#include <sys/stat.h>
using namespace std;

int main() {

    struct stat st;
    int fd = open("./tmp", O_RDONLY);
    fstat(fd, &st);

    return 0;
}
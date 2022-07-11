#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>

int main(int argc, char **argv) {
    assert(argc == 2);

    struct stat buf;
    int fd;
    fd = open(argv[1], O_RDONLY);
    fstat(fd, &buf);
    printf("'%s' file size: %ld\n ", argv[1], buf.st_size);

    return 0;
}
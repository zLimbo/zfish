// posix
/*gcc -o shmopen shmopen.c -lrt*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAP_SIZE 68157440

int main(int argc, char* argv[]) {
    int fd;
    void* result;
    fd = shm_open("/shm1", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        printf("shm_open failed\n");
        exit(1);
    }
    return 0;
}
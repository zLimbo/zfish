// posix
/*gcc -o shmwrite shmwrite.c -lrt*/
#include <fcntl.h>
#include <memory.h>
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
    if (ftruncate(fd, MAP_SIZE) < 0) {
        printf("ftruncate failed\n");
        exit(1);
    }
    result = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (result == MAP_FAILED) {
        printf("mapped failed\n");
        exit(1);
    }
    /* ... operate result pointer */
    printf("memset\n");
    memset(result, 0, MAP_SIZE);
    shm_unlink("/shm1");
    getchar();
    return 0;
}
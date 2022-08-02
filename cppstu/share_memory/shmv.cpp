// System V
/*gcc -o shmv shmv.c*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#define MAP_SIZE 68157440

int main(int argc, char** argv) {
    int shm_id, i;
    key_t key;
    char temp;
    char* p_map;
    const char* name = "/dev/shm/shm3";
    key = ftok(name, 0);
    if (key == -1)
        perror("ftok error");
    shm_id = shmget(key, MAP_SIZE, IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget error");
        return 0;
    }
    p_map = (char*)shmat(shm_id, NULL, 0);
    memset(p_map, 0, MAP_SIZE);
    getchar();
    if (shmdt(p_map) == -1)
        perror(" detach error ");
}
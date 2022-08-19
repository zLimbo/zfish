#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf {
    long mtype;
    char mtext[255];
};

int main() {
    // 1. 获取消息队列
    int msg_id = msgget(10, IPC_CREAT | 0666);
    if (msg_id != -1) {
        struct msgbuf mybuf;
        // 2. 接收第一条消息，存到 mybuf 中
        // IPC_NOWAIT 表示不阻塞
        if (msgrcv(msg_id, &mybuf, sizeof(mybuf.mtext), 0, IPC_NOWAIT) != -1) {
            printf("read success: %s\n", mybuf.mtext);
        } else {
            perror("msgsnd:");
        }
    } else {
        perror("msgget:");
    }
    return 0;
}
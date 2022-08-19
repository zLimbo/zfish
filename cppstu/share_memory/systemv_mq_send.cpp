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
    // 1. 创建一个消息队列，用 key = 10 来唯一表示这个队列
    int msg_id = msgget(10, IPC_CREAT | 0666);
    if (msg_id != -1) {
        // 2. 初始化要发生的消息
        struct msgbuf mybuf;
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "hello, message queue test...\n");

        // 3. 发送消息
        int ret = msgsnd(msg_id, &mybuf, sizeof(mybuf.mtext), 0);
        if (ret < 0)
            printf("error: %d \n", ret);
        else
            printf("success: %d \n", ret);
    } else {
        perror("msgget:");
    }
    return 0;
}
#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> /* For mode constants */
#include <unistd.h>

int main(int argc, char *argv[]) {
    mqd_t mq_cmd;
    struct mq_attr attr;
    char msgbuffer[5];
    memcpy(msgbuffer, "boots", 5);

    /* Open the message queue for reading */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 20;
    attr.mq_curmsgs = 0;

    mq_cmd = mq_open("/mq_test", O_WRONLY | O_CREAT, 0666, &attr);  //为什么要加 / ，否则打开失败
    if (mq_cmd < 0) {
        printf("mq_open error: %d \n", mq_cmd);
    } else {
        printf("mq_open success: %d \n", mq_cmd);
    }

    int nbytes = mq_send(mq_cmd, (char *)msgbuffer, sizeof(msgbuffer), 0);
    if (nbytes < 0) {
        printf("mq_send error: %d \n", nbytes);
    } else {
        printf("mq_send success: %d \n", nbytes);
    }

    if (mq_close(mq_cmd) < 0) {
        printf("mq_close error! \n");
    } else {
        printf("mq_close success! \n");
    }

    // mq_unlink("/mq_test");
}
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    char temp[1024] = {0};
    dup2(fd, STDOUT_FILENO);
    //文件重定向后，往终端输出的数据，会写入的文件中
    //先写4096B试试，看看能写入磁盘不
    for (int i = 0; i < 4096; i++) {
        printf("%c", 48);
    }
    // kernel缓存区大小为4096！写到4097字节，缓冲区溢出才会将缓冲区内容写道磁盘文件，
    //缓存区继续放数据
    write(STDERR_FILENO, "write 4096", 11);
    getchar();
    while (1) {
        //读取终端数据
        read(STDIN_FILENO, temp, sizeof(temp));
        if (strncmp(temp, "exit", 4) == 0)
            break;
        printf("%s\n", temp);
    }
    close(fd);
    return 0;
}
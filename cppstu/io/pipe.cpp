#include <bits/stdc++.h>

using namespace std;

int main() {
    int fd[2];
    int ret = pipe(fd);  // unistd.h
    assert(ret == 0);

    auto f1 = async(launch::async, [&] {
        for (int i = 0; i < 3; ++i) {
            char buf[10];
            sprintf(buf, "entry %d", i);
            this_thread::sleep_for(chrono::seconds{1});
            write(fd[1], buf, strlen(buf));
        }
        close(fd[1]);
    });

    auto f2 = async(launch::async, [&] {
        while (true) {
            printf("wait...\n");
            char buf[10];
            int n = read(fd[0], buf, sizeof(buf));
            assert(n >= 0);
            if (n == 0) {
                close(fd[0]);
                printf("done.\n");
                break;
            }
            printf("read: %s\n", buf);
        }
    });

    return 0;
}
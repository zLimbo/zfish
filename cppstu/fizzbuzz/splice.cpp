#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    size_t buf_size = 1 << 18;  // 256KiB
    char* buf = (char*)malloc(buf_size);
    memset((void*)buf, 'X', buf_size);  // output Xs
    char* bufs[2] = {buf, buf + buf_size / 2};
    int buf_ix = 0;
    // Flip between the two buffers, splicing until we're done.
    while (true) {
        struct iovec bufvec = {.iov_base = bufs[buf_ix], .iov_len = buf_size / 2};
        buf_ix = (buf_ix + 1) % 2;
        while (bufvec.iov_len > 0) {
            ssize_t ret = vmsplice(STDOUT_FILENO, &bufvec, 1, 0);
            bufvec.iov_base = (void*)(((char*)bufvec.iov_base) + ret);
            bufvec.iov_len -= ret;
        }
    }
} 
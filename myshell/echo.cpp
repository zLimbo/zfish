#include <unistd.h>
#include <cstring>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        write(1, argv[i], strlen(argv[i]));
        if (i + 1 < argc) {
            write(1, " ", 1);
        } else {
            write(1, "\n", 1);
        }
    }

    return 0;
}
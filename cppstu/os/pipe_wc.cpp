#include <unistd.h>
#include <string_view>

int main() {
    int p[2];
    pipe(p);

    if (fork() == 0) {

        _exit(0);
    }
    
    

    return 0;
}
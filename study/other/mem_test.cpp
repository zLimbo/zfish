#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t large = 1099511627776;
    char *buffer = (char *)malloc(large);
    if (buffer == NULL) {
        printf("error!\n");
        return EXIT_FAILURE;
    }
    printf("Memory allocated\n");
    for (size_t i = 0; i < large; i += 4096) {
        buffer[i] = 0;
        printf("i: %lu\n", i);
    }
    free(buffer);
    return EXIT_SUCCESS;
}
#include <elf.h>

#include <cstdio>

int main(int argc, char *argv[]) {
    long long *p = (long long *)argv;
    int i;
    Elf32_auxv_t *aux;
    printf("Argument count: %lld\n", *(p - 1));

    for (i = 0; i < *(p - 1); ++i) {
        printf("Argument %d : %s\n", i, *(p + i));
    }

    p += i;
    p++;

    printf("\n[Environment]\n");
    while (*p) {
        printf("%s\n", *p);
        p++;
    }

    p++;

    printf("\n[Auxiliary Vectors]\n");
    aux = (Elf32_auxv_t *)p;
    while (aux->a_type != AT_NULL) {
        printf("Type: %02lld Value: %x\n", aux->a_type, aux->a_un.a_val);
        aux++;
    }

    return 0;
}
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstddef>

pthread_key_t key;

void destroy_func1(void *data) {
    if (data == NULL) {
        return;
    } else {
        printf("key data plus 10 is:%d\n", *(int *)data + 10);
        free(data);
        data = NULL;
    }
}

void destroy_func(void *data) {
    if (data == NULL) {
        return;
    } else {
        printf("key data is :%d\n", *(int *)data);
        free(data);
        data = NULL;
    }
}

void *thread_func(void *) {
    int *data = NULL;
    pthread_key_create(&key, destroy_func);
    data = (int *)pthread_getspecific(key);
    if (data == NULL) {
        data = (int *)malloc(sizeof(int));
        *data = 1;
        pthread_setspecific(key, data);
    }

    pthread_key_create(&key, destroy_func1);
    data = (int *)pthread_getspecific(key);
    if (data == NULL) {
        data = (int *)malloc(sizeof(int));
        *data = 2;
        pthread_setspecific(key, data);
    }

    printf("hello world\n");
    return nullptr;
}

int main(int argc, char **argv) {
    pthread_t pid;
    pthread_create(&pid, NULL, thread_func, NULL);
    pthread_join(pid, NULL);
    pthread_key_delete(key);

    printf("keys:\n");
    constexpr int n = 1024;
    pthread_key_t ks[n];
    for (int i = 0; i < n; ++i) {
        ks[i] = -1;
        pthread_key_create(&ks[i], nullptr);
        printf("%d: %d\n", i, ks[i]);
    }
    
}

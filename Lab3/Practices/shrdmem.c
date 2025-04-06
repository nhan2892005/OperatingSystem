// shrdmem.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXCOUNT 1e9

int count = 0;
pthread_mutex_t lock;

void* f_count(void* sid) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAXCOUNT; i++) {
        count = count + 1;
    }
    pthread_mutex_unlock(&lock);
    printf("Thread %s : holding %d\n", (char*) sid, count);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);

    // Create independent threads
    pthread_create(&thread1, NULL, f_count, "1");
    pthread_create(&thread2, NULL, f_count, "2");

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}

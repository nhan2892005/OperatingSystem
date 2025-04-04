// pc.c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFSIZE 2
#define THREADS 1
#define LOOPS (3 * BUFSIZE)

int buffer[BUFSIZE];
int fill = 0;
int use = 0;

sem_t empty; // buffer trống
sem_t full;  // buffer đầy
pthread_mutex_t lock;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % BUFSIZE;
}

int get() {
    int tmp = buffer[use];
    buffer[use] = -1; // clean
    use = (use + 1) % BUFSIZE;
    return tmp;
}

void* producer(void* arg) {
    int tid = *(int*) arg;
    for (int i = 0; i < LOOPS; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&lock);

        put(i);
        printf("Producer %d put data %d\n", tid, i);

        pthread_mutex_unlock(&lock);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int tid = *(int*) arg;
    int tmp = 0;
    for (int i = 0; i < LOOPS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        tmp = get();
        printf("Consumer %d get data %d\n", tid, tmp);

        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t producers[THREADS], consumers[THREADS];
    int tid[THREADS];

    sem_init(&empty, 0, BUFSIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < THREADS; i++) {
        tid[i] = i;
        pthread_create(&producers[i], NULL, producer, &tid[i]);
        pthread_create(&consumers[i], NULL, consumer, &tid[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);
    return 0;
}

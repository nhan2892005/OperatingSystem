#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    long long start, end, partial_sum;
} ThreadData;

void *partial_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->partial_sum = 0;
    for (long long i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    int num_threads = atoi(argv[1]);
    long long n = atoll(argv[2]);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    long long chunk_size = n / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * chunk_size + 1;
        thread_data[i].end = (i == num_threads - 1) ? n : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, partial_sum, &thread_data[i]);
    }

    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    } 
    printf("%lld", total_sum);
    return 0;
}
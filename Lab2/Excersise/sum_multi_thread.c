#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    long long start;
    long long end;
    long long partial_sum;
} ThreadData;

void *partial_sum(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    data->partial_sum = 0;
    for (long long i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s numThreads n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int numThreads = atoi(argv[1]);
    long long n = atoll(argv[2]);
    
    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    ThreadData *threadData = malloc(numThreads * sizeof(ThreadData));
    
    // Tính khoảng chia cho mỗi thread
    long long chunk = n / numThreads;
    long long remainder = n % numThreads;
    
    long long current_start = 1;
    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = current_start;
        // Phân chia các số dư (remainder) cho các thread đầu tiên
        threadData[i].end = current_start + chunk - 1;
        if (i < remainder) {
            threadData[i].end++;
        }
        current_start = threadData[i].end + 1;
        
        if(pthread_create(&threads[i], NULL, partial_sum, &threadData[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    long long total_sum = 0;
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += threadData[i].partial_sum;
    }
    
    printf("Multi-thread sum(1..%lld) with %d threads = %lld\n", n, numThreads, total_sum);
    
    free(threads);
    free(threadData);
    return 0;
}

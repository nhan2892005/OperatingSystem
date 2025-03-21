#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COUNT 10000  // Số lần tăng biến count

int count = 0;  // Biến dùng chung
pthread_mutex_t mutex;  // Mutex để tránh race condition

// Hàm chạy trên từng luồng
void *f_count(void *sid) {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        pthread_mutex_lock(&mutex);  // Khóa biến count
        count++;
        pthread_mutex_unlock(&mutex);  // Mở khóa
    }
    printf("Thread %s: holding %d\n", (char *)sid, count);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("Hello world\n");

    pthread_mutex_init(&mutex, NULL);  // Khởi tạo mutex

    // Tạo 2 luồng
    pthread_create(&thread1, NULL, f_count, "1");
    pthread_create(&thread2, NULL, f_count, "2");

    // Chờ cả hai luồng kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);  // Giải phóng mutex

    printf("Final count = %d\n", count);
    return 0;
}

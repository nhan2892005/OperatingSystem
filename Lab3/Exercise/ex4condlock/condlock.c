#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Bộ đệm chia sẻ và biến đếm
int buffer[BUFFER_SIZE];
int count = 0;

// Mutex và biến điều kiện
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

// Hàm writer (producer)
void* writer(void* arg) {
    int item = 0; // Ví dụ: sản phẩm là số nguyên tăng dần
    while (1) {
        // Khóa mutex trước khi truy cập bộ đệm
        pthread_mutex_lock(&mutex);

        // Nếu bộ đệm đầy, chờ cho tới khi có không gian
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&condvar, &mutex);
        }

        // Thêm sản phẩm vào bộ đệm
        buffer[count++] = item;
        printf("Producer produced: %d | Buffer count: %d\n", item, count);
        item++; // Tạo sản phẩm mới

        // Thông báo cho consumer rằng có sản phẩm mới
        pthread_cond_signal(&condvar);

        // Giải phóng mutex
        pthread_mutex_unlock(&mutex);

        // Giả lập thời gian sản xuất
        sleep(1);
    }
    return NULL;
}

// Hàm reader (consumer)
void* reader(void* arg) {
    int item;
    while (1) {
        // Khóa mutex trước khi truy cập bộ đệm
        pthread_mutex_lock(&mutex);

        // Nếu bộ đệm rỗng, chờ cho tới khi có sản phẩm
        while (count == 0) {
            pthread_cond_wait(&condvar, &mutex);
        }

        // Lấy sản phẩm từ bộ đệm
        item = buffer[--count];
        printf("Consumer consumed: %d | Buffer count: %d\n", item, count);

        // Thông báo cho producer rằng có không gian trống
        pthread_cond_signal(&condvar);

        // Giải phóng mutex
        pthread_mutex_unlock(&mutex);

        // Giả lập thời gian tiêu thụ
        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t writerThread, readerThread;

    // Tạo thread producer và consumer
    if (pthread_create(&writerThread, NULL, writer, NULL) != 0) {
        perror("Failed to create writer thread");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&readerThread, NULL, reader, NULL) != 0) {
        perror("Failed to create reader thread");
        exit(EXIT_FAILURE);
    }

    // Chờ cho các thread hoàn thành (trong ví dụ này, chúng chạy vô hạn)
    pthread_join(writerThread, NULL);
    pthread_join(readerThread, NULL);

    return 0;
}

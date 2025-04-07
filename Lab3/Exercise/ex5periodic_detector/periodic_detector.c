#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Khai báo mutex và biến toàn cục
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int finished = 0;

int sum_digits_until_less_than_10(int n) {
    if (n < 10) {
        return n;
    }
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum_digits_until_less_than_10(sum);
}

// Hàm kiểm tra an toàn của hệ thống
int is_safe() {
    // TODO: Thực hiện các kiểm tra polling thật sự ở đây
    // Giả lập kiểm tra: sử dụng hàm rand() để mô phỏng xác suất phát hiện bất thường
    int r = sum_digits_until_less_than_10(rand()); // Giả lập: số ngẫu nhiên từ 0 đến 99
    if (r < 2) {  // Giả sử 20% khả năng không an toàn
        printf("Kiểm tra an toàn: Hệ thống không an toàn!\n");
        return 0; // Không an toàn
    }
    printf("Kiểm tra an toàn: Hệ thống an toàn.\n");
    return 1; // An toàn
}

// Hàm thực hiện hành động khắc phục khi phát hiện bất thường
void take_corrective_action() {
    printf("Thực hiện hành động khắc phục...\n");
    // TODO: Thực hiện các hành động khắc phục phù hợp
    // Giả lập: đặt finished = 1 sau khi khắc phục xong
    finished = 1;
}

// Hàm phát hiện định kỳ
void* periodic_detector(void* arg) {
    while (1) {
        sleep(5);  // Kiểm tra định kỳ sau mỗi 5 giây

        pthread_mutex_lock(&lock);
        if (!is_safe()) {
            // Phát hiện bất thường, thực hiện hành động khắc phục
            take_corrective_action();

            // Nếu hệ thống đã khắc phục xong (finished) thì thoát vòng lặp
            if (finished) {
                pthread_mutex_unlock(&lock);
                break;
            }
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    // Khởi tạo seed cho hàm rand()
    srand(time(NULL));

    pthread_t detector_thread;

    // Tạo thread để chạy periodic_detector
    if (pthread_create(&detector_thread, NULL, periodic_detector, NULL) != 0) {
        perror("Lỗi khi tạo thread periodic_detector");
        exit(EXIT_FAILURE);
    }

    // Chờ thread periodic_detector kết thúc
    pthread_join(detector_thread, NULL);

    printf("Thread periodic_detector đã kết thúc.\n");
    return 0;
}

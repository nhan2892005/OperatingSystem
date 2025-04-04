#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define SHM_KEY 0x1234

typedef struct {
    double avg1;
    double avg2;
} ShmData;

int main() {
    FILE *file = fopen("movie-100k_1.txt", "r");
    if (!file) {
        perror("Không thể mở file movie-100k_1.txt");
        exit(1);
    }

    int sum = 0, count = 0, rating;
    // Đọc file theo định dạng: userID movieID rating timestamp
    while (fscanf(file, "%*d %*d %d %*d", &rating) == 1) {
        sum += rating;
        count++;
    }
    fclose(file);

    // Ghi kết quả vào shared memory
    int shmid = shmget(SHM_KEY, sizeof(ShmData), 0644);
    ShmData *shm = (ShmData*)shmat(shmid, NULL, 0);
    shm->avg1 = (count > 0) ? (double)sum / count : 0.0;

    shmdt(shm);
    return 0;
}
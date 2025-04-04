#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_KEY 0x1234

typedef struct {
    double avg1;  // Điem trung bình từ movie-100k_1.txt
    double avg2;  // Điem trung bình từ movie-100k_2.txt
} ShmData;

int main() {
    // Tạo shared memory
    int shmid = shmget(SHM_KEY, sizeof(ShmData), 0644 | IPC_CREAT);
    ShmData *shm = (ShmData*)shmat(shmid, NULL, 0);

    // Tạo tiến trình con 1 (xử lý movie-100k_1.txt)
    pid_t pid1 = fork();
    if (pid1 == 0) {
        execl("./process1", "process1", NULL);
        perror("execl process1 failed");
        exit(1);
    }

    // Tạo tiến trình con 2 (xu lý movie-100k_2.txt)
    pid_t pid2 = fork();
    if (pid2 == 0) {
        execl("./process2", "process2", NULL);
        perror("execl process2 failed");
        exit(1);
    }

    // Đợi cả 2 tiến trình con hoàn thành
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Tính điểm trung bình tong cua moi file
    printf("Average from movie-100k_1.txt: %.2f\n", shm->avg1);
    printf("Average from movie-100k_2.txt: %.2f\n", shm->avg2);

    // Giải phóng shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
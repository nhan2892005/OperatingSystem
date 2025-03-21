#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Hàm tính trung bình rating của file
double compute_average(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }
    
    long count = 0;
    double sum = 0.0;
    int userID, movieID, rating;
    long timestamp;
    
    // Định dạng file: userID <tab> movieID <tab> rating <tab> timeStamp
    while (fscanf(fp, "%d\t%d\t%d\t%ld", &userID, &movieID, &rating, &timestamp) == 4) {
        sum += rating;
        count++;
    }
    
    fclose(fp);
    return (count > 0) ? sum / count : 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }
    
    // Tạo shared memory để lưu 2 giá trị double (một cho mỗi file)
    int shmid = shmget(IPC_PRIVATE, 2 * sizeof(double), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    
    double *shared = (double *) shmat(shmid, NULL, 0);
    if (shared == (void *) -1) {
        perror("shmat");
        exit(1);
    }
    
    // Khởi tạo giá trị ban đầu
    shared[0] = 0.0;
    shared[1] = 0.0;
    
    pid_t pid1, pid2;
    
    // Tạo tiến trình con đầu tiên để xử lý file argv[1]
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }
    if (pid1 == 0) {
        double avg = compute_average(argv[1]);
        // Ghi kết quả vào vị trí đầu của shared memory
        shared[0] = avg;
        shmdt(shared);
        exit(0);
    }
    
    // Tạo tiến trình con thứ hai để xử lý file argv[2]
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }
    if (pid2 == 0) {
        double avg = compute_average(argv[2]);
        // Ghi kết quả vào vị trí thứ 2 của shared memory
        shared[1] = avg;
        shmdt(shared);
        exit(0);
    }
    
    // Tiến trình cha chờ cả hai tiến trình con kết thúc
    wait(NULL);
    wait(NULL);
    
    // In kết quả trung bình của từng file
    printf("Average rating from file %s = %.2f\n", argv[1], shared[0]);
    printf("Average rating from file %s = %.2f\n", argv[2], shared[1]);
    
    // Tách và xóa shared memory
    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}

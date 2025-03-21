#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define SHMKEY 0x123
int main(int argc, char * argv[]) {
    int shmid;
    char * shm;
    shmid= shmget(SHMKEY, 1000, 0644 | IPC_CREAT);
    if (shmid<0) {
        perror("shmget");
        return 1;
    } else {
        printf("shared memory ID: %d\n", shmid);
    }
    shm= (char * ) shmat(shmid, 0, 0);
    if (shm== (char * )- 1) {
        perror("shmat");
        exit(1);
    }
    printf("shared memorymm: %p\n", shm);
    if (shm != 0) {
        printf("shared memory content: %s\n", shm);
    }
    sleep(10);
    if (shmdt(shm) ==-1) {
        perror("shmdt");
        return 1;
    }
    return 0;
}
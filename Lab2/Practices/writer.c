#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define SHMKEY 0x123

int main(int argc, char * argv[]) {
    int shmid;
    char *shm;
    shmid= shmget(SHMKEY, 1000, 0644 | IPC_CREAT);
    if (shmid<0) {
        perror("Shared-memory");
        return 1;
    } else {
        printf("Shared-memory ID: %d\n", shmid);
    }
    shm= (char *) shmat(shmid, 0, 0);
    if (shm== (char *)-1) {
        perror("shmat");
        exit(1);
    }
    printf("shared memorymm: %p\n", shm);
    sprintf(shm, "hello world\n");
    printf("shared memory content: %s\n", shm);
    sleep(10);
    // detach from the shared memory
    if (shmdt(shm) ==-1) {
        perror("shmdt");
        return 1;
    }
    // Mark the shared segment to be destroyed .
    if (shmctl(shmid, IPC_RMID, 0) ==-1) {
        perror("shmctl");
        return 1;
    }
    return 0;
}
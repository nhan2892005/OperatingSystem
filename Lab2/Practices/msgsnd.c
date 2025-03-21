#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define PERMS 0644  // Quyền truy cập hàng đợi tin nhắn

struct mymsgbuf {
    long mtype;
    char mtext[200];
};

int main(void) {
    struct mymsgbuf buf;
    int msqid;
    key_t key;

    // Tạo file nếu chưa có
    system("touch msgqueuefile");

    // Dùng ftok để tạo key
    key = ftok("msgqueuefile", 'A');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Tạo hoặc lấy hàng đợi tin nhắn
    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message queue ready. Enter messages (Ctrl+D to exit):\n");

    buf.mtype = 1;
    while (fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
        int len = strlen(buf.mtext);
        if (buf.mtext[len - 1] == '\n') buf.mtext[len - 1] = '\0';

        if (msgsnd(msqid, &buf, len + 1, 0) == -1) {
            perror("msgsnd failed");
        }
    }

    strcpy(buf.mtext, "end");
    if (msgsnd(msqid, &buf, strlen(buf.mtext) + 1, 0) == -1) {
        perror("msgsnd failed");
    }

    printf("Message queue: Done sending messages.\n");
    return 0;
}

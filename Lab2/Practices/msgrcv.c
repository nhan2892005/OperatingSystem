#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644  // Quyền truy cập hàng đợi tin nhắn

// Định nghĩa cấu trúc tin nhắn
struct mymsgbuf {
    long mtype;
    char mtext[200];
};

int main(void) {
    struct mymsgbuf buf;
    int msqid;
    key_t key;

    // Tạo key từ file, đảm bảo giá trị hợp lệ
    key = ftok("msgqueuefile", 'A');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Lấy ID hàng đợi tin nhắn
    if ((msqid = msgget(key, PERMS)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message queue ready to receive messages.\n");

    while (1) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        printf("Received: \"%s\"\n", buf.mtext);

        if (strcmp(buf.mtext, "end") == 0) {
            break;  // Dừng nếu nhận được "end"
        }
    }

    // Xóa hàng đợi tin nhắn sau khi sử dụng
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    printf("Message queue: Done receiving messages.\n");
    return 0;
}

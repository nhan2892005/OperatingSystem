#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE 100
#define CLIENT_TO_SERVER 1234
#define SERVER_TO_CLIENT 5678

typedef struct {
    char text[MSG_SIZE];
} Message;

int msgid_recv, msgid_send;
volatile sig_atomic_t received_first_msg = 0; // Đánh dấu đã nhận tin nhắn đầu tiên

void *receive_message(void *arg) {
    Message msg;
    // printf("[Server] Waiting for messages...\n");
    while (1) {
        if (msgrcv(msgid_recv, &msg, sizeof(msg.text), 0, 0) > 0) {
            printf("\n[Server] Received: %s", msg.text);
            fflush(stdout);

            received_first_msg = 1; 

            // printf("[Server] Enter response: ");
            fflush(stdout);
        }
    }
    return NULL;
}

void *send_message(void *arg) {
    Message msg;
    
    while (!received_first_msg) {
        usleep(10000);
    }

    while (1) {
        printf("[Server] Enter response: ");
        fflush(stdout);
        
        fgets(msg.text, MSG_SIZE, stdin);
        msgsnd(msgid_send, &msg, sizeof(msg.text), 0);
    }
    return NULL;
}

int main() {
    pthread_t thread_recv, thread_send;

    msgid_recv = msgget(CLIENT_TO_SERVER, 0666 | IPC_CREAT);
    msgid_send = msgget(SERVER_TO_CLIENT, 0666 | IPC_CREAT);

    pthread_create(&thread_recv, NULL, receive_message, NULL);
    pthread_create(&thread_send, NULL, send_message, NULL);

    pthread_join(thread_recv, NULL);
    pthread_join(thread_send, NULL);

    return 0;
}

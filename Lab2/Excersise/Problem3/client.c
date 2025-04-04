#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#define MSG_SIZE 100
#define CLIENT_TO_SERVER 1234
#define SERVER_TO_CLIENT 5678

typedef struct {
    char text[MSG_SIZE];
} Message;

int msgid_send, msgid_recv;

void *send_message(void *arg) {
    Message msg;
    while (1) {
        printf("[Client] Enter message: ");
        fflush(stdout);
        
        fgets(msg.text, MSG_SIZE, stdin);
        msgsnd(msgid_send, &msg, sizeof(msg.text), 0);
    }
    return NULL;
}

void *receive_message(void *arg) {
    Message msg;
    while (1) {
        if (msgrcv(msgid_recv, &msg, sizeof(msg.text), 0, 0) > 0) {
            printf("\n[Client] Received: %s", msg.text);
            fflush(stdout);
        }
    }
    return NULL;
}

int main() {
    pthread_t thread_send, thread_recv;

    msgid_send = msgget(CLIENT_TO_SERVER, 0666 | IPC_CREAT);
    msgid_recv = msgget(SERVER_TO_CLIENT, 0666 | IPC_CREAT);

    pthread_create(&thread_send, NULL, send_message, NULL);
    pthread_create(&thread_recv, NULL, receive_message, NULL);

    pthread_join(thread_send, NULL);
    pthread_join(thread_recv, NULL);

    return 0;
}

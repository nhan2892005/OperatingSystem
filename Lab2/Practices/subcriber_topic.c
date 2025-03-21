#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    void *context = zmq_ctx_new();
    // Tạo socket SUB và kết nối đến broker (cổng 5556)
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "tcp://localhost:5556");
    if (rc != 0) {
        perror("zmq_connect");
        return 1;
    }
    // Đăng ký nhận thông điệp có topic "news" (đăng ký theo prefix)
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "news", strlen("news"));
    if (rc != 0) {
        perror("zmq_setsockopt");
        return 1;
    }

    while (1) {
        char message[256];
        int size = zmq_recv(subscriber, message, 255, 0);
        if (size != -1) {
            message[size] = '\0';
            printf("Subscriber received: %s\n", message);
        }
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    void *context = zmq_ctx_new();
    // Tạo socket PUB và kết nối đến broker (cổng 5555)
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_connect(publisher, "tcp://localhost:5555");
    if (rc != 0) {
        perror("zmq_connect");
        return 1;
    }

    // Để các subscriber có thời gian kết nối, tạm dừng 1 giây
    sleep(1);

    int count = 0;
    while (1) {
        char message[256];
        // Lấy topic theo cách đơn giản, xoay vòng giữa "sports" và "news"
        const char *topic = (count % 2 == 0) ? "sports" : "news";
        sprintf(message, "%s: Message number %d", topic, count);
        zmq_send(publisher, message, strlen(message), 0);
        printf("Publisher sent: %s\n", message);
        count++;
        sleep(1);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}

#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void) {
    void *context = zmq_ctx_new();

    // Socket nhận từ publisher (SUB)
    void *frontend = zmq_socket(context, ZMQ_SUB);
    // Bind cổng cho publisher gửi tin (ví dụ 5555)
    int rc = zmq_bind(frontend, "tcp://*:5555");
    assert(rc == 0);
    // Đăng ký nhận tất cả thông điệp
    rc = zmq_setsockopt(frontend, ZMQ_SUBSCRIBE, "", 0);
    assert(rc == 0);

    // Socket gửi đến subscriber (PUB)
    void *backend = zmq_socket(context, ZMQ_PUB);
    // Bind cổng cho subscriber nhận tin (ví dụ 5556)
    rc = zmq_bind(backend, "tcp://*:5556");
    assert(rc == 0);

    // Nếu muốn kết nối với broker khác trong cluster, có thể tạo thêm socket kết nối outbound
    // Ví dụ: void *cluster = zmq_socket(context, ZMQ_PUB);
    // zmq_connect(cluster, "tcp://<ip-broker-khac>:5557");

    char buffer[256];
    while (1) {
        int size = zmq_recv(frontend, buffer, 255, 0);
        if (size != -1) {
            buffer[size] = '\0';
            // Ghi log nhận được tin
            printf("Broker received: %s\n", buffer);
            // Chuyển tiếp thông điệp (bao gồm topic) đến subscriber
            zmq_send(backend, buffer, size, 0);

            // Nếu có kết nối cluster, chuyển tiếp tin nhắn cho các broker khác
            // zmq_send(cluster, buffer, size, 0);
        }
    }

    zmq_close(frontend);
    zmq_close(backend);
    // zmq_close(cluster);
    zmq_ctx_destroy(context);
    return 0;
}

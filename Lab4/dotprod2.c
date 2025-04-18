/*
 * File: dotprod2.c
 * Mô tả: Tính tích vô hướng (dot product) của hai vector sử dụng đa luồng,
 *       đồng bộ cập nhật kết quả bằng mutex.
 * Kết quả khi chạy:
 *   - Mỗi luồng in ra thông tin partial sum = 100.000000 và giá trị sum hiện tại.
 *   - Cuối cùng in: Done. Threaded version: sum = 800.000000
 */

 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>
 
 /* Giải thích 1:
  * STRUCT DOTDATA chứa dữ liệu chung cho các thread:
  *   - a, b: con trỏ đến hai mảng double cần nhân tích vô hướng.
  *   - sum: kết quả tổng chung được các thread cộng vào.
  *   - veclen: độ dài phần của mảng mà mỗi thread xử lý.
  */
 typedef struct {
     double *a;
     double *b;
     double sum;
     int veclen;
 } DOTDATA;
 
 /* Giải thích 2:
  *   - MAXTHRDS: số luồng tối đa (8).
  *   - VECLEN: số phần tử mỗi luồng sẽ tính (100).
  *   - dotstr: biến toàn cục kiểu DOTDATA chứa dữ liệu dùng chung.
  *   - callThd: mảng pthread_t để lưu ID các thread.
  *   - mutexsum: mutex bảo vệ cập nhật dotstr.sum.
  */
 #define MAXTHRDS 8
 #define VECLEN    100
 
 DOTDATA dotstr;
 pthread_t callThd[MAXTHRDS];
 pthread_mutex_t mutexsum;
 
 /* Giải thích 3:
  * Hàm dotprod khởi đầu mỗi thread:
  *   - arg: offset (chỉ số thứ tự) truyền qua cast từ (void*).
  *   - Lấy offset, tính start và end dựa trên veclen.
  */
 void *dotprod(void *arg) {
     long offset = (long)arg;
     int start = offset * dotstr.veclen;
     int end   = start + dotstr.veclen;
     double *x = dotstr.a;
     double *y = dotstr.b;
 
     /* Giải thích 4:
      * Tính tích vô hướng cục bộ mysum của đoạn x[start..end-1] và y[...] .
      * Dùng mysum để tính tổng trong nội bộ thread, tránh thời gian chờ mutex.
      */
     double mysum = 0;
     for (int i = start; i < end; i++) {
         mysum += x[i] * y[i];
     }
 
     /* Giải thích 5:
      * Cập nhật mysum vào dotstr.sum dùng mutex để tránh race condition.
      * In thông tin partial sum và giá trị sum trước khi cập nhật.
      */
     pthread_mutex_lock(&mutexsum);
     printf("Thread %ld adding partial sum of %f to global sum of %f\n",
            offset, mysum, dotstr.sum);
     dotstr.sum += mysum;
     pthread_mutex_unlock(&mutexsum);
 
     pthread_exit(NULL);
 }
 
 /* Giải thích 6:
  * Hàm main khởi tạo dữ liệu, tạo và join các thread:
  *   - Cấp phát và khởi tạo mảng a, b toàn giá trị 1.
  *   - Thiết lập dotstr veclen, con trỏ a/b, sum = 0.
  *   - Khởi tạo mutex, thuộc tính thread joinable.
  *   - Tạo MAXTHRDS thread, truyền offset (0..7).
  *   - Join tất cả thread, in kết quả cuối cùng, giải phóng tài nguyên.
  */
 int main(int argc, char *argv[]) {
     // Cấp phát và khởi tạo 2 mảng độ dài MAXTHRDS*VECLEN
     double *a = malloc(MAXTHRDS * VECLEN * sizeof(double));
     double *b = malloc(MAXTHRDS * VECLEN * sizeof(double));
     if (!a || !b) {
         fprintf(stderr, "Không cấp phát được bộ nhớ.\n");
         return 1;
     }
     for (long i = 0; i < MAXTHRDS * VECLEN; i++) {
         a[i] = 1.0;
         b[i] = 1.0;
     }
 
     dotstr.veclen = VECLEN;
     dotstr.a      = a;
     dotstr.b      = b;
     dotstr.sum    = 0.0;
 
     pthread_mutex_init(&mutexsum, NULL);
     pthread_attr_t attr;
     pthread_attr_init(&attr);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
     for (long i = 0; i < MAXTHRDS; i++) {
         pthread_create(&callThd[i], &attr, dotprod, (void *)i);
     }
     pthread_attr_destroy(&attr);
 
     for (int i = 0; i < MAXTHRDS; i++) {
         pthread_join(callThd[i], NULL);
     }

     printf("Done. Threaded version: sum =  %f \n", dotstr.sum);

     free(a);
     free(b);
     pthread_mutex_destroy(&mutexsum);
     return 0;
 }
 
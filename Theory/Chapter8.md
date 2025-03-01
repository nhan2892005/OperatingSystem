# Chương 8: Deadlocks (Tình Trạng Bế Tắc)

Deadlock (bế tắc) là tình trạng mà trong đó một nhóm tiến trình bị kẹt khi mỗi tiến trình đang giữ một tài nguyên và đồng thời chờ đợi các tài nguyên do tiến trình khác giữ, dẫn đến không tiến trình nào có thể tiến hành công việc. Chương 8 tập trung vào việc nhận dạng, phân loại và giải quyết vấn đề deadlock trong các hệ thống đa nhiệm.

---

## 8.1 Mô Hình Hệ Thống và Deadlock

- **Mô hình hệ thống:**  
  - Mô hình đại diện cho các tài nguyên và tiến trình trong hệ thống.
  - Các tiến trình yêu cầu và giữ các tài nguyên khác nhau.
  
- **Deadlock xảy ra khi:**  
  - Có một tập hợp tiến trình \(P = \{P_1, P_2, \dots, P_n\}\) và các tài nguyên \(R = \{R_1, R_2, \dots, R_m\}\) mà:
    1. **Mutual Exclusion (Loại trừ lẫn nhau):** Một tài nguyên chỉ có thể được sử dụng bởi một tiến trình tại một thời điểm.
    2. **Hold and Wait (Giữ tài nguyên và chờ đợi):** Một tiến trình đang giữ ít nhất một tài nguyên và đồng thời yêu cầu tài nguyên khác đang bị các tiến trình khác giữ.
    3. **No Preemption (Không thể tước đoạt):** Tài nguyên không thể bị tước đoạt từ một tiến trình một cách cưỡng chế; tiến trình phải tự giải phóng.
    4. **Circular Wait (Chờ đợi vòng tròn):** Có một chuỗi các tiến trình \(P_1, P_2, \dots, P_n\) sao cho \(P_1\) chờ \(P_2\), \(P_2\) chờ \(P_3\), …, \(P_n\) chờ \(P_1\).

---

## 8.2 Phân Tích và Đặc Trưng Deadlock

- **Đặc trưng của deadlock:**  
  - Xác định các điều kiện cần để deadlock xảy ra.
  - Mô hình hóa bằng đồ thị yêu cầu tài nguyên (Resource Allocation Graph) giúp nhận diện deadlock.
  
- **Ví dụ minh họa:**  
  - Hai tiến trình \(P_1\) và \(P_2\) với tài nguyên \(R_1\) và \(R_2\). Nếu \(P_1\) giữ \(R_1\) và chờ \(R_2\), đồng thời \(P_2\) giữ \(R_2\) và chờ \(R_1\), thì xảy ra deadlock do có chu trình chờ đợi.

---

## 8.3 Các Phương Pháp Xử Lý Deadlock

### 8.3.1 Deadlock Prevention (Phòng Ngừa Deadlock)
- **Nguyên tắc:** Thiết kế hệ thống sao cho ít nhất một trong bốn điều kiện cần của deadlock không bao giờ xảy ra.
- **Phương pháp:**  
  - **Loại trừ Hold and Wait:** Yêu cầu tiến trình phải yêu cầu tất cả tài nguyên cùng lúc hoặc không giữ tài nguyên nào khi chờ đợi tài nguyên mới.
  - **Tiền định tước đoạt (Preemption):** Cho phép tước đoạt tài nguyên từ tiến trình khi cần thiết.
  - **Phòng tránh Circular Wait:** Áp dụng thứ tự định trước cho các tài nguyên; tiến trình chỉ có thể yêu cầu tài nguyên theo thứ tự tăng dần.
- **Ưu điểm:** Ngăn chặn deadlock xảy ra từ đầu.
- **Nhược điểm:** Có thể dẫn đến lãng phí tài nguyên hoặc giảm tính linh hoạt của hệ thống.

### 8.3.2 Deadlock Avoidance (Tránh Deadlock)
- **Nguyên tắc:** Hệ thống kiểm tra trước khi cấp phát tài nguyên, đảm bảo rằng việc cấp phát không đưa hệ thống vào trạng thái không an toàn (unsafe state).
- **Ví dụ tiêu biểu:**  
  - **Banker’s Algorithm:** Dựa trên thông tin về yêu cầu tối đa của tiến trình, hệ thống quyết định cấp phát tài nguyên nếu đảm bảo rằng luôn tồn tại một chuỗi tiến trình có thể hoàn thành.
- **Ưu điểm:** Cho phép hệ thống cấp phát tài nguyên một cách linh hoạt nhưng vẫn an toàn.
- **Nhược điểm:** Yêu cầu phải có thông tin về yêu cầu tối đa của tiến trình, có thể phức tạp trong thực tế.

### 8.3.3 Deadlock Detection (Phát Hiện Deadlock)
- **Nguyên tắc:** Cho phép hệ thống xảy ra deadlock, sau đó sử dụng các thuật toán để phát hiện deadlock.
- **Phương pháp:**  
  - Sử dụng đồ thị yêu cầu tài nguyên để kiểm tra chu trình.
  - Theo dõi trạng thái hệ thống để nhận diện các tiến trình bị kẹt.
- **Ưu điểm:** Không cần thiết kế phòng tránh, linh hoạt hơn trong môi trường phức tạp.
- **Nhược điểm:** Phát hiện deadlock có thể tốn thời gian và sau khi phát hiện, hệ thống cần có cơ chế xử lý.

### 8.3.4 Recovery from Deadlock (Khắc Phục Deadlock)
- **Phương pháp:**  
  - **Tước đoạt tài nguyên:** Hủy một số tiến trình hoặc tước đoạt tài nguyên từ tiến trình bị deadlock.
  - **Rollback (Quay lui):** Chạy lại các tiến trình từ một trạng thái an toàn đã lưu trước đó.
  - **Khiến deadlock không tái diễn:** Sau khi phục hồi, hệ thống có thể áp dụng các biện pháp phòng tránh để ngăn ngừa deadlock tiếp theo.
- **Ưu điểm:** Cho phép hệ thống hồi phục và tiếp tục hoạt động sau khi deadlock xảy ra.
- **Nhược điểm:** Có thể gây mất dữ liệu hoặc làm hỏng công việc của tiến trình bị hủy.

---

## 8.4 Ví Dụ Minh Họa Deadlock

- **Ví dụ 1: Hai tiến trình và hai tài nguyên:**  
  - \(P_1\) giữ \(R_1\) và yêu cầu \(R_2\), \(P_2\) giữ \(R_2\) và yêu cầu \(R_1\). Đây là một ví dụ điển hình của deadlock do có chu trình chờ đợi.
  
- **Ví dụ 2: Sử dụng Banker’s Algorithm:**  
  - Hệ thống kiểm tra yêu cầu tài nguyên của các tiến trình trước khi cấp phát. Nếu việc cấp phát sẽ đưa hệ thống vào trạng thái không an toàn, yêu cầu bị từ chối, giúp tránh deadlock xảy ra.

---

## 8.5 Tóm Lại Chương 8

Chương 8 cung cấp một cái nhìn toàn diện về tình trạng deadlock trong hệ thống máy tính, bao gồm:

- **Các điều kiện cần thiết để deadlock xảy ra:** Mutual Exclusion, Hold and Wait, No Preemption, và Circular Wait.
- **Phân loại và đặc trưng của deadlock:** Sử dụng đồ thị yêu cầu tài nguyên để nhận diện chu trình chờ đợi.
- **Các phương pháp xử lý deadlock:**  
  - **Prevention:** Ngăn chặn deadlock bằng cách loại bỏ một trong bốn điều kiện cần thiết.
  - **Avoidance:** Kiểm tra an toàn trước khi cấp phát tài nguyên (ví dụ: Banker’s Algorithm).
  - **Detection:** Phát hiện deadlock khi xảy ra và sau đó xử lý.
  - **Recovery:** Khắc phục deadlock thông qua tước đoạt tài nguyên, rollback hoặc hủy tiến trình.
  
- **Ví dụ minh họa:**  
  - Hai tiến trình tranh chấp hai tài nguyên dẫn đến deadlock; hệ thống sử dụng Banker’s Algorithm để tránh tình trạng này hoặc phát hiện và khắc phục deadlock khi nó xảy ra.

---
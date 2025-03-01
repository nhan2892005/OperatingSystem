# Chương 5: Lập lịch CPU (CPU Scheduling)

Chương 5 của cuốn sách *Operating System Concepts* tập trung vào cách hệ điều hành quyết định chọn tiến trình nào sẽ được chạy trên CPU trong một hệ thống đa nhiệm. Việc lập lịch CPU ảnh hưởng trực tiếp đến hiệu năng, độ công bằng và khả năng phản hồi của hệ thống.

---

## 5.1 Khái Niệm Cơ Bản

- **Mục tiêu của lập lịch CPU:**  
  - Tối ưu hóa việc sử dụng CPU (CPU utilization).
  - Tăng throughput (số lượng tiến trình hoàn thành trong một khoảng thời gian nhất định).
  - Giảm thời gian phản hồi (response time) và thời gian chờ (waiting time) của tiến trình.
  - Đảm bảo tính công bằng giữa các tiến trình.
  
- **Context Switching:**  
  - Là quá trình chuyển đổi CPU từ việc thực hiện tiến trình này sang tiến trình khác.
  - Bao gồm lưu trạng thái của tiến trình hiện tại và khôi phục trạng thái của tiến trình mới.
  - Context switching tiêu tốn thời gian, do đó, tối ưu hóa việc chuyển đổi là yếu tố quan trọng trong thiết kế thuật toán lập lịch.

---

## 5.2 Tiêu Chí Lập Lịch

Các tiêu chí thường được sử dụng để đánh giá hiệu quả của thuật toán lập lịch bao gồm:
- **CPU Utilization:** Tỷ lệ thời gian CPU hoạt động hiệu quả.
- **Throughput:** Số tiến trình hoàn thành trong một đơn vị thời gian.
- **Turnaround Time:** Thời gian từ lúc tiến trình nộp yêu cầu cho đến khi hoàn thành.
- **Waiting Time:** Thời gian tiến trình chờ đợi trong hàng đợi.
- **Response Time:** Thời gian từ lúc tiến trình gửi yêu cầu đến lúc hệ thống bắt đầu phản hồi.
- **Fairness:** Đảm bảo không tiến trình nào bị "đói" CPU quá lâu.

---

## 5.3 Các Thuật Toán Lập Lịch CPU

### 5.3.1 FCFS (First-Come, First-Served)
- **Đặc điểm:**  
  - Tiến trình được thực thi theo thứ tự đến.
  - Dễ triển khai nhưng có thể dẫn đến hiện tượng “convoy effect” (hiệu ứng xe đoàn).
- **Ưu điểm:** Đơn giản, dễ hiểu.
- **Nhược điểm:** Thời gian chờ có thể rất dài đối với các tiến trình có thời gian thực thi lớn.

### 5.3.2 SJF (Shortest Job First)
- **Đặc điểm:**  
  - Ưu tiên tiến trình có thời gian thực thi ngắn nhất.
  - Có thể tối ưu hóa turnaround time.
- **Ưu điểm:** Giảm tổng thời gian chờ và turnaround time tối đa.
- **Nhược điểm:** Khó ước lượng thời gian thực thi của tiến trình; có thể gây đói tiến trình (starvation) đối với các tiến trình dài.

### 5.3.3 Round Robin (RR)
- **Đặc điểm:**  
  - Mỗi tiến trình được cấp một khoảng thời gian (time slice) cố định.
  - Sau khi hết thời gian, nếu tiến trình chưa hoàn thành thì chuyển sang cuối hàng đợi.
- **Ưu điểm:** Đáp ứng tốt trong hệ thống đa nhiệm, đảm bảo mọi tiến trình đều có cơ hội chạy.
- **Nhược điểm:** Nếu time slice quá nhỏ sẽ tăng số lần chuyển đổi ngữ cảnh, nếu quá lớn thì trở nên giống FCFS.

### 5.3.4 Lập Lịch Ưu Tiên (Priority Scheduling)
- **Đặc điểm:**  
  - Mỗi tiến trình được gán một mức ưu tiên, tiến trình có ưu tiên cao được thực thi trước.
  - Có thể thực hiện theo dạng preemptive hoặc non-preemptive.
- **Ưu điểm:** Cho phép ưu tiên xử lý các tiến trình quan trọng hoặc có tính thời gian nhạy cảm.
- **Nhược điểm:** Có thể gây ra hiện tượng đói tiến trình (starvation) đối với tiến trình có độ ưu tiên thấp.

---

## 5.4 Lập Lịch trong Môi Trường Đa Luồng và Đa Lõi

- **Thread Scheduling:**  
  - Ngoài tiến trình, hệ điều hành còn quản lý các luồng (threads) bên trong tiến trình. Các luồng này chia sẻ không gian bộ nhớ, do đó, context switching giữa các luồng thường nhẹ hơn.
  
- **Multi-Processor Scheduling:**  
  - Trong hệ thống đa lõi, lập lịch phải phân bổ công việc trên nhiều CPU.
  - Các thuật toán đa lõi cần giải quyết vấn đề cân bằng tải (load balancing) để tránh hiện tượng một CPU quá tải trong khi các CPU khác nhàn rỗi.
  
- **Ví dụ thực tế:**  
  - Trong một máy chủ xử lý nhiều kết nối mạng, các tiến trình hoặc luồng sẽ được phân bổ đồng đều trên các lõi CPU để tối ưu hóa hiệu năng và giảm thời gian xử lý yêu cầu.

---

## 5.5 Lập Lịch Thời Gian Thực (Real-Time CPU Scheduling)

- **Đặc điểm:**  
  - Được thiết kế cho các ứng dụng có yêu cầu đáp ứng nghiêm ngặt về thời gian (real-time applications).
  - Phân chia thành hai loại: **hard real-time** (đáp ứng nghiêm ngặt, không chấp nhận trễ) và **soft real-time** (có thể chấp nhận trễ nhưng cần tối thiểu hóa thời gian trễ).
  
- **Thuật toán thường dùng:**  
  - Rate Monotonic Scheduling (RMS), Earliest Deadline First (EDF).
  
- **Ví dụ thực tế:**  
  - Các hệ thống điều khiển trong ô tô hoặc thiết bị y tế, nơi mà thời gian phản hồi cực kỳ quan trọng để đảm bảo an toàn và hiệu quả hoạt động.

---

## 5.6 Đánh Giá và Ví Dụ Ứng Dụng

- **Algorithm Evaluation:**  
  - Mỗi thuật toán được đánh giá dựa trên các tiêu chí đã nêu (CPU utilization, throughput, turnaround time, waiting time, response time).
  - Sự lựa chọn thuật toán phù hợp phụ thuộc vào đặc thù của hệ thống và mục tiêu cần đạt được (ví dụ: ưu tiên phản hồi nhanh hay tối ưu hóa hiệu suất tổng thể).

- **Ví dụ ứng dụng:**  
  - Một hệ thống máy chủ web sử dụng thuật toán Round Robin để đảm bảo mọi yêu cầu của khách hàng được xử lý đều đặn, trong khi một hệ thống thời gian thực như hệ thống điều khiển robot có thể sử dụng EDF để đảm bảo tiến trình có deadline ngắn nhất được xử lý trước.

---

## 5.7 Tóm Lại Chương 5

Chương 5 cung cấp cái nhìn toàn diện về lập lịch CPU, bao gồm:
- **Khái niệm cơ bản:** Mục tiêu, tiêu chí và context switching.
- **Các thuật toán lập lịch:** FCFS, SJF, Round Robin, và Priority Scheduling, cùng với ưu, nhược điểm của từng thuật toán.
- **Lập lịch trong môi trường đa luồng và đa lõi:** Cách quản lý và phân bổ công việc trên nhiều CPU.
- **Lập lịch thời gian thực:** Các thuật toán và ứng dụng trong hệ thống yêu cầu thời gian phản hồi nghiêm ngặt.

*Ví dụ minh họa:*  
- Trong một máy chủ xử lý nhiều kết nối, việc áp dụng thuật toán Round Robin giúp đảm bảo rằng mọi tiến trình đều được cấp thời gian CPU đều đặn. Trong khi đó, trong các ứng dụng điều khiển y tế hoặc ô tô, thuật toán EDF đảm bảo rằng tiến trình có deadline gần nhất sẽ được ưu tiên xử lý, giảm thiểu rủi ro do trễ thời gian.

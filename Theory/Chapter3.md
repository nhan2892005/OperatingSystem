# Chương 3: Các Tiến Trình (Processes)

Chương 3 giới thiệu về khái niệm tiến trình, các thao tác cơ bản để quản lý tiến trình, và cách thức tiến trình giao tiếp với nhau. Đây là một trong những phần quan trọng của hệ điều hành vì tiến trình là đơn vị cơ bản để thực hiện công việc của hệ thống.

---

## 3.1 Khái Niệm Tiến Trình

- **Định nghĩa tiến trình:**  
  - Một **tiến trình** là một chương trình đang được thực thi, bao gồm mã lệnh, dữ liệu và trạng thái của tiến trình (context).  
  - Sự khác biệt giữa **chương trình** (một tập hợp mã lệnh tĩnh) và **tiến trình** (phiên bản động, chạy của chương trình).
  
- **Thành phần của tiến trình:**  
  - **Không gian địa chỉ:** Bộ nhớ chứa mã lệnh, dữ liệu, stack và heap.
  - **Ngữ cảnh tiến trình (Process Control Block - PCB):** Gồm các thông tin như số hiệu tiến trình (PID), trạng thái, thông tin CPU (registers, program counter), thông tin tài nguyên và các thông tin quản lý khác.

- **Ví dụ minh họa:**  
  - Khi bạn chạy một trình duyệt web, hệ điều hành tạo ra một tiến trình chứa mã lệnh của trình duyệt, dữ liệu như cookie, phiên làm việc… PCB của tiến trình này lưu trữ thông tin cần thiết để hệ thống có thể chuyển đổi giữa các tiến trình khi thực hiện đa nhiệm.

---

## 3.2 Lập Lịch Tiến Trình (Process Scheduling)

- **Mục tiêu lập lịch:**  
  - Tối ưu hóa việc sử dụng CPU, đảm bảo công bằng giữa các tiến trình, giảm thời gian chờ và tăng hiệu năng chung của hệ thống.
  
- **Các thuật toán lập lịch:**  
  - **FCFS (First-Come, First-Served):** Các tiến trình được phục vụ theo thứ tự đến.
  - **SJF (Shortest Job First):** Ưu tiên các tiến trình có thời gian thực thi ngắn hơn.
  - **Round Robin (RR):** Mỗi tiến trình được cấp một khoảng thời gian (time slice) cố định; khi hết thời gian, tiến trình chuyển sang trạng thái chờ.
  - **Priority Scheduling:** Mỗi tiến trình có một mức ưu tiên; tiến trình có độ ưu tiên cao hơn sẽ được chọn chạy trước.

- **Context Switching:**  
  - Khi CPU chuyển từ tiến trình này sang tiến trình khác, hệ thống phải lưu lại trạng thái của tiến trình hiện tại (trong PCB) và khôi phục trạng thái của tiến trình mới. Quá trình này gọi là **context switch**.
  
- **Ví dụ minh họa:**  
  - Trên hệ thống đa nhiệm, khi bạn chạy nhiều ứng dụng cùng lúc, thuật toán Round Robin sẽ chia nhỏ thời gian CPU cho từng tiến trình để đảm bảo tất cả ứng dụng đều có cơ hội thực thi, tạo cảm giác hoạt động mượt mà cho người dùng.

---

## 3.3 Các Hoạt Động Trên Tiến Trình

- **Tạo tiến trình:**  
  - Các hệ điều hành hỗ trợ các hàm như **fork()** (tạo ra một tiến trình con từ tiến trình cha) và **exec()** (thay thế hình ảnh tiến trình hiện tại bằng một chương trình khác).
  
- **Kết thúc tiến trình:**  
  - Khi tiến trình hoàn thành công việc, nó thực hiện lệnh **exit()** để kết thúc. Tiến trình cha thường sử dụng **wait()** để thu thập trạng thái của tiến trình con đã kết thúc.

- **Chuyển đổi trạng thái tiến trình:**  
  - Các trạng thái cơ bản của tiến trình gồm: mới, sẵn sàng (ready), chạy (running), chờ (waiting/blocked) và kết thúc (terminated).
  
- **Ví dụ minh họa:**  
  - Khi một tiến trình con được tạo ra qua fork(), tiến trình cha và tiến trình con có thể chạy song song. Sau đó, tiến trình con sẽ thực hiện exec() để chạy chương trình mới và cuối cùng kết thúc bằng exit().

---

## 3.4 Giao Tiếp Giữa Các Tiến Trình (Interprocess Communication - IPC)

- **Mục đích của IPC:**  
  - Cho phép các tiến trình độc lập trao đổi dữ liệu và đồng bộ hóa hoạt động của chúng.
  
- **Các cơ chế IPC phổ biến:**  
  - **Bộ nhớ dùng chung (Shared Memory):**  
    - Các tiến trình truy cập chung một vùng nhớ để trao đổi dữ liệu.
    - Ưu điểm: Tốc độ nhanh vì không cần sao chép dữ liệu nhiều lần.
    - Nhược điểm: Cần cơ chế đồng bộ hóa (mutex, semaphore) để tránh tranh chấp dữ liệu.
  - **Message Passing:**  
    - Các tiến trình gửi và nhận tin nhắn thông qua hệ thống hàng đợi (queue) hoặc các kênh truyền thông.
    - Ưu điểm: An toàn, dễ kiểm soát truy cập.
    - Nhược điểm: Có thể chậm hơn do chi phí sao chép dữ liệu.
  - **Pipes, Sockets, Signals:**  
    - **Pipes:** Cho phép giao tiếp theo chiều đơn giữa các tiến trình liên quan.
    - **Sockets:** Dùng cho giao tiếp mạng giữa các tiến trình, có thể ở cùng một máy hoặc khác máy.
    - **Signals:** Dùng để gửi thông báo ngắt giữa các tiến trình.

- **Ví dụ minh họa:**  
  - Trong một hệ thống máy chủ web, một tiến trình nhận kết nối (listener) sẽ giao tiếp với các tiến trình con xử lý yêu cầu thông qua socket. Cùng lúc đó, các tiến trình có thể sử dụng shared memory để trao đổi dữ liệu nhanh trong nội bộ một ứng dụng lớn.

---

## 3.5 Các Vấn Đề Nâng Cao về Tiến Trình

- **Đồng thời và cạnh tranh (Concurrency):**  
  - Khi nhiều tiến trình (hoặc luồng) cùng truy cập và thay đổi tài nguyên chung, có nguy cơ xảy ra race condition. Các cơ chế đồng bộ hóa như semaphore, mutex, và monitor được sử dụng để giải quyết vấn đề này.
  
- **Deadlock:**  
  - Xảy ra khi các tiến trình chờ nhau mãi mãi vì mỗi tiến trình giữ một tài nguyên và không giải phóng để tiến trình khác có thể sử dụng. Hệ điều hành cần phát hiện và xử lý tình huống deadlock (phòng tránh, tránh, hoặc khắc phục).
  
- **Tiến trình vs. Luồng:**  
  - **Tiến trình:** Là đơn vị thực thi độc lập, có không gian địa chỉ riêng biệt.
  - **Luồng:** Là đơn vị thực thi nhẹ hơn trong cùng một tiến trình, chia sẻ không gian địa chỉ và tài nguyên với các luồng khác trong cùng tiến trình.
  - **Ví dụ:** Một trình duyệt web có thể sử dụng luồng để tải dữ liệu, xử lý giao diện người dùng và thực hiện các tác vụ nền, giúp cải thiện hiệu năng và độ phản hồi.

---

## 3.6 Tóm Lại Chương 3

Chương 3 tập trung vào khái niệm tiến trình – đơn vị cơ bản của công việc trong hệ thống máy tính. Từ việc định nghĩa tiến trình, lưu trữ thông tin quản lý (PCB), cho đến các thao tác tạo, chuyển đổi trạng thái và kết thúc tiến trình, chương này cung cấp cái nhìn toàn diện về cách mà hệ điều hành quản lý các tác vụ đang chạy. Bên cạnh đó, các cơ chế giao tiếp giữa tiến trình (IPC) được giới thiệu nhằm đảm bảo các tiến trình có thể làm việc đồng bộ và trao đổi dữ liệu một cách an toàn. Các khái niệm nâng cao như đồng thời, cạnh tranh và deadlock cũng được đề cập để giúp người đọc hiểu được những thách thức khi xây dựng hệ thống đa nhiệm và cách giải quyết chúng.

*Ví dụ minh họa:*  
- Trong một ứng dụng đa nhiệm, khi một tiến trình chạy tác vụ tính toán nặng, hệ điều hành sẽ thực hiện context switching để chuyển CPU sang tiến trình khác nhằm đảm bảo tất cả tiến trình đều được thực hiện.  
- Một hệ thống máy chủ sử dụng IPC qua socket để giao tiếp giữa tiến trình xử lý yêu cầu và tiến trình quản lý kết nối, giúp tăng hiệu năng và khả năng mở rộng của hệ thống.

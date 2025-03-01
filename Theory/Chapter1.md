# Chương 1: Giới Thiệu (Introduction)

Chương 1 của cuốn *Operating System Concepts* giới thiệu về vai trò, chức năng và cấu trúc của hệ điều hành trong một hệ thống máy tính hiện đại. Nội dung được trình bày theo hai góc nhìn chính: góc nhìn của người dùng và góc nhìn của hệ thống (máy tính).

## 1.1 Vai Trò và Chức Năng của Hệ Điều Hành

### 1.1.1 Định Nghĩa Hệ Điều Hành
- **Hệ điều hành (OS)** là phần mềm quản lý phần cứng máy tính và cung cấp một môi trường cho các ứng dụng chạy.  
- Nó đóng vai trò **trung gian giữa người dùng, ứng dụng và phần cứng**, giúp các chương trình hoạt động hiệu quả mà không cần lo lắng về các chi tiết của phần cứng.

### 1.1.2 Chức Năng Chính của Hệ Điều Hành
- **Quản lý tài nguyên:**  
  - Phân bổ thời gian CPU, bộ nhớ, và các thiết bị I/O cho các tiến trình.
  - Ví dụ: Khi mở nhiều ứng dụng trên máy tính, OS sẽ chia sẻ thời gian CPU cho từng ứng dụng theo thuật toán lập lịch.
- **Quản lý bộ nhớ:**  
  - Chuyển đổi địa chỉ logic (virtual addresses) sang địa chỉ vật lý (physical addresses) thông qua cơ chế như phân trang (paging) hoặc phân đoạn (segmentation).
  - Ví dụ: Khi chạy một chương trình, OS nạp mã lệnh và dữ liệu của chương trình vào bộ nhớ chính (RAM) và quản lý không gian bộ nhớ cho từng tiến trình.
- **Quản lý tiến trình:**  
  - Tạo, huỷ và chuyển đổi giữa các tiến trình; đảm bảo các tiến trình được thực thi một cách đồng thời (đa nhiệm).
  - Ví dụ: Trên hệ thống đa lõi, nhiều tiến trình có thể chạy song song, giúp cải thiện hiệu năng và độ phản hồi.
- **Quản lý I/O:**  
  - Điều phối hoạt động của các thiết bị ngoại vi như bàn phím, chuột, ổ đĩa, và màn hình.
  - Ví dụ: Khi bạn gõ trên bàn phím, OS sẽ xử lý tín hiệu nhập liệu để hiển thị chữ trên màn hình.
- **Bảo mật và bảo vệ:**  
  - Kiểm soát truy cập vào tài nguyên máy tính, ngăn chặn truy cập trái phép.
  - Ví dụ: OS sử dụng cơ chế phân quyền và xác thực người dùng để đảm bảo an toàn cho hệ thống.
- **Ảo hóa:**  
  - Cho phép chạy nhiều hệ thống ảo (virtual machines) trên cùng một phần cứng, tách biệt các môi trường làm việc.
  - Ví dụ: Trong các trung tâm dữ liệu, ảo hóa giúp chạy nhiều máy chủ ảo trên một máy chủ vật lý, tối ưu hóa tài nguyên.

### 1.1.3 Góc Nhìn Người Dùng và Góc Nhìn Hệ Thống
- **Góc nhìn người dùng:**  
  - Người dùng thường thấy giao diện đồ họa (GUI) hoặc giao diện dòng lệnh (CLI) để tương tác với hệ thống.  
  - Mục tiêu là tối ưu hóa trải nghiệm, dễ sử dụng và đáp ứng nhanh.
  - Ví dụ: Trên máy tính cá nhân, giao diện Windows hay macOS được thiết kế để trực quan, dễ thao tác cho người dùng.
- **Góc nhìn hệ thống:**  
  - Từ quan điểm của máy tính, hệ điều hành là **trình quản lý tài nguyên**, chịu trách nhiệm phân bổ CPU, bộ nhớ, thiết bị lưu trữ và các thiết bị ngoại vi cho các tiến trình đang chạy.
  - OS đảm bảo rằng các yêu cầu từ các tiến trình được xử lý một cách hiệu quả và công bằng.
  - Ví dụ: Một hệ thống máy chủ phải đảm bảo rằng các ứng dụng quan trọng được ưu tiên xử lý tài nguyên để duy trì hiệu năng tổng thể.

---

## 1.2 Tổ Chức Hệ Thống Máy Tính

### 1.2.1 Các Thành Phần Cơ Bản
- **CPU (Central Processing Unit):**  
  - Bộ xử lý trung tâm thực hiện các lệnh và tính toán.  
- **Bộ nhớ chính (RAM):**  
  - Lưu trữ tạm thời các chương trình và dữ liệu khi máy tính đang hoạt động.
- **Thiết bị I/O:**  
  - Bao gồm bàn phím, chuột, màn hình, ổ đĩa, và các thiết bị ngoại vi khác.
- **Lưu trữ thứ cấp:**  
  - Ổ cứng (HDD), ổ đĩa thể rắn (SSD), và các thiết bị lưu trữ khác dùng để lưu trữ dữ liệu lâu dài.

### 1.2.2 Giao Tiếp Giữa Các Thành Phần
- **Bus và Bộ Điều Khiển Bộ Nhớ:**  
  - Các thành phần trong máy tính được kết nối qua bus, cho phép trao đổi dữ liệu giữa CPU, bộ nhớ và các thiết bị.
  - Bộ điều khiển bộ nhớ điều phối việc truy cập bộ nhớ để tránh xung đột.
- **Interrupts (Ngắt):**  
  - Là tín hiệu bất đồng bộ từ phần cứng gửi tới CPU để thông báo sự kiện cần xử lý.
  - Khi một thiết bị (như bàn phím hoặc ổ đĩa) hoàn thành một tác vụ, nó sẽ gửi tín hiệu ngắt, khiến CPU tạm dừng công việc hiện tại để xử lý yêu cầu của thiết bị đó.
  - Ví dụ: Khi máy in hoàn thành in 1 trang, nó sẽ gửi tín hiệu ngắt để báo hiệu cho OS biết công việc in đã hoàn tất.

### 1.2.3 Kiến Trúc Lưu Trữ và Hệ Thống Bộ Nhớ
- **Hệ thống lưu trữ theo cấp bậc:**
  - **Thanh ghi (Registers):** Nằm trong CPU, tốc độ rất cao nhưng dung lượng nhỏ.
  - **Cache:** Bộ nhớ nhỏ, tốc độ rất nhanh, giúp giảm độ trễ khi truy cập dữ liệu từ bộ nhớ chính.
  - **Bộ nhớ chính (RAM):** Dung lượng lớn hơn cache, tốc độ chậm hơn nhưng vẫn nhanh so với lưu trữ thứ cấp.
  - **Lưu trữ thứ cấp (HDD/SSD):** Dung lượng rất lớn, tốc độ chậm hơn, dùng để lưu trữ dữ liệu lâu dài.
  - **Lưu trữ bậc ba (Tertiary storage):** Ví dụ như băng từ, thường dùng cho sao lưu và lưu trữ dữ liệu không cần truy cập thường xuyên.
- **Ví dụ thực tế:**  
  - Một máy tính cá nhân có CPU với các thanh ghi và bộ nhớ cache nhỏ, RAM dung lượng vài GB và ổ cứng dung lượng hàng trăm GB. Các tác vụ cần tốc độ cao như xử lý video sẽ ưu tiên truy cập từ cache và RAM, trong khi các dữ liệu ít dùng đến sẽ được lưu trữ trên ổ cứng.

---

## 1.3 Các Khái Niệm và Quá Trình Quan Trọng Khác

### 1.3.1 Chuyển Đổi Chế Độ (Mode Switching)
- **User Mode vs. Kernel Mode:**  
  - **User Mode:** Chế độ chạy của ứng dụng, có quyền truy cập hạn chế vào tài nguyên hệ thống.
  - **Kernel Mode:** Chế độ chạy của hệ điều hành, cho phép truy cập trực tiếp và toàn quyền vào phần cứng.
- **Quá trình chuyển đổi:**  
  - Khi một ứng dụng cần thực hiện một thao tác đặc quyền (như truy cập thiết bị I/O), nó sẽ gọi một system call, từ đó CPU chuyển từ user mode sang kernel mode để thực hiện yêu cầu.
- **Ví dụ thực tế:**  
  - Khi một ứng dụng soạn thảo văn bản muốn lưu file, nó gọi hệ thống để ghi dữ liệu vào ổ đĩa; hệ điều hành chuyển sang kernel mode để truy cập ổ đĩa, sau đó chuyển lại về user mode.

### 1.3.2 Bộ Cấu Trúc Dữ Liệu Của Hệ Điều Hành
- **Bảng tiến trình (Process Table):**  
  - Lưu trữ thông tin về các tiến trình đang chạy, bao gồm trạng thái, thông tin tài nguyên, và ngữ cảnh của tiến trình.
- **Bảng trang (Page Table):**  
  - Dùng trong quá trình quản lý bộ nhớ, ánh xạ các địa chỉ logic sang địa chỉ vật lý.
- **Ví dụ thực tế:**  
  - Khi bạn mở nhiều cửa sổ trình duyệt, OS sử dụng bảng tiến trình để theo dõi mỗi cửa sổ (tiến trình) và bảng trang để quản lý vùng nhớ của chúng.

---

## 1.4 Tóm Lại Chương 1

Chương 1 của cuốn sách cung cấp cái nhìn tổng quát về hệ điều hành, từ vai trò trung gian giữa phần cứng và ứng dụng, cho đến các thành phần cơ bản của một hệ thống máy tính. Các khái niệm như quản lý bộ nhớ, quản lý tiến trình, giao tiếp qua ngắt, chuyển đổi chế độ và cấu trúc lưu trữ được trình bày nhằm giúp độc giả hiểu rõ hơn về cách mà các hệ điều hành hoạt động và tối ưu hóa việc sử dụng tài nguyên của máy tính.

*Ví dụ minh họa:*  
- Một smartphone chạy Android sẽ sử dụng các khái niệm trên để điều phối việc xử lý các ứng dụng (như gọi điện, nhắn tin, chơi game) trong khi vẫn duy trì tính bảo mật và hiệu năng cao.  
- Trên một máy tính cá nhân, việc nạp một ứng dụng và chuyển đổi giữa các tiến trình được thực hiện nhờ các cơ chế quản lý tiến trình và bộ nhớ đã được mô tả.

---
# Chương 2: Cấu Trúc của Hệ Điều Hành (Operating-System Structures)

Chương 2 tập trung vào cách mà hệ điều hành được tổ chức, từ các dịch vụ cốt lõi đến cách mà các thành phần giao tiếp với nhau. Nội dung này giúp ta hiểu được những yêu cầu khi thiết kế và triển khai một hệ điều hành, cũng như các phương pháp khắc phục vấn đề phát sinh trong quá trình khởi động và vận hành.

---

## 2.1 Dịch Vụ của Hệ Điều Hành (Operating-System Services)

- **Khái niệm dịch vụ:**  
  Hệ điều hành cung cấp một tập hợp các dịch vụ mà ứng dụng và người dùng có thể sử dụng để thực hiện các tác vụ cơ bản như quản lý tiến trình, quản lý bộ nhớ, xử lý tập tin, giao tiếp giữa các tiến trình (IPC), điều khiển thiết bị I/O, và bảo mật.
  
- **Các dịch vụ chính bao gồm:**
  - **Quản lý tiến trình:** Tạo, huỷ, chuyển đổi giữa các tiến trình và lập lịch CPU.
  - **Quản lý bộ nhớ:** Phân bổ bộ nhớ cho tiến trình, chuyển đổi địa chỉ logic sang địa chỉ vật lý, và quản lý bộ nhớ ảo.
  - **Quản lý tập tin:** Tạo, xóa, đọc, ghi tập tin, và quản lý hệ thống tập tin.
  - **Quản lý thiết bị I/O:** Cung cấp giao diện để truy cập và điều khiển các thiết bị ngoại vi.
  - **Bảo mật và bảo vệ:** Kiểm soát quyền truy cập, xác thực người dùng, và cách ly tiến trình.

- **Ví dụ thực tế:**  
  Khi bạn mở một ứng dụng trên máy tính, hệ điều hành phải phân bổ bộ nhớ, tạo tiến trình để chạy ứng dụng và quản lý việc truy xuất tập tin từ ổ cứng. Tất cả các thao tác này đều được thực hiện thông qua các dịch vụ của hệ điều hành.

---

## 2.2 Giao Diện Người Dùng và Giao Diện Hệ Điều Hành

- **Giao diện người dùng (User Interface):**  
  - Bao gồm giao diện đồ họa (GUI) và giao diện dòng lệnh (CLI) cho phép người dùng tương tác với hệ thống.
  - Mục tiêu là cung cấp một môi trường thân thiện, dễ sử dụng và trực quan.

- **Giao diện lập trình ứng dụng (API) và System Calls:**  
  - **API:** Bộ các hàm, thư viện cho phép lập trình viên truy cập các dịch vụ của hệ điều hành.
  - **System Calls:** Các hàm cấp thấp hơn, cung cấp cách thức giao tiếp trực tiếp giữa ứng dụng và kernel.
  - **Ví dụ:** Trong Linux, các hàm như `open()`, `read()`, `write()` được sử dụng để thao tác với tập tin thông qua các system call.

- **Ví dụ thực tế:**  
  Khi bạn sử dụng terminal trên Linux để liệt kê tập tin (lệnh `ls`), hệ thống sẽ thực hiện các system call để truy xuất thông tin từ hệ thống tập tin, sau đó trả về kết quả cho người dùng qua giao diện dòng lệnh.

---

## 2.3 Hệ Thống Gọi Hệ Thống (System Calls)

- **Định nghĩa:**  
  System calls là giao diện mà ứng dụng sử dụng để yêu cầu các dịch vụ từ kernel. Chúng cho phép ứng dụng chuyển từ user mode sang kernel mode để thực hiện các tác vụ cần quyền đặc biệt.

- **Cách thức hoạt động:**  
  1. **Gọi từ ứng dụng:** Ứng dụng gọi một hàm hệ thống (ví dụ: `fork()`, `exec()`, `read()`, `write()`).
  2. **Chuyển đổi chế độ:** CPU chuyển đổi từ user mode sang kernel mode.
  3. **Thực hiện yêu cầu:** Kernel thực hiện tác vụ được yêu cầu, ví dụ như tạo tiến trình mới hoặc truy xuất dữ liệu từ ổ đĩa.
  4. **Trả kết quả:** Sau khi hoàn tất, kernel chuyển lại về user mode và trả kết quả cho ứng dụng.

- **Ví dụ thực tế:**  
  Khi một trình duyệt web muốn tải nội dung từ internet, nó sẽ sử dụng system call để truy cập vào card mạng, sau đó kernel sẽ xử lý yêu cầu và truyền dữ liệu trả về cho trình duyệt.

---

## 2.4 Các Dịch Vụ Hệ Thống và Cách Triển Khai

- **Hệ Thống Dịch Vụ (System Services):**  
  Các dịch vụ này cung cấp một bộ các hàm và giao diện cho các lập trình viên phát triển ứng dụng. Các dịch vụ này có thể bao gồm:
  - **Quản lý tiến trình:** Xử lý tạo, hủy và chuyển đổi giữa các tiến trình.
  - **Quản lý bộ nhớ:** Cung cấp cơ chế quản lý bộ nhớ ảo, như phân trang, swap, và cấp phát động.
  - **Quản lý tập tin:** Xây dựng hệ thống tập tin với các cấu trúc như inode, directory, và phân quyền truy cập.
  - **Quản lý thiết bị I/O:** Các driver thiết bị cung cấp giao diện thống nhất cho các loại thiết bị khác nhau.

- **Triển khai:**
  - **Kernel:** Là phần mềm chạy ở chế độ đặc quyền, thực hiện các dịch vụ cốt lõi.
  - **Các module hệ thống:** Một số hệ điều hành hỗ trợ nạp (load) hoặc gỡ bỏ (unload) các module mở rộng nhằm tăng tính linh hoạt và mở rộng chức năng mà không cần khởi động lại hệ thống.
  - **Ví dụ:** Linux sử dụng mô hình kernel đơn với khả năng mở rộng thông qua các module động, giúp cập nhật hoặc thêm driver mà không cần khởi động lại máy.

---

## 2.5 Linkers và Loaders

- **Linkers:**
  - Kết hợp các đoạn mã và dữ liệu từ các tệp đối tượng khác nhau thành một chương trình thực thi duy nhất.
  - Giải quyết các vấn đề về liên kết giữa các hàm, biến và thư viện.
  
- **Loaders:**
  - Nạp chương trình thực thi từ ổ đĩa vào bộ nhớ.
  - Thiết lập không gian địa chỉ, ánh xạ các đoạn mã và dữ liệu theo yêu cầu của kernel.
  
- **Ví dụ thực tế:**  
  Khi bạn chạy một ứng dụng, loader sẽ đọc file thực thi từ ổ cứng, sau đó tải nó vào RAM, nạp các thư viện cần thiết và khởi động chương trình.

---

## 2.6 Tại Sao Ứng Dụng Phụ Thuộc Vào Hệ Điều Hành

- **Phụ thuộc vào hệ điều hành:**  
  - Các ứng dụng thường phải được viết dựa trên API và system calls của hệ điều hành cụ thể.
  - Điều này có nghĩa là một ứng dụng được viết cho Windows có thể không chạy trực tiếp trên Linux mà không có sự tương thích.
  
- **Lý do:**  
  - Mỗi hệ điều hành có kiến trúc và cách quản lý tài nguyên riêng, từ cách gọi hàm hệ thống đến cách xử lý giao tiếp giữa các tiến trình.
  
- **Ví dụ thực tế:**  
  - Các ứng dụng desktop thường sử dụng các thư viện GUI đặc trưng của từng hệ điều hành (ví dụ: WinAPI cho Windows, GTK hoặc Qt cho Linux).

---

## 2.7 Thiết Kế và Triển Khai Hệ Điều Hành

- **Quy trình thiết kế:**
  - **Xác định mục tiêu:** Định nghĩa rõ ràng các chức năng và dịch vụ mà hệ điều hành cần cung cấp.
  - **Chia nhỏ hệ thống:** Phân chia hệ điều hành thành các module hoặc lớp với các nhiệm vụ riêng biệt (ví dụ: quản lý tiến trình, quản lý bộ nhớ, quản lý tập tin).
  - **Lập kế hoạch triển khai:** Chọn kiến trúc (monolithic, microkernel, hybrid) và xác định cách thức giao tiếp giữa các thành phần.
  
- **Các vấn đề triển khai:**
  - **Hiệu năng:** Đảm bảo hệ điều hành có thể xử lý các yêu cầu nhanh chóng, tối ưu hóa tài nguyên.
  - **Bảo mật:** Thiết kế các cơ chế để ngăn chặn truy cập trái phép và bảo vệ dữ liệu.
  - **Độ ổn định:** Quản lý lỗi và đảm bảo rằng lỗi của một thành phần không ảnh hưởng đến toàn bộ hệ thống.
  
- **Ví dụ thực tế:**  
  - Hệ điều hành Linux được thiết kế theo mô hình monolithic nhưng lại hỗ trợ nạp module động, giúp cân bằng giữa hiệu năng và khả năng mở rộng.

---

## 2.8 Cấu Trúc Hệ Điều Hành

- **Các mô hình kiến trúc chính:**
  - **Kernel đơn (Monolithic Kernel):** Tất cả các chức năng (quản lý tiến trình, bộ nhớ, tập tin, …) đều được tích hợp vào một khối kernel duy nhất.
  - **Microkernel:** Chỉ chứa các chức năng cốt lõi trong kernel, các dịch vụ khác được tách ra và chạy ở không gian người dùng, giao tiếp qua message passing.
  - **Hybrid kernel:** Kết hợp các đặc điểm của monolithic kernel và microkernel để tối ưu hóa hiệu năng và tính mở rộng.
  - **Layered kernel:** Chia kernel thành các lớp, mỗi lớp chỉ tương tác với lớp kế bên, giúp tổ chức mã nguồn rõ ràng và dễ bảo trì.
  
- **Ví dụ thực tế:**  
  - Windows và Linux chủ yếu sử dụng kiến trúc kernel đơn với một số tính năng mở rộng, trong khi các hệ điều hành như MINIX hoặc QNX áp dụng kiến trúc microkernel.

---

## 2.9 Quá Trình Xây Dựng và Khởi Động Hệ Điều Hành

- **Quá trình boot (Khởi động):**
  - **BIOS/UEFI:** Bộ phần mềm khởi động ban đầu kiểm tra phần cứng và nạp bootloader.
  - **Bootloader (ví dụ: GRUB):** Nạp kernel của hệ điều hành vào bộ nhớ, thiết lập các tham số ban đầu.
  - **Kernel:** Sau khi được nạp, kernel bắt đầu khởi tạo hệ thống, cấu hình các driver thiết bị, và bắt đầu tạo các tiến trình hệ thống (như tiến trình init hoặc systemd).
  
- **Debugging (Gỡ lỗi):**
  - Các công cụ và phương pháp để xác định và khắc phục lỗi trong quá trình khởi động và vận hành hệ điều hành.
  - Ví dụ: Sử dụng công cụ gỡ lỗi như GDB, hoặc các log hệ thống để theo dõi quá trình khởi động.

---

## 2.10 Các Vấn Đề Nâng Cao Khác

- **Tính hiệu năng và độ tin cậy:**
  - Cần đảm bảo rằng các dịch vụ của hệ điều hành được thực hiện một cách tối ưu để giảm độ trễ và tăng thông lượng.
  - Các phương pháp tối ưu hóa bao gồm caching, giảm thiểu số lần chuyển đổi chế độ, và tối ưu hóa lập lịch.
  
- **An toàn và bảo mật:**
  - Xây dựng các cơ chế để ngăn chặn lỗi và tấn công, chẳng hạn như kiểm soát truy cập, phân quyền, sandboxing, và ảo hóa.
  
- **Khả năng mở rộng:**
  - Thiết kế hệ điều hành để có thể mở rộng cho các hệ thống đa nhân, hệ thống phân tán hoặc ảo hóa.
  - Ví dụ: Trong các trung tâm dữ liệu hiện đại, khả năng mở rộng của hệ điều hành giúp tận dụng tối đa tài nguyên phần cứng và cung cấp dịch vụ liên tục cho người dùng.

---

## 2.11 Tóm Lại Chương 2

Chương 2 cung cấp một cái nhìn toàn diện về cấu trúc của hệ điều hành, từ các dịch vụ cốt lõi đến giao diện lập trình và cách mà các thành phần nội bộ phối hợp với nhau. Các khái niệm như system calls, linkers và loaders, kiến trúc kernel (monolithic, microkernel, hybrid) cùng với quá trình boot hệ thống được giải thích nhằm tạo nền tảng cho việc hiểu cách hệ điều hành quản lý tài nguyên và xử lý các yêu cầu từ ứng dụng.

*Ví dụ minh họa:*  
- Khi bạn chạy một ứng dụng trên máy tính, loader nạp chương trình vào bộ nhớ, hệ điều hành sử dụng system calls để yêu cầu các dịch vụ cần thiết (như đọc dữ liệu từ ổ cứng), và các module kernel sẽ tương tác qua lại theo kiến trúc đã định để đảm bảo ứng dụng chạy mượt mà, an toàn và hiệu năng cao.

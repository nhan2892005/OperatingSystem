# Chương 13: File-System Interface (Giao Diện Hệ Thống Tập Tin)

File system interface là thành phần quan trọng của hệ điều hành, cung cấp cách thức trừu tượng hóa việc lưu trữ, truy xuất và quản lý dữ liệu dưới dạng tập tin cho các ứng dụng. Chương 13 giúp người đọc hiểu cách hệ điều hành xử lý tập tin và thư mục, các phương thức truy cập và bảo vệ thông tin.

---

## 13.1 File Concept (Khái Niệm Tập Tin)

- **Định nghĩa tập tin:**  
  - Tập tin là một tập hợp các byte dữ liệu được lưu trữ trên thiết bị lưu trữ.  
  - Nó có thể chứa dữ liệu văn bản, nhị phân, hình ảnh, âm thanh hoặc chương trình thực thi.

- **Thuộc tính của tập tin:**  
  - Tên, kích thước, ngày tạo, ngày sửa đổi, quyền truy cập và thông tin liên quan đến vị trí lưu trữ trên đĩa.
  - Các hệ thống tập tin thường lưu trữ thông tin này trong các cấu trúc như inode (trên Unix/Linux) hay file allocation table (FAT) trên một số hệ thống khác.

- **Mục đích:**  
  - Tập tin giúp tổ chức và lưu trữ dữ liệu một cách có hệ thống, hỗ trợ việc chia sẻ và truy xuất dữ liệu giữa các ứng dụng.

---

## 13.2 Access Methods (Phương Pháp Truy Cập Tập Tin)

- **Truy cập tuần tự (Sequential Access):**  
  - Dữ liệu được đọc theo thứ tự từ đầu đến cuối.  
  - Phù hợp với các ứng dụng xử lý file log, văn bản hoặc luồng dữ liệu liên tục.

- **Truy cập trực tiếp (Direct/Random Access):**  
  - Cho phép truy cập bất kỳ phần nào của tập tin mà không cần đọc toàn bộ file từ đầu.  
  - Thường dùng trong các hệ thống cơ sở dữ liệu hoặc file đa phương tiện.

- **Ví dụ minh họa:**  
  - Một ứng dụng xử lý video cần truy cập trực tiếp đến các frame cụ thể trong file video, trong khi một trình đọc văn bản có thể dùng phương pháp truy cập tuần tự để đọc nội dung.

---

## 13.3 Directory Structure (Cấu Trúc Thư Mục)

- **Cấu trúc thư mục:**  
  - Thư mục (directory) là một tập hợp các tập tin và các thư mục con, tạo thành một cấu trúc phân cấp.  
  - Cấu trúc này cho phép tổ chức và quản lý dữ liệu một cách hợp lý, giúp người dùng dễ dàng định vị và truy cập các tập tin.

- **Đường dẫn (Path):**  
  - Đường dẫn tuyệt đối và đường dẫn tương đối dùng để xác định vị trí của tập tin hoặc thư mục trong hệ thống.
  
- **Ví dụ minh họa:**  
  - Trên hệ điều hành Windows, một đường dẫn có thể là `C:\Users\Username\Documents\file.txt`; trên Unix/Linux, đường dẫn tương ứng có thể là `/home/username/documents/file.txt`.

---

## 13.4 File Protection (Bảo Vệ Tập Tin)

- **Mục đích:**  
  - Bảo vệ dữ liệu lưu trữ trong tập tin khỏi truy cập trái phép, thay đổi hoặc xóa nhầm.
  
- **Các cơ chế bảo vệ:**  
  - **Phân quyền (Permissions):** Gán quyền đọc, ghi, thực thi cho chủ sở hữu, nhóm và người dùng khác.
  - **Access Control Lists (ACLs):** Cung cấp mức độ kiểm soát chi tiết hơn so với phân quyền cơ bản.
  - **Mã hóa:** Một số hệ thống còn hỗ trợ mã hóa tập tin để tăng cường bảo mật.

- **Ví dụ minh họa:**  
  - Trên Unix/Linux, các quyền truy cập được hiển thị với các ký hiệu như `rwx` (read, write, execute) cho chủ sở hữu, nhóm và người dùng khác.

---

## 13.5 Memory-Mapped Files

- **Khái niệm:**  
  - Memory-mapped file là kỹ thuật ánh xạ nội dung của tập tin vào không gian địa chỉ của tiến trình, cho phép xử lý file thông qua truy cập bộ nhớ.
  
- **Ưu điểm:**  
  - Tăng tốc độ truy xuất file vì dữ liệu được truy cập trực tiếp từ bộ nhớ thay vì thông qua các thao tác I/O truyền thống.
  - Hỗ trợ chia sẻ dữ liệu giữa các tiến trình thông qua không gian địa chỉ chung.

- **Ví dụ minh họa:**  
  - Một ứng dụng xử lý ảnh có thể sử dụng memory-mapped file để ánh xạ file ảnh vào bộ nhớ, sau đó truy xuất và chỉnh sửa dữ liệu ảnh thông qua các phép toán trên bộ nhớ, giúp cải thiện hiệu năng.

---

## 13.6 Tóm Lại Chương 13

Chương 13 cung cấp cái nhìn tổng quan về giao diện hệ thống tập tin của hệ điều hành, bao gồm:

- **File Concept:** Tập tin là đơn vị cơ bản lưu trữ dữ liệu, có các thuộc tính và thông tin liên quan để quản lý.
- **Access Methods:** Các phương pháp truy cập tập tin như truy cập tuần tự và truy cập trực tiếp phục vụ các nhu cầu khác nhau của ứng dụng.
- **Directory Structure:** Cấu trúc phân cấp của thư mục giúp tổ chức và định vị tập tin một cách hiệu quả.
- **File Protection:** Các cơ chế bảo vệ tập tin như phân quyền, ACL và mã hóa giúp đảm bảo an toàn dữ liệu.
- **Memory-Mapped Files:** Kỹ thuật ánh xạ tập tin vào bộ nhớ cho phép truy xuất nhanh và chia sẻ dữ liệu giữa các tiến trình.

*Ví dụ minh họa:*  
- Một hệ thống quản lý tài liệu trên máy chủ sử dụng cấu trúc thư mục phân cấp để lưu trữ các file văn bản, áp dụng các quyền truy cập để bảo vệ dữ liệu, và sử dụng memory-mapped files để xử lý các file lớn một cách hiệu quả.

---
# Chương 15: File-System Internals (Bên Trong Hệ Thống Tập Tin)

Chương 15 đi sâu vào nội bộ của hệ thống tập tin, giải thích các cấu trúc, cơ chế và thuật toán được sử dụng để quản lý và duy trì dữ liệu trên ổ đĩa. Các khái niệm chính bao gồm việc mount file system, quản lý phân vùng, cơ chế chia sẻ tập tin, lớp trừu tượng VFS, truy cập tập tin từ xa và các chính sách nhất quán dữ liệu.

---

## 15.1 Tổng Quan về Hệ Thống Tập Tin

- **Khái niệm chung:**  
  - Hệ thống tập tin xác định cách thức lưu trữ, truy xuất và quản lý các tập tin trên thiết bị lưu trữ.  
  - Nó bao gồm các thành phần như siêu khối (superblock), inode (hoặc File Control Block – FCB), danh sách các block dữ liệu và cấu trúc thư mục.
  
- **Mục tiêu:**  
  - Tổ chức dữ liệu một cách hợp lý để cho phép truy xuất nhanh chóng, bảo vệ dữ liệu và hỗ trợ chia sẻ giữa các người dùng và tiến trình.

---

## 15.2 File-System Mounting (Quá Trình Mount Hệ Thống Tập Tin)

- **Mounting:**  
  - Quá trình “gắn” một hệ thống tập tin từ một thiết bị lưu trữ (ví dụ: ổ cứng, USB) vào cây thư mục của hệ điều hành.  
  - Cho phép hệ điều hành truy cập và quản lý tập tin trên thiết bị đó như một phần của hệ thống tập tin chung.
  
- **Unmounting:**  
  - Quá trình tách rời hệ thống tập tin khỏi cây thư mục, đảm bảo rằng tất cả dữ liệu đã được ghi vào thiết bị và không còn tiến trình nào đang sử dụng hệ thống đó.

- **Ví dụ minh họa:**  
  - Trên Linux, lệnh `mount` được sử dụng để gắn ổ đĩa vào thư mục như `/mnt/usb`, và `umount` để gỡ bỏ.

---

## 15.3 Partitions and Mounting (Phân Vùng và Mount)

- **Phân vùng (Partitioning):**  
  - Ổ đĩa cứng được chia thành các vùng riêng biệt, mỗi vùng có thể chứa một hệ thống tập tin độc lập.  
  - Có các loại phân vùng như phân vùng chính (primary) và phân vùng mở rộng (extended).
  
- **Mount theo phân vùng:**  
  - Mỗi phân vùng được mount riêng biệt vào hệ thống tập tin.  
  - Điều này giúp quản lý tài nguyên lưu trữ hiệu quả và tạo ra sự phân chia rõ ràng giữa các loại dữ liệu (ví dụ: hệ điều hành, dữ liệu người dùng).

- **Ví dụ minh họa:**  
  - Một máy tính có thể có một phân vùng dành cho hệ điều hành (mount tại `/`) và một phân vùng khác cho dữ liệu người dùng (mount tại `/home`).

---

## 15.4 File Sharing (Chia Sẻ Tập Tin)

- **Mục đích:**  
  - Cho phép nhiều người dùng hoặc tiến trình truy cập và sử dụng chung một tập tin.
  
- **Các cơ chế hỗ trợ:**  
  - **File Locking:** Giúp ngăn chặn các tiến trình ghi đè lẫn nhau khi cùng truy cập tập tin.  
  - **Quyền truy cập và ACLs:** Xác định ai được phép đọc, ghi hay thực thi tập tin.
  
- **Ví dụ minh họa:**  
  - Trong một hệ thống cơ sở dữ liệu, nhiều tiến trình có thể đọc dữ liệu từ một tập tin đồng thời, nhưng khi một tiến trình cần ghi, nó phải đặt khóa để đảm bảo dữ liệu không bị hỏng.

---

## 15.5 Virtual File Systems (VFS)

- **Khái niệm:**  
  - Virtual File System là lớp trừu tượng nằm giữa các ứng dụng và các hệ thống tập tin cụ thể.  
  - Nó cung cấp giao diện thống nhất để truy xuất tập tin, bất kể hệ thống tập tin vật lý nào đang được sử dụng.
  
- **Lợi ích:**  
  - Cho phép hệ điều hành hỗ trợ nhiều loại hệ thống tập tin khác nhau (như FAT, NTFS, ext4) qua cùng một API.
  - Tăng tính di động và khả năng mở rộng của các ứng dụng.
  
- **Ví dụ minh họa:**  
  - Một ứng dụng trên Linux có thể truy xuất tập tin trên ổ đĩa cục bộ (ext4), ổ đĩa USB (FAT32) hoặc qua mạng (NFS) mà không cần thay đổi cách gọi các hàm truy xuất tập tin.

---

## 15.6 Remote File Systems (Hệ Thống Tập Tin Từ Xa)

- **Khái niệm:**  
  - Remote File Systems cho phép truy xuất tập tin trên các máy chủ từ xa thông qua mạng.  
  - Các giao thức phổ biến bao gồm NFS (Network File System), SMB/CIFS (dùng trong Windows) và AFP (Apple Filing Protocol).
  
- **Chức năng:**  
  - Cho phép người dùng truy cập tập tin từ xa như thể chúng đang được lưu trữ cục bộ.
  
- **Ví dụ minh họa:**  
  - NFS cho phép một máy tính Linux mount một hệ thống tập tin từ máy chủ khác, hỗ trợ chia sẻ dữ liệu trong các môi trường mạng nội bộ hoặc trên internet.

---

## 15.7 Consistency Semantics (Chính Sách Nhất Quán Dữ Liệu)

- **Định nghĩa:**  
  - Consistency Semantics liên quan đến việc đảm bảo rằng các thay đổi đối với tập tin và dữ liệu được thực hiện một cách nhất quán trên hệ thống tập tin, bất kể có sự truy cập đồng thời hay truy cập từ xa.
  
- **Các vấn đề cần xử lý:**  
  - **Caching:** Cách làm mới và duy trì tính nhất quán của dữ liệu được lưu trong bộ nhớ đệm.
  - **Journaling:** Ghi lại các thay đổi trước khi thực hiện để có thể phục hồi dữ liệu nếu có lỗi xảy ra.
  - **Sự nhất quán giữa các client:** Đặc biệt quan trọng với các hệ thống tập tin từ xa, đảm bảo rằng tất cả các client đều thấy dữ liệu giống nhau.

- **Ví dụ minh họa:**  
  - Trong một hệ thống NFS, nếu một client chỉnh sửa tập tin và ghi đè dữ liệu, các client khác phải được thông báo để cập nhật bộ nhớ đệm của họ, nhằm tránh xung đột và lỗi không nhất quán.

---

## 15.8 NFS (Network File System)

- **Khái niệm:**  
  - NFS là một giao thức cho phép các hệ thống máy tính truy xuất tập tin từ xa qua mạng một cách hiệu quả, như thể tập tin đó được lưu trữ cục bộ.
  
- **Kiến trúc:**  
  - NFS hoạt động theo mô hình client-server, nơi máy chủ NFS quản lý hệ thống tập tin và các client truy xuất thông qua các yêu cầu mạng.
  
- **Lợi ích:**  
  - Tích hợp dễ dàng trong môi trường mạng, hỗ trợ chia sẻ tài nguyên và làm việc nhóm.
  
- **Ví dụ minh họa:**  
  - Trong các trung tâm dữ liệu, NFS cho phép các máy chủ truy cập dữ liệu từ một hệ thống lưu trữ tập trung, giảm thiểu sự trùng lặp và tăng tính linh hoạt trong quản lý tài nguyên.

---

## 15.9 Tóm Lại Chương 15

Chương 15 cung cấp cái nhìn sâu sắc vào nội bộ của hệ thống tập tin, bao gồm:

- **File Systems Overview:** Cách thức dữ liệu được tổ chức và lưu trữ, thông qua các cấu trúc như inode/FCB và thư mục.
- **Mounting:** Quá trình gắn kết hệ thống tập tin vào cây thư mục của hệ điều hành, cho phép truy xuất tập tin.
- **Partitions:** Phân vùng ổ đĩa và cách mount chúng để phân chia rõ ràng tài nguyên lưu trữ.
- **File Sharing:** Các cơ chế cho phép nhiều tiến trình hoặc người dùng truy cập tập tin đồng thời, với các phương pháp khóa và quyền truy cập.
- **Virtual File Systems (VFS):** Lớp trừu tượng giúp truy xuất tập tin đồng nhất bất kể hệ thống tập tin vật lý.
- **Remote File Systems:** Cung cấp khả năng truy xuất tập tin từ xa thông qua các giao thức như NFS.
- **Consistency Semantics:** Đảm bảo tính nhất quán của dữ liệu trong môi trường có truy cập đồng thời và từ xa.
- **NFS:** Một giao thức phổ biến cho phép truy cập tập tin từ xa trong môi trường mạng.

*Ví dụ minh họa:*  
- Một công ty sử dụng NFS cho phép nhân viên truy cập tập tin trên một máy chủ lưu trữ tập trung. Hệ thống VFS cho phép ứng dụng trên các máy khách truy cập các hệ thống tập tin khác nhau (cục bộ, từ xa) mà không cần thay đổi mã nguồn. Đồng thời, các cơ chế nhất quán như journaling và cache coherency đảm bảo rằng mọi thay đổi đều được cập nhật đồng bộ giữa các client.

---

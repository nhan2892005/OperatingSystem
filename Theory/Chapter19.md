# Chương 19: Networks and Distributed Systems (Mạng và Hệ thống Phân tán)

Chương 19 giải thích cách các hệ thống phân tán và mạng máy tính hoạt động, từ cấu trúc mạng, các vấn đề giao tiếp giữa các nút (node) đến các dịch vụ phân tán như hệ thống tập tin phân tán. Mục tiêu là giúp người đọc hiểu được cách các hệ thống này cung cấp hiệu năng cao, khả năng mở rộng và độ tin cậy trong môi trường tính toán hiện đại.

---

## 19.1 Advantages of Distributed Systems (Ưu điểm của Hệ thống Phân tán)

- **Tài nguyên chia sẻ:**  
  - Các hệ thống phân tán cho phép chia sẻ tài nguyên (CPU, bộ nhớ, lưu trữ) giữa nhiều máy tính, giúp tận dụng tối đa khả năng của phần cứng.
- **Khả năng mở rộng:**  
  - Dễ dàng thêm các nút mới vào hệ thống để tăng khả năng xử lý và lưu trữ.
- **Độ tin cậy và chịu lỗi:**  
  - Nếu một nút gặp sự cố, các nút khác vẫn có thể tiếp tục cung cấp dịch vụ, giúp tăng độ sẵn sàng của hệ thống.
- **Hiệu suất:**  
  - Các tác vụ có thể được xử lý song song trên nhiều máy, giúp cải thiện thông lượng và thời gian phản hồi.

---

## 19.2 Network Structure (Cấu trúc Mạng)

- **Các thành phần cấu thành mạng:**  
  - **Nút (Nodes):** Các máy tính hoặc thiết bị kết nối trong mạng.
  - **Giao thức mạng:** Các quy tắc và định dạng để truyền tải dữ liệu (ví dụ: TCP/IP).
  - **Topologies (Mô hình kết nối):** Các cách sắp xếp các nút trong mạng (như bus, star, mesh, ring).
- **Ví dụ minh họa:**  
  - Một mạng LAN trong văn phòng sử dụng mô hình star, nơi các máy tính kết nối đến một thiết bị trung tâm (switch) để giao tiếp với nhau.

---

## 19.3 Communication Structure (Cấu trúc Giao tiếp)

- **Message Passing:**  
  - Các nút trong hệ thống phân tán giao tiếp qua việc gửi và nhận thông điệp.  
  - Giao thức truyền thông đảm bảo dữ liệu được chuyển một cách đáng tin cậy.
- **Remote Procedure Call (RPC):**  
  - Cho phép một chương trình trên một máy gọi hàm (procedure) trên máy khác như thể nó là một hàm cục bộ, ẩn đi sự phức tạp của giao tiếp mạng.
- **Ví dụ minh họa:**  
  - Một ứng dụng web có thể sử dụng RPC để truy xuất dữ liệu từ một máy chủ cơ sở dữ liệu từ xa.

---

## 19.4 Design Issues in Distributed Systems (Vấn đề Thiết kế Hệ thống Phân tán)

- **Đồng bộ hóa và nhất quán dữ liệu:**  
  - Các nút phải làm việc cùng nhau để đảm bảo dữ liệu được cập nhật và nhất quán.
- **Bảo mật:**  
  - Phải bảo vệ thông tin truyền qua mạng và đảm bảo rằng chỉ có người dùng được ủy quyền mới có thể truy cập dữ liệu.
- **Chịu lỗi và khả năng phục hồi:**  
  - Hệ thống cần phát hiện và xử lý các lỗi, cho phép các nút bị lỗi được thay thế hoặc khôi phục.
- **Hiệu năng và mở rộng:**  
  - Thiết kế phải đảm bảo hệ thống có thể mở rộng và vẫn duy trì hiệu suất khi số lượng nút tăng lên.
- **Ví dụ minh họa:**  
  - Trong một hệ thống giao dịch trực tuyến, việc duy trì tính nhất quán giữa các nút phân tán là rất quan trọng để tránh lỗi giao dịch.

---

## 19.5 Distributed File Systems (Hệ thống Tập tin Phân tán)

- **Định nghĩa:**  
  - Hệ thống tập tin phân tán cho phép các nút truy cập và chia sẻ tập tin qua mạng như thể tập tin đó được lưu trữ cục bộ.
- **Các vấn đề cần xử lý:**  
  - **Định danh và truy cập:** Cung cấp một hệ thống định danh thống nhất cho các tập tin.
  - **Nhất quán dữ liệu:** Đảm bảo rằng các thay đổi được cập nhật đồng bộ trên tất cả các nút.
- **Ví dụ minh họa:**  
  - Google File System (GFS) và Hadoop Distributed File System (HDFS) là các hệ thống tập tin phân tán được sử dụng trong các trung tâm dữ liệu quy mô lớn để lưu trữ và xử lý dữ liệu.

---

## 19.6 DFS Naming and Transparency (Định danh và Tính Minh bạch của Hệ thống Tập tin Phân tán)

- **DFS Naming:**  
  - Cung cấp một không gian tên duy nhất cho các tập tin trên toàn bộ hệ thống phân tán, giúp người dùng không cần biết vị trí lưu trữ cụ thể.
- **Transparency:**  
  - Hệ thống phân tán được thiết kế sao cho người dùng và ứng dụng có thể truy xuất tập tin mà không cần biết chúng được lưu trữ ở đâu hay cách thức kết nối giữa các nút.
- **Ví dụ minh họa:**  
  - Một ứng dụng có thể mở tập tin từ một đường dẫn duy nhất dù tập tin đó được phân phối trên nhiều máy chủ trong mạng.

---

## 19.7 Remote File Access (Truy cập Tập tin Từ xa)

- **Khái niệm:**  
  - Cho phép các ứng dụng truy xuất tập tin trên máy chủ từ xa thông qua mạng.
- **Giao thức phổ biến:**  
  - NFS (Network File System), SMB/CIFS, AFP,…
- **Ví dụ minh họa:**  
  - Trong môi trường doanh nghiệp, người dùng có thể truy cập tập tin từ máy chủ file qua giao thức NFS như thể chúng được lưu trữ trên ổ cứng cục bộ.

---

## 19.8 Tóm Lại Chương 19

Chương 19 cung cấp cái nhìn tổng quan về mạng và hệ thống phân tán, bao gồm:

- **Ưu điểm của hệ thống phân tán:** Chia sẻ tài nguyên, mở rộng dễ dàng, khả năng chịu lỗi và cải thiện hiệu suất.
- **Cấu trúc mạng:** Các thành phần của mạng, mô hình kết nối và giao thức truyền thông.
- **Cấu trúc giao tiếp:** Message passing, RPC và các cơ chế để các nút giao tiếp hiệu quả.
- **Các vấn đề thiết kế:** Đồng bộ hóa, bảo mật, chịu lỗi, nhất quán và khả năng mở rộng.
- **Hệ thống tập tin phân tán:** Định danh, tính minh bạch và truy cập tập tin từ xa qua DFS và giao thức như NFS.
- **Ví dụ minh họa:**  
  - Một trung tâm dữ liệu sử dụng DFS cho phép các máy chủ truy cập tập tin từ xa, đồng thời áp dụng các cơ chế đồng bộ và bảo mật để đảm bảo dữ liệu luôn nhất quán và an toàn.

---
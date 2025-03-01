# Chương 14: File-System Implementation (Triển Khai Hệ Thống Tập Tin)

Chương 14 giải thích cách thức hệ điều hành triển khai một hệ thống tập tin. Nó đề cập đến các cấu trúc dữ liệu và thuật toán cần thiết để quản lý tập tin, tổ chức thư mục, cấp phát không gian lưu trữ, quản lý vùng trống (free space) cũng như các phương pháp đảm bảo hiệu năng và tính nhất quán của dữ liệu.

---

## 14.1 Cấu Trúc Hệ Thống Tập Tin

- **Mục tiêu:**  
  - Định nghĩa cách dữ liệu được tổ chức và lưu trữ trên thiết bị lưu trữ.  
  - Tạo ra một hệ thống trừu tượng giúp người dùng và ứng dụng thao tác với tập tin một cách đơn giản mà không cần quan tâm đến chi tiết của phần cứng lưu trữ.

- **Các thành phần chính:**  
  - **File Control Block (FCB) hoặc Inode:**  
    - Lưu trữ các thuộc tính của tập tin như kích thước, quyền truy cập, thời gian tạo, sửa đổi, và vị trí lưu trữ trên đĩa.  
  - **Directory Entry:**  
    - Dùng để liên kết tên tập tin với inode hoặc FCB, giúp hệ thống tra cứu nhanh chóng.

- **Ví dụ minh họa:**  
  - Trong hệ thống Unix, mỗi tập tin được biểu diễn bởi một inode, chứa thông tin cần thiết để truy cập dữ liệu của tập tin đó.

---

## 14.2 File-System Operations (Các Phép Toán Trên Tập Tin)

- **Các thao tác cơ bản:**  
  - **Tạo tập tin (create):** Khởi tạo inode và cập nhật thư mục.
  - **Đọc/ghi tập tin (read/write):** Truy xuất dữ liệu từ/đến ổ đĩa dựa trên các địa chỉ được lưu trong inode.
  - **Xóa tập tin (delete):** Xoá inode và cập nhật lại danh sách tập tin trong thư mục.
  - **Di chuyển/đổi tên (rename/move):** Thay đổi liên kết trong cấu trúc thư mục mà không cần sao chép dữ liệu.

- **Ý nghĩa:**  
  - Các thao tác này được thực hiện thông qua việc truy xuất và cập nhật các cấu trúc dữ liệu nội bộ của hệ thống tập tin, đảm bảo tính nhất quán của dữ liệu lưu trữ.

---

## 14.3 Directory Implementation (Triển Khai Thư Mục)

- **Cấu trúc thư mục:**  
  - Thư mục được tổ chức dưới dạng cây phân cấp, nơi mỗi thư mục chứa danh sách các mục con là tập tin hoặc thư mục khác.
  
- **Các phương pháp lưu trữ thư mục:**  
  - **Danh sách liên kết (linked list):** Dễ cài đặt nhưng truy vấn chậm khi danh sách dài.
  - **B-tree hoặc hash table:** Cải thiện tốc độ tra cứu khi số lượng tập tin lớn.
  
- **Ví dụ minh họa:**  
  - Hệ thống tập tin của Windows sử dụng NTFS, trong đó cấu trúc thư mục được quản lý bằng các chỉ mục (index) giúp truy xuất nhanh chóng tập tin cần tìm.

---

## 14.4 Phương Pháp Cấp Phát Tập Tin (Allocation Methods)

- **Các chiến lược cấp phát không gian cho tập tin:**  
  - **Contiguous Allocation (Phân bổ liên tục):**  
    - Tập tin được lưu trữ trong một khối liên tục trên đĩa.
    - Ưu điểm: Truy cập nhanh, không cần phải tra cứu nhiều phần.
    - Nhược điểm: Dễ xảy ra phân mảnh ngoài (external fragmentation) khi không gian liên tục trở nên khó tìm.
  
  - **Linked Allocation (Phân bổ theo liên kết):**  
    - Tập tin được chia thành các khối rời rạc, mỗi khối chứa thông tin liên kết đến khối tiếp theo.
    - Ưu điểm: Không gây ra phân mảnh ngoài.
    - Nhược điểm: Tra cứu chậm do phải duyệt chuỗi liên kết.
  
  - **Indexed Allocation (Phân bổ theo chỉ mục):**  
    - Sử dụng một bảng chỉ mục để lưu trữ địa chỉ của các khối dữ liệu của tập tin.
    - Ưu điểm: Truy cập ngẫu nhiên dễ dàng, giảm thiểu phân mảnh.
    - Nhược điểm: Bảng chỉ mục có thể lớn đối với tập tin có kích thước lớn.

- **Ví dụ minh họa:**  
  - Hệ thống tập tin FAT của DOS sử dụng một bảng phân bổ tập tin (File Allocation Table) để theo dõi các khối dữ liệu của tập tin, trong khi hệ thống NTFS sử dụng chỉ mục mạnh mẽ để quản lý dữ liệu.

---

## 14.5 Free-Space Management (Quản Lý Vùng Trống)

- **Mục tiêu:**  
  - Quản lý các khối không sử dụng trên đĩa, đảm bảo rằng các tập tin mới có thể được cấp phát không gian một cách hiệu quả.
  
- **Các phương pháp quản lý:**  
  - **Bit Vector (Bitmap):**  
    - Sử dụng mảng bit để đánh dấu các khối đã sử dụng hoặc còn trống.
    - Ưu điểm: Dễ triển khai và nhanh chóng tra cứu.
  
  - **Linked List (Danh sách liên kết):**  
    - Các khối trống được nối với nhau theo chuỗi.
    - Ưu điểm: Tiết kiệm không gian lưu trữ cho việc quản lý.
  
  - **Grouping:**  
    - Gom nhóm các khối trống thành các nhóm để quản lý dễ dàng.
  
- **Ví dụ minh họa:**  
  - Hệ thống tập tin của Unix sử dụng bitmap để theo dõi các block trống trên ổ đĩa, giúp tối ưu việc cấp phát khi tạo mới tập tin.

---

## 14.6 Recovery (Phục Hồi)

- **Mục tiêu:**  
  - Đảm bảo tính nhất quán của hệ thống tập tin sau khi xảy ra lỗi (ví dụ: mất điện đột ngột, lỗi phần cứng).
  
- **Các phương pháp phục hồi:**  
  - **Journaling:**  
    - Ghi lại nhật ký (journal) các thay đổi của hệ thống tập tin trước khi thực hiện, giúp khôi phục lại hệ thống trong trường hợp xảy ra lỗi.
  
  - **Checkpointing:**  
    - Lưu trữ trạng thái của hệ thống tập tin tại những thời điểm nhất định để có thể khôi phục nếu cần.
  
- **Ví dụ minh họa:**  
  - Hệ thống NTFS của Windows sử dụng journaling để theo dõi các thay đổi, giúp giảm thiểu rủi ro mất mát dữ liệu khi hệ thống gặp sự cố.

---

## 14.7 Tóm Lại Chương 14

Chương 14 cung cấp cái nhìn sâu sắc về cách hệ điều hành triển khai hệ thống tập tin, bao gồm:

- **Cấu trúc tập tin:** Cách lưu trữ thông tin và các thuộc tính của tập tin (inode, FCB).
- **Các thao tác tập tin:** Tạo, đọc, ghi, xóa và đổi tên tập tin.
- **Triển khai thư mục:** Cấu trúc cây phân cấp giúp tổ chức tập tin một cách hiệu quả.
- **Phương pháp cấp phát tập tin:** Phân bổ liên tục, theo liên kết, và theo chỉ mục – mỗi phương pháp có ưu, nhược điểm riêng.
- **Quản lý vùng trống:** Sử dụng bitmap, danh sách liên kết hoặc grouping để theo dõi không gian đĩa.
- **Phục hồi:** Các cơ chế journaling và checkpointing giúp đảm bảo dữ liệu không bị mất mát khi xảy ra lỗi.

*Ví dụ minh họa:*  
- Một hệ thống tập tin hiện đại như NTFS sử dụng các kỹ thuật tiên tiến trong cấp phát (indexed allocation) và quản lý vùng trống cùng với journaling để đảm bảo hiệu suất và độ tin cậy cao của dữ liệu lưu trữ.

---
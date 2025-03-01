# Chương 9: Main Memory (Bộ Nhớ Chính)

Chương 9 cung cấp cái nhìn toàn diện về quản lý bộ nhớ chính trong hệ điều hành. Bộ nhớ chính (RAM) là nơi chứa mã lệnh và dữ liệu tạm thời của các tiến trình đang thực thi. Việc quản lý bộ nhớ hiệu quả là rất quan trọng để đảm bảo rằng hệ thống sử dụng tài nguyên một cách tối ưu và đáp ứng nhu cầu của các ứng dụng đa nhiệm.

---

## 9.1 Tổng Quan

- **Vai trò của bộ nhớ chính:**
  - Lưu trữ chương trình và dữ liệu trong quá trình thực thi.
  - Cung cấp không gian làm việc cho các tiến trình.
  
- **Thách thức chính:**
  - Bộ nhớ chính có dung lượng hạn chế so với yêu cầu của các tiến trình.
  - Cần thiết lập các cơ chế quản lý để giải quyết vấn đề phân mảnh (fragmentation) và tối ưu hóa hiệu năng.

---

## 9.2 Phân Bổ Bộ Nhớ Liên Tục (Contiguous Memory Allocation)

- **Khái niệm:**
  - Mỗi tiến trình được cấp một khối bộ nhớ liên tục trong không gian bộ nhớ chính.
  
- **Ưu điểm:**
  - Dễ triển khai và quản lý.
  - Việc truy cập bộ nhớ nhanh và đơn giản vì không cần chuyển đổi ánh xạ giữa các đoạn.

- **Nhược điểm:**
  - Dễ xảy ra phân mảnh bên ngoài (external fragmentation) khi bộ nhớ bị chia nhỏ không liên tục.
  - Khó sử dụng tối đa bộ nhớ khi các tiến trình có kích thước khác nhau và có thời gian sống khác nhau.

- **Ví dụ minh họa:**
  - Một hệ thống đơn giản cấp phát bộ nhớ liên tục cho các tiến trình có thể gặp vấn đề khi tiến trình lớn bị từ chối dù tổng bộ nhớ trống đủ, nhưng không liên tục.

---

## 9.3 Phân Trang (Paging)

- **Khái niệm:**
  - Bộ nhớ chính được chia thành các khối nhỏ cố định kích thước gọi là “pages”.  
  - Không gian địa chỉ của tiến trình (virtual address space) được chia tương tự, và hệ điều hành quản lý ánh xạ giữa các trang ảo và các frame vật lý trong RAM qua bảng trang.

- **Ưu điểm:**
  - Giảm thiểu vấn đề phân mảnh bên ngoài.
  - Cho phép tiến trình sử dụng không gian ảo lớn hơn bộ nhớ vật lý.
  - Hỗ trợ cơ chế bảo vệ bộ nhớ giữa các tiến trình.

- **Nhược điểm:**
  - Quá trình chuyển đổi ánh xạ giữa địa chỉ ảo và vật lý (qua bảng trang) có thể làm tăng overhead.
  - Quản lý bảng trang và xử lý page fault (lỗi trang) đòi hỏi tài nguyên tính toán bổ sung.

- **Ví dụ minh họa:**
  - Trên hệ thống 32-bit, không gian địa chỉ 4GB có thể được chia thành các trang có kích thước 4KB; hệ điều hành sử dụng bảng trang để ánh xạ các trang này sang frame trong RAM.

---

## 9.4 Cấu Trúc Bảng Trang (Page Table)

- **Vai trò của bảng trang:**
  - Lưu trữ thông tin ánh xạ giữa các địa chỉ logic (trong không gian ảo) và địa chỉ vật lý trong bộ nhớ.
  
- **Các dạng bảng trang:**
  - **Bảng trang đơn cấp:** Dễ hiểu nhưng tiêu tốn bộ nhớ nếu không gian ảo lớn.
  - **Bảng trang đa cấp:** Chia bảng trang thành nhiều cấp, giúp tiết kiệm không gian lưu trữ và tăng hiệu quả khi không gian ảo thưa.
  - **Inverted Page Table:** Lưu trữ thông tin ánh xạ theo thứ tự các frame của bộ nhớ thay vì theo tiến trình, giảm kích thước bảng trong các hệ thống lớn.

- **Ví dụ minh họa:**
  - Kiến trúc Intel 32-bit thường sử dụng bảng trang đa cấp để quản lý không gian ảo 4GB, trong khi các hệ thống 64-bit cần giải pháp khác để xử lý không gian ảo cực lớn.

---

## 9.5 Swapping

- **Khái niệm:**
  - Là cơ chế di chuyển toàn bộ tiến trình giữa bộ nhớ chính và bộ nhớ thứ cấp (thường là ổ cứng) khi bộ nhớ chính không đủ để chứa tất cả tiến trình.
  
- **Ưu điểm:**
  - Tăng khả năng chạy đa nhiệm khi nhiều tiến trình cùng yêu cầu bộ nhớ.
  
- **Nhược điểm:**
  - Chi phí I/O cao: Quá trình swapping (hoán đổi) thường chậm hơn rất nhiều so với truy cập bộ nhớ chính.
  - Nếu swapping xảy ra quá thường xuyên (thrashing), hiệu năng của hệ thống sẽ giảm nghiêm trọng.

- **Ví dụ minh họa:**
  - Một hệ thống máy chủ với nhiều tiến trình có thể sử dụng swapping để di chuyển các tiến trình không hoạt động sang ổ cứng nhằm giải phóng bộ nhớ cho các tiến trình cần xử lý khẩn cấp.

---

## 9.6 Ví Dụ Thực Tế và Ứng Dụng

- **Kiến trúc Intel 32-bit và 64-bit:**
  - Hệ thống Intel 32-bit chia không gian địa chỉ thành các trang với kích thước cố định (thường là 4KB).  
  - Hệ thống Intel 64-bit cần áp dụng các kỹ thuật bảng trang đa cấp hoặc các phương pháp ánh xạ khác để quản lý không gian ảo rất lớn (có thể lên đến 2^48 hoặc 2^57 địa chỉ).
  
- **Kiến trúc ARMv8:**
  - ARMv8 cũng áp dụng cơ chế phân trang để quản lý bộ nhớ, hỗ trợ các chế độ bảo vệ bộ nhớ và các tính năng nâng cao khác.
  - Ví dụ: Các thiết bị di động hiện đại sử dụng ARMv8 thường tận dụng cơ chế phân trang để cho phép đa nhiệm và bảo vệ dữ liệu giữa các ứng dụng.

- **Ứng dụng thực tế:**
  - Các hệ điều hành hiện đại như Windows, Linux và macOS đều sử dụng phân trang và swapping để tối ưu hóa việc sử dụng bộ nhớ, cung cấp không gian ảo cho tiến trình và bảo vệ sự an toàn của dữ liệu.

---

## 9.7 Tóm Lại Chương 9

Chương 9 trình bày các khái niệm và kỹ thuật quản lý bộ nhớ chính trong hệ điều hành, bao gồm:

- **Phân bổ bộ nhớ liên tục:** Dễ quản lý nhưng gặp vấn đề phân mảnh.
- **Phân trang:** Giúp giải quyết vấn đề phân mảnh, tạo không gian ảo cho tiến trình và bảo vệ bộ nhớ.
- **Bảng trang:** Lưu trữ ánh xạ giữa địa chỉ ảo và vật lý; có nhiều cách tổ chức (đơn cấp, đa cấp, inverted).
- **Swapping:** Di chuyển tiến trình giữa bộ nhớ chính và bộ nhớ thứ cấp nhằm tăng khả năng chạy đa nhiệm, mặc dù có chi phí I/O cao.
- **Ví dụ thực tế:** Áp dụng trong các kiến trúc như Intel 32/64-bit và ARMv8, giúp các hệ điều hành hiện đại quản lý hiệu quả bộ nhớ và đảm bảo hiệu năng hệ thống.

*Ví dụ minh họa:*  
- Một máy tính cá nhân sử dụng phân trang để cho phép các ứng dụng có không gian ảo lớn hơn bộ nhớ vật lý, kết hợp với cơ chế swapping để chuyển các tiến trình ít hoạt động sang ổ cứng, từ đó tối ưu hóa việc sử dụng RAM cho các tác vụ cần tốc độ xử lý cao.

---
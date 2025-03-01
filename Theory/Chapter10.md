# Chương 10: Virtual Memory (Bộ nhớ ảo)

Bộ nhớ ảo là một kỹ thuật quan trọng trong hệ điều hành cho phép mỗi tiến trình có không gian địa chỉ riêng, độc lập với bộ nhớ vật lý thật, giúp tăng khả năng đa nhiệm, bảo vệ bộ nhớ và tối ưu hóa sử dụng tài nguyên.

---

## 10.1 Tổng Quan về Bộ Nhớ Ảo

- **Định nghĩa:**  
  - Bộ nhớ ảo là một lớp trừu tượng cho phép tiến trình có không gian địa chỉ ảo lớn hơn dung lượng bộ nhớ vật lý (RAM) thực tế.
  - Nó tạo điều kiện cho việc chia sẻ và bảo vệ bộ nhớ giữa các tiến trình.

- **Lợi ích:**  
  - Cho phép các tiến trình chạy với không gian địa chỉ riêng biệt, tăng tính bảo mật.
  - Tối ưu hóa sử dụng bộ nhớ thông qua việc nạp trang theo yêu cầu (demand paging).
  - Hỗ trợ các cơ chế như copy-on-write để tiết kiệm tài nguyên khi tiến trình sao chép dữ liệu.

---

## 10.2 Demand Paging và Page Fault

- **Demand Paging:**  
  - Chỉ nạp vào bộ nhớ các trang (pages) mà tiến trình thực sự cần trong quá trình thực thi.
  - Khi một tiến trình truy cập trang chưa được nạp vào RAM, xảy ra một lỗi trang (page fault).

- **Page Fault:**  
  - Xảy ra khi bộ xử lý yêu cầu một trang không có trong bộ nhớ chính.
  - Hệ điều hành sẽ tải trang đó từ bộ nhớ thứ cấp (ổ cứng) vào một frame trống trong RAM.
  - Quá trình xử lý page fault gây ra overhead, nhưng giúp tối ưu hóa việc sử dụng bộ nhớ bằng cách chỉ nạp dữ liệu cần thiết.

- **Ví dụ minh họa:**  
  - Khi một ứng dụng lớn khởi động, không phải toàn bộ chương trình được nạp vào RAM ngay lập tức; thay vào đó, các trang dữ liệu và mã lệnh được nạp theo nhu cầu khi ứng dụng truy cập vào chúng.

---

## 10.3 Copy-on-Write (COW)

- **Khái niệm:**  
  - Cơ chế cho phép các tiến trình chia sẻ bộ nhớ chung cho đến khi có sự thay đổi dữ liệu.
  - Khi một tiến trình cố gắng ghi vào vùng nhớ chia sẻ, hệ thống sẽ tạo ra một bản sao riêng biệt cho tiến trình đó.

- **Lợi ích:**  
  - Tiết kiệm bộ nhớ vì không cần tạo bản sao ngay lập tức.
  - Giảm thiểu chi phí sao chép dữ liệu khi tiến trình chỉ đọc dữ liệu.

- **Ví dụ minh họa:**  
  - Khi tiến trình cha thực hiện fork() để tạo tiến trình con, bộ nhớ của tiến trình cha có thể được chia sẻ với tiến trình con cho đến khi một trong hai tiến trình thay đổi nội dung vùng nhớ đó.

---

## 10.4 Thuật Toán Thay Thế Trang (Page Replacement Algorithms)

- **Mục tiêu:**  
  - Khi bộ nhớ vật lý đầy, hệ điều hành cần chọn trang nào sẽ bị loại bỏ để nạp trang mới vào RAM.

- **Các thuật toán thay thế trang phổ biến:**

  - **FIFO (First-In, First-Out):**  
    - Loại bỏ trang được nạp vào bộ nhớ trước nhất.
    - Ưu điểm: Đơn giản, dễ triển khai.
    - Nhược điểm: Không tối ưu hiệu năng vì có thể loại bỏ các trang thường xuyên được sử dụng.

  - **Optimal (OPT):**  
    - Loại bỏ trang mà trong tương lai sẽ không được sử dụng trong thời gian dài nhất.
    - Ưu điểm: Hiệu năng tối ưu.
    - Nhược điểm: Yêu cầu thông tin về tương lai, không thể triển khai trong thực tế.

  - **LRU (Least Recently Used):**  
    - Loại bỏ trang mà ít được sử dụng gần đây nhất.
    - Ưu điểm: Phản ánh tốt thói quen sử dụng của tiến trình.
    - Nhược điểm: Chi phí theo dõi thời gian truy cập của các trang có thể cao.

  - **Clock (Second-Chance):**  
    - Là biến thể của FIFO kết hợp với cơ chế “second chance” cho các trang đã được truy cập gần đây.
    - Ưu điểm: Cân bằng giữa hiệu năng và độ phức tạp.
    
- **Ví dụ minh họa:**  
  - Trong một hệ thống chạy nhiều ứng dụng, thuật toán LRU có thể giúp giảm thiểu số lần xảy ra page fault bằng cách giữ lại các trang thường xuyên được sử dụng.

---

## 10.5 Phân Bổ Frame (Allocation of Frames)

- **Quá trình cấp phát frame:**  
  - Khi một page fault xảy ra, hệ điều hành cần tìm một frame trống trong bộ nhớ vật lý.
  - Nếu không có frame trống, hệ điều hành sẽ sử dụng thuật toán thay thế trang để chọn frame cần loại bỏ.
  
- **Yếu tố ảnh hưởng:**  
  - Số lượng frame được cấp cho mỗi tiến trình.
  - Chính sách phân bổ có thể dựa trên kích thước tiến trình, mức độ ưu tiên hoặc tình trạng sử dụng bộ nhớ hiện tại.

- **Ví dụ minh họa:**  
  - Một tiến trình lớn có thể được cấp nhiều frame hơn so với tiến trình nhỏ để đảm bảo hiệu năng, nhưng nếu phân bổ không hợp lý, có thể dẫn đến thrashing.

---

## 10.6 Thrashing

- **Khái niệm:**  
  - Thrashing xảy ra khi hệ thống dành quá nhiều thời gian để xử lý page fault và chuyển đổi trang thay vì thực thi tiến trình.
  - Là hiện tượng khi bộ nhớ vật lý không đủ để chứa hầu hết các trang cần thiết, dẫn đến hoạt động swapping liên tục.

- **Nguyên nhân và hậu quả:**  
  - Nguyên nhân: Quá nhiều tiến trình chạy đồng thời hoặc phân bổ bộ nhớ không hợp lý.
  - Hậu quả: Hiệu năng hệ thống giảm sút nghiêm trọng do CPU liên tục xử lý page fault.
  
- **Giải pháp:**  
  - Giới hạn số lượng tiến trình chạy cùng lúc.
  - Điều chỉnh chính sách phân bổ bộ nhớ hoặc tối ưu hóa thuật toán thay thế trang.

- **Ví dụ minh họa:**  
  - Trên một máy chủ với quá nhiều tiến trình nặng về sử dụng bộ nhớ, thrashing có thể xảy ra khiến hệ thống trở nên chậm chạp và phản hồi kém.

---

## 10.7 Memory Compression và Allocating Kernel Memory

- **Memory Compression:**  
  - Một số hệ điều hành sử dụng nén bộ nhớ để giảm dung lượng dữ liệu cần lưu trữ trong RAM, từ đó giảm tần suất xảy ra page fault.
  
- **Allocating Kernel Memory:**  
  - Kernel có những yêu cầu đặc biệt khi cấp phát bộ nhớ, vì nó cần đảm bảo an toàn, bảo mật và hiệu năng.
  - Các chiến lược cấp phát kernel memory thường tách biệt với bộ nhớ của các tiến trình người dùng để đảm bảo tính ổn định của hệ thống.

---

## 10.8 Tóm Lại Chương 10

Chương 10 trình bày các khái niệm và kỹ thuật quan trọng của bộ nhớ ảo trong hệ điều hành, bao gồm:

- **Bộ nhớ ảo:** Cung cấp không gian địa chỉ riêng cho tiến trình, tách biệt không gian logic và vật lý.
- **Demand Paging và Page Fault:** Nạp trang theo yêu cầu khi tiến trình truy cập vào dữ liệu chưa có trong RAM.
- **Copy-on-Write:** Tiết kiệm bộ nhớ bằng cách chia sẻ dữ liệu giữa các tiến trình cho đến khi có sự thay đổi.
- **Thuật toán thay thế trang:** Các thuật toán như FIFO, LRU, OPT, và Clock giúp quyết định trang nào sẽ bị loại bỏ khi bộ nhớ đầy.
- **Phân bổ frame:** Quản lý việc cấp phát frame cho tiến trình dựa trên tình trạng sử dụng bộ nhớ.
- **Thrashing:** Hiện tượng hệ thống dành quá nhiều thời gian xử lý page fault do thiếu bộ nhớ vật lý, cần có các biện pháp điều chỉnh để khắc phục.
- **Memory Compression và kernel memory:** Những kỹ thuật nâng cao hỗ trợ tối ưu hóa việc sử dụng bộ nhớ và bảo vệ kernel.

*Ví dụ minh họa:*  
- Một máy tính cá nhân sử dụng bộ nhớ ảo cho phép các ứng dụng chạy với không gian địa chỉ ảo lớn hơn bộ nhớ vật lý thực tế, kết hợp với thuật toán LRU để giảm thiểu page fault. Đồng thời, nếu hệ thống quá tải, thrashing có thể xảy ra, đòi hỏi các biện pháp như giới hạn số lượng tiến trình chạy cùng lúc hoặc sử dụng memory compression để cải thiện hiệu năng.

---
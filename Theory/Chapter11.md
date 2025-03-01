# Chương 11: Mass-Storage Structure (Cấu Trúc Lưu Trữ Khối)

Chương 11 tập trung vào cách hệ điều hành quản lý và tối ưu hóa các thiết bị lưu trữ khối – những thiết bị này thường được sử dụng để lưu trữ dữ liệu lâu dài, hỗ trợ không gian lưu trữ lớn mà bộ nhớ chính (RAM) không thể đáp ứng.

---

## 11.1 Tổng Quan về Cấu Trúc Lưu Trữ Khối

- **Định nghĩa & Vai trò:**  
  - Lưu trữ khối (mass storage) là bộ phận lưu trữ dữ liệu lâu dài, chẳng hạn như ổ cứng (HDD), ổ đĩa thể rắn (SSD), băng từ, đĩa quang,…  
  - Nó bổ sung cho bộ nhớ chính, giúp lưu trữ dữ liệu và chương trình khi hệ thống tắt nguồn.

- **Chức năng:**  
  - Cung cấp không gian lưu trữ lớn với chi phí thấp.
  - Đáp ứng yêu cầu lưu trữ liên tục cho các ứng dụng và hệ thống tập tin.

---

## 11.2 HDD Scheduling (Lập Lịch Ổ Cứng)

- **Mục tiêu của lập lịch HDD:**  
  - Tối ưu hóa thời gian truy cập (seek time, latency) bằng cách sắp xếp thứ tự các yêu cầu đọc/ghi.
  - Giảm độ trễ và tăng thông lượng của ổ cứng.

- **Các thuật toán phổ biến:**  
  - **FCFS (First-Come, First-Served):** Xử lý các yêu cầu theo thứ tự đến.
  - **SCAN (Elevator Algorithm):** Ổ cứng di chuyển theo một hướng, xử lý tất cả các yêu cầu trên đường đi rồi quay lại.
  - **C-SCAN (Circular SCAN):** Tương tự SCAN nhưng sau khi đạt đến cuối dãy, ổ cứng sẽ quay lại đầu dãy một cách liên tục.
  
- **Ví dụ minh họa:**  
  - Trong một hệ thống máy chủ, khi có nhiều yêu cầu truy xuất dữ liệu từ ổ cứng, thuật toán SCAN có thể giảm thiểu thời gian di chuyển đầu đọc giữa các track, từ đó tăng hiệu năng I/O.

---

## 11.3 NVM Scheduling (Lập Lịch Bộ Nhớ Không Bay Hơi)

- **Đặc điểm của NVM:**  
  - Các thiết bị NVM (ví dụ: SSD, flash memory) có tốc độ truy cập nhanh hơn ổ cứng cơ học và không có thành phần cơ học.
  
- **Lập lịch NVM:**  
  - Dù không bị hạn chế bởi thời gian di chuyển đầu đọc như HDD, NVM cũng cần được quản lý hợp lý để tối ưu hóa số lượng thao tác ghi/đọc và kéo dài tuổi thọ của thiết bị (do giới hạn số lần ghi).
  - Một số chiến lược tập trung vào **wear leveling** (phân bổ đều việc ghi) và tối ưu hóa truy cập song song.

- **Ví dụ minh họa:**  
  - Một hệ thống lưu trữ sử dụng SSD sẽ ưu tiên các yêu cầu truy xuất dữ liệu theo cách phân bổ đều các thao tác ghi, giúp tránh việc một vùng bộ nhớ bị hao mòn quá nhanh.

---

## 11.4 Error Detection and Correction (Phát Hiện và Sửa Lỗi)

- **Mục tiêu:**  
  - Đảm bảo tính toàn vẹn của dữ liệu khi lưu trữ và truyền tải.
  
- **Các kỹ thuật:**  
  - **Parity Check:** Kiểm tra số bit 1 để phát hiện lỗi đơn giản.
  - **ECC (Error-Correcting Code):** Sử dụng mã ECC để không chỉ phát hiện mà còn sửa lỗi nếu dữ liệu bị lỗi.
  - **Checksums và CRC (Cyclic Redundancy Check):** Tính toán giá trị kiểm tra của dữ liệu nhằm phát hiện sự thay đổi không mong muốn.

- **Ví dụ minh họa:**  
  - Ổ cứng và bộ nhớ RAM thường được trang bị ECC để tự động phát hiện và sửa các lỗi bit đơn, đảm bảo dữ liệu được lưu trữ an toàn và đáng tin cậy.

---

## 11.5 Storage Device Management (Quản Lý Thiết Bị Lưu Trữ)

- **Vai trò của quản lý thiết bị:**  
  - Hệ điều hành sử dụng driver để giao tiếp với thiết bị lưu trữ, chuyển đổi các yêu cầu I/O từ hệ thống thành các lệnh phù hợp với thiết bị.
  
- **Các nhiệm vụ quản lý:**  
  - Theo dõi trạng thái và hiệu suất của thiết bị.
  - Quản lý hàng đợi yêu cầu I/O và xử lý lỗi trong quá trình truyền dữ liệu.

- **Ví dụ minh họa:**  
  - Trong Linux, driver thiết bị sẽ xử lý các yêu cầu đọc/ghi đến ổ cứng và sử dụng các thuật toán lập lịch I/O để tối ưu hóa hiệu suất truy xuất.

---

## 11.6 Swap-Space Management (Quản Lý Không Gian Swap)

- **Khái niệm:**  
  - Swap space là vùng lưu trữ trên ổ cứng được sử dụng như một phần mở rộng của bộ nhớ chính khi RAM không đủ.
  
- **Chức năng:**  
  - Di chuyển một số tiến trình hoặc trang bộ nhớ không hoạt động khỏi RAM sang swap, từ đó giải phóng bộ nhớ cho các tiến trình đang cần tài nguyên.
  
- **Nhược điểm:**  
  - Truy cập swap chậm hơn nhiều so với RAM, do đó việc quá phụ thuộc vào swap có thể gây ra hiệu suất kém (thrashing).
  
- **Ví dụ minh họa:**  
  - Trên máy tính cá nhân, khi chạy quá nhiều ứng dụng cùng lúc, một số trang bộ nhớ không hoạt động sẽ được chuyển sang swap để cho phép các ứng dụng hoạt động mượt mà hơn.

---

## 11.7 Storage Attachment (Kết Nối Thiết Bị Lưu Trữ)

- **Khái niệm:**  
  - Kết nối các thiết bị lưu trữ với hệ thống thông qua các giao tiếp như SATA, SCSI, NVMe, USB,…  
  - Mỗi loại giao tiếp có đặc điểm về tốc độ, băng thông và độ tin cậy khác nhau.

- **Ý nghĩa:**  
  - Cách thức kết nối ảnh hưởng đến hiệu suất của các hoạt động I/O và khả năng mở rộng của hệ thống.
  
- **Ví dụ minh họa:**  
  - Ổ cứng SSD sử dụng giao tiếp NVMe qua bus PCIe có tốc độ truy cập rất cao, phù hợp với các ứng dụng yêu cầu tốc độ I/O mạnh mẽ như máy chủ cơ sở dữ liệu.

---

## 11.8 RAID Structure (Cấu Trúc RAID)

- **Định nghĩa RAID:**  
  - RAID (Redundant Array of Independent Disks) là một công nghệ kết hợp nhiều ổ đĩa thành một hệ thống lưu trữ duy nhất nhằm tăng hiệu năng, dung lượng lưu trữ và độ tin cậy.
  
- **Các cấp độ RAID phổ biến:**  
  - **RAID 0:** Chia dữ liệu đồng đều cho các ổ đĩa để tăng tốc độ truy xuất nhưng không có dự phòng lỗi.
  - **RAID 1:** Sao chép dữ liệu sang hai hoặc nhiều ổ đĩa (mirroring) để đảm bảo an toàn dữ liệu.
  - **RAID 5:** Kết hợp giữa chia sẻ dữ liệu và sử dụng parity để cung cấp dự phòng lỗi với hiệu năng tốt.
  - **RAID 6:** Tương tự RAID 5 nhưng sử dụng hai lớp parity, cho phép chịu được lỗi của hai ổ đĩa.
  - **RAID 10 (hoặc RAID 1+0):** Kết hợp mirroring và striping, cung cấp hiệu năng cao và khả năng dự phòng tốt.

- **Ví dụ minh họa:**  
  - Một trung tâm dữ liệu thường sử dụng RAID 5 hoặc RAID 6 để cân bằng giữa hiệu năng, dung lượng lưu trữ và khả năng chịu lỗi của hệ thống.

---

## 11.9 Tóm Lại Chương 11

Chương 11 cung cấp cái nhìn tổng quát về các thành phần và kỹ thuật quản lý lưu trữ khối trong hệ điều hành, bao gồm:

- **Overview:** Vai trò của lưu trữ khối trong việc lưu trữ dữ liệu lâu dài và hỗ trợ hệ thống tập tin.
- **HDD Scheduling:** Các thuật toán sắp xếp yêu cầu I/O trên ổ cứng để tối ưu hóa thời gian truy cập.
- **NVM Scheduling:** Các chiến lược quản lý thiết bị NVM như SSD, tối ưu hóa số lần ghi và truy cập.
- **Error Detection and Correction:** Các phương pháp ECC, parity, checksum để đảm bảo dữ liệu được lưu trữ chính xác.
- **Storage Device Management:** Quản lý thiết bị lưu trữ thông qua driver và hàng đợi I/O.
- **Swap-Space Management:** Quản lý vùng swap để mở rộng bộ nhớ ảo, tránh thrashing.
- **Storage Attachment:** Các giao diện kết nối thiết bị lưu trữ và ảnh hưởng của chúng đến hiệu suất.
- **RAID Structure:** Công nghệ kết hợp nhiều ổ đĩa nhằm tăng hiệu năng và độ tin cậy của hệ thống lưu trữ.

*Ví dụ minh họa:*  
- Một máy chủ cơ sở dữ liệu có thể sử dụng ổ cứng SSD kết nối qua NVMe để đạt tốc độ truy cập cực cao, đồng thời áp dụng RAID 6 để đảm bảo dữ liệu luôn được dự phòng trong trường hợp một hoặc hai ổ đĩa gặp sự cố. Hệ điều hành sẽ sử dụng các thuật toán lập lịch I/O phù hợp để xử lý các yêu cầu đọc/ghi, quản lý swap-space khi cần thiết, và đảm bảo rằng các lỗi phần cứng được phát hiện và sửa chữa thông qua các cơ chế ECC.

---
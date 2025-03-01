# Chương 16: Security (Bảo Mật)

Chương 16 trình bày tổng quan về vấn đề bảo mật trong hệ điều hành – một lĩnh vực quan trọng nhằm bảo vệ dữ liệu, tài nguyên và các dịch vụ của hệ thống khỏi các mối đe dọa từ bên ngoài cũng như từ các tiến trình không đáng tin cậy.

---

## 16.1 Vấn Đề Bảo Mật (The Security Problem)

- **Mục tiêu bảo mật:**  
  - Bảo vệ tính toàn vẹn, tính bảo mật và tính khả dụng của dữ liệu và tài nguyên hệ thống.
  - Ngăn chặn truy cập trái phép, phá hoại dữ liệu, và các cuộc tấn công từ virus, malware hay hacker.

- **Các mối đe dọa:**  
  - **Lỗ hổng phần mềm:** Lỗi trong mã nguồn hệ điều hành hoặc ứng dụng.
  - **Cuộc tấn công từ bên ngoài:** Các tấn công từ mạng (ví dụ: tấn công từ chối dịch vụ – DoS/DDoS), tấn công xâm nhập.
  - **Cuộc tấn công nội bộ:** Người dùng trái phép hoặc các tiến trình có ý đồ xấu bên trong hệ thống.

---

## 16.2 Các Mối Đe Dọa Chương Trình và Mạng (Program and Network Threats)

- **Mối đe dọa từ chương trình:**  
  - **Buffer overflow:** Tấn công bằng cách ghi đè bộ nhớ ngoài phạm vi dự kiến.
  - **Code injection:** Chèn mã độc vào chương trình thông qua các lỗ hổng bảo mật.
  - **Privilege escalation:** Lợi dụng lỗi để tăng quyền truy cập trong hệ thống.

- **Mối đe dọa từ mạng:**  
  - **Man-in-the-Middle (MitM):** Kẻ tấn công chặn và thay đổi thông tin truyền qua mạng.
  - **Sniffing:** Thu thập dữ liệu không được mã hóa.
  - **DoS/DDoS:** Tấn công làm gián đoạn dịch vụ bằng cách làm quá tải hệ thống.

---

## 16.3 Cryptography as a Security Tool

- **Vai trò của mã hóa:**  
  - Bảo vệ dữ liệu bằng cách chuyển đổi thông tin thành dạng không thể đọc được nếu không có khóa giải mã.
  - Đảm bảo tính toàn vẹn (integrity), bảo mật (confidentiality) và xác thực (authentication).

- **Các thuật toán mã hóa phổ biến:**  
  - **Mã hóa đối xứng:** AES, DES – sử dụng cùng một khóa cho việc mã hóa và giải mã.
  - **Mã hóa bất đối xứng:** RSA, ECC – sử dụng cặp khóa (khóa công khai và khóa riêng tư).
  - **Hàm băm (Hash functions):** MD5, SHA – dùng để tạo ra giá trị băm duy nhất đại diện cho dữ liệu.

- **Ví dụ minh họa:**  
  - Trong giao tiếp qua Internet, HTTPS sử dụng các thuật toán mã hóa để bảo vệ dữ liệu người dùng khỏi việc bị nghe lén.

---

## 16.4 User Authentication (Xác Thực Người Dùng)

- **Các phương thức xác thực:**  
  - **Mật khẩu:** Phương pháp cơ bản, nhưng dễ bị tấn công nếu không được bảo vệ đúng cách.
  - **Token và OTP (One-Time Password):** Tăng cường bảo mật bằng cách sử dụng mã dùng một lần.
  - **Sinh trắc học:** Nhận dạng qua dấu vân tay, khuôn mặt, hay quét võng mạc.
  - **Xác thực đa yếu tố (Multi-Factor Authentication):** Kết hợp nhiều phương pháp để tăng cường độ an toàn.

- **Quá trình xác thực:**  
  - Người dùng cung cấp thông tin (mật khẩu, token,…).
  - Hệ thống so sánh với thông tin đã lưu trữ và cấp quyền truy cập nếu khớp.

- **Ví dụ minh họa:**  
  - Các dịch vụ ngân hàng trực tuyến thường yêu cầu xác thực đa yếu tố để bảo vệ tài khoản người dùng.

---

## 16.5 Implementing Security Defenses (Triển Khai Các Biện Pháp Phòng Thủ Bảo Mật)

- **Các biện pháp phòng thủ:**  
  - **Least Privilege (Nguyên tắc tối thiểu):** Cấp quyền truy cập chỉ đủ để thực hiện nhiệm vụ, giảm nguy cơ lạm dụng.
  - **Sandboxing:** Cô lập các ứng dụng và tiến trình để hạn chế ảnh hưởng nếu bị tấn công.
  - **Access Control Mechanisms:** Sử dụng ACL, role-based access control (RBAC) để quản lý quyền truy cập tài nguyên.
  - **Security Patches and Updates:** Cập nhật hệ thống thường xuyên để vá các lỗ hổng bảo mật.

- **Ví dụ minh họa:**  
  - Hệ điều hành Windows và Linux đều có các chính sách kiểm soát truy cập và hệ thống cập nhật tự động giúp ngăn ngừa các cuộc tấn công dựa trên các lỗ hổng đã biết.

---

## 16.6 An Example: Windows 10 Security

- **Triển khai bảo mật của Windows 10:**  
  - Windows 10 áp dụng nhiều lớp bảo mật, bao gồm:
    - **Windows Defender:** Phần mềm chống virus và bảo mật tích hợp.
    - **User Account Control (UAC):** Giới hạn quyền truy cập của người dùng.
    - **BitLocker:** Mã hóa ổ đĩa giúp bảo vệ dữ liệu nếu máy tính bị đánh cắp.
    - **Windows Hello:** Xác thực sinh trắc học để tăng cường bảo mật đăng nhập.
  - Các công nghệ này giúp Windows 10 đảm bảo tính toàn vẹn, bảo mật và khả năng chịu tấn công trong môi trường ngày càng phức tạp.

---

## 16.7 Tóm Lại Chương 16

Chương 16 cung cấp cái nhìn toàn diện về bảo mật trong hệ điều hành, bao gồm:

- **Các vấn đề bảo mật cơ bản:** Các mối đe dọa từ chương trình và mạng, lỗ hổng và cách tấn công.
- **Vai trò của mã hóa:** Sử dụng các thuật toán mã hóa và hàm băm để bảo vệ dữ liệu.
- **Xác thực người dùng:** Các phương thức từ mật khẩu đến xác thực đa yếu tố nhằm đảm bảo chỉ người dùng hợp lệ được truy cập.
- **Các biện pháp phòng thủ bảo mật:** Triển khai các nguyên tắc như least privilege, sandboxing và cập nhật bảo mật để giảm thiểu rủi ro.
- **Ví dụ cụ thể:** Windows 10 áp dụng nhiều công nghệ bảo mật như Windows Defender, UAC, BitLocker và Windows Hello nhằm bảo vệ người dùng và dữ liệu hệ thống.

*Ví dụ minh họa:*  
- Một hệ thống giao dịch trực tuyến sử dụng HTTPS với mã hóa AES để bảo vệ dữ liệu người dùng, kết hợp với xác thực đa yếu tố để ngăn chặn truy cập trái phép, đảm bảo rằng ngay cả khi mật khẩu bị đánh cắp, kẻ tấn công vẫn không thể truy cập vào tài khoản mà không có OTP hoặc yếu tố sinh trắc học.

---
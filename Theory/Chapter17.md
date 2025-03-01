# Chương 17: Protection (Phòng Ngừa và Kiểm Soát Truy Cập)

Chương 17 trình bày các cơ chế bảo vệ trong hệ điều hành, nhằm kiểm soát quyền truy cập vào tài nguyên và đảm bảo rằng các tiến trình chỉ có thể thực hiện các hành động phù hợp với mức độ quyền hạn của chúng.

---

## 17.1 Mục Tiêu của Bảo Vệ (Goals of Protection)

- **Bảo vệ dữ liệu và tài nguyên:**  
  - Đảm bảo rằng dữ liệu không bị truy cập, sửa đổi hay phá hoại trái phép.
- **Tính toàn vẹn và tính sẵn sàng:**  
  - Đảm bảo rằng chỉ có các tiến trình được ủy quyền mới có thể thao tác với tài nguyên, từ đó duy trì tính nhất quán của hệ thống.
- **Ngăn chặn sự lạm dụng quyền:**  
  - Hạn chế khả năng của tiến trình (và người dùng) khi thực hiện các hành động có thể ảnh hưởng tiêu cực đến hệ thống.

---

## 17.2 Nguyên Tắc Bảo Vệ (Principles of Protection)

- **Least Privilege (Quyền tối thiểu):**  
  - Mỗi tiến trình chỉ được cấp quyền cần thiết để thực hiện nhiệm vụ của nó.
- **Complete Mediation:**  
  - Mọi truy cập tài nguyên đều phải được kiểm tra quyền truy cập mỗi khi được yêu cầu.
- **Separation of Duties (Phân chia nhiệm vụ):**  
  - Tách biệt các chức năng quan trọng để giảm nguy cơ lạm dụng quyền.
- **Fail-Safe Defaults:**  
  - Mặc định từ chối truy cập trừ khi quyền truy cập được cho phép rõ ràng.

---

## 17.3 Protection Rings (Vòng Bảo Vệ)

- **Khái niệm:**  
  - Hệ thống vòng bảo vệ phân cấp, trong đó các mức (ring) càng bên trong thì quyền truy cập càng cao và bảo mật càng nghiêm ngặt.
- **Ví dụ:**  
  - Ring 0 thường dành cho kernel (hệ điều hành), Ring 3 dành cho các ứng dụng người dùng.
- **Mục tiêu:**  
  - Ngăn chặn các tiến trình người dùng tác động trực tiếp lên phần cứng hoặc các chức năng bảo mật của hệ thống.

---

## 17.4 Domain of Protection và Access Matrix

- **Domain of Protection:**  
  - Một tập hợp các đối tượng (object) và các chủ thể (subject) cùng tồn tại trong hệ thống, với các quyền truy cập được xác định.
- **Access Matrix:**  
  - Một mô hình trừu tượng biểu diễn quyền truy cập, trong đó hàng biểu diễn các chủ thể và cột biểu diễn các đối tượng, mỗi ô chứa các quyền (read, write, execute,…).
- **Triển khai:**  
  - Access Matrix có thể được triển khai qua các danh sách kiểm soát truy cập (ACLs) hoặc danh sách khả năng (capabilities).

---

## 17.5 Revocation và Các Phương Pháp Kiểm Soát Khác

- **Revocation (Thu hồi quyền truy cập):**  
  - Cơ chế để thu hồi quyền truy cập đã cấp khi không còn phù hợp.
- **Role-Based Access Control (RBAC):**  
  - Phân quyền dựa trên vai trò của người dùng trong tổ chức, thay vì gán quyền trực tiếp cho từng cá nhân.
- **Mandatory Access Control (MAC):**  
  - Hệ thống bắt buộc, trong đó quyền truy cập được quy định bởi các chính sách bảo mật trung tâm, không thể bị thay đổi bởi người dùng.
- **Capability-Based Systems:**  
  - Mỗi chủ thể được cấp một "khả năng" (capability) – một token chứa quyền truy cập đến các đối tượng cụ thể.
- **Language-Based Protection:**  
  - Sử dụng các ràng buộc của ngôn ngữ lập trình để kiểm soát truy cập tài nguyên, hạn chế lỗi do lập trình.

---

## 17.6 Ví Dụ Minh Họa

- **Ví dụ 1 – RBAC:**  
  - Trong một hệ thống doanh nghiệp, nhân viên thuộc bộ phận kế toán có quyền truy cập vào các tập tin tài chính, nhưng không được truy cập vào dữ liệu kỹ thuật.
- **Ví dụ 2 – MAC:**  
  - Một hệ thống quân sự sử dụng MAC để đảm bảo rằng các thông tin mật chỉ có thể được truy cập bởi các cấp có thẩm quyền theo quy định bảo mật nghiêm ngặt.
- **Ví dụ 3 – Capability-Based Systems:**  
  - Trong một số hệ thống phân tán, mỗi tiến trình nhận được một capability chứa thông tin xác thực và quyền truy cập, giúp hạn chế việc truy cập trái phép vào tài nguyên chia sẻ.

---

## 17.7 Tóm Lại Chương 17

Chương 17 cung cấp các khái niệm và phương pháp bảo vệ hệ thống, bao gồm:

- **Mục tiêu bảo vệ:** Đảm bảo tính toàn vẹn, bảo mật và sẵn có của tài nguyên.
- **Nguyên tắc bảo vệ:** Least privilege, complete mediation, separation of duties, và fail-safe defaults.
- **Protection Rings:** Phân cấp quyền truy cập qua các vòng bảo vệ, từ kernel (Ring 0) đến ứng dụng người dùng (Ring 3).
- **Access Matrix:** Mô hình trừu tượng giúp biểu diễn và quản lý quyền truy cập của các chủ thể đến đối tượng.
- **Các phương pháp kiểm soát truy cập:** RBAC, MAC, capability-based systems và language-based protection giúp triển khai các chính sách bảo mật khác nhau.
- **Revocation:** Cơ chế thu hồi quyền truy cập khi cần thiết.
- **Ví dụ minh họa:** Các hệ thống doanh nghiệp, quân sự và phân tán đều áp dụng các mô hình kiểm soát truy cập để bảo vệ dữ liệu và tài nguyên khỏi truy cập trái phép.

*Ví dụ minh họa:*  
- Một hệ thống ngân hàng sử dụng RBAC để đảm bảo rằng chỉ các nhân viên thuộc bộ phận được ủy quyền mới có thể truy cập dữ liệu tài chính, đồng thời sử dụng MAC để đảm bảo rằng các thông tin nhạy cảm được bảo vệ nghiêm ngặt. Capability-based systems có thể được áp dụng trong các ứng dụng đám mây để quản lý quyền truy cập tài nguyên một cách linh hoạt và an toàn.

---
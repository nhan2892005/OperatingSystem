# Chương 6: Synchronization Tools (Công Cụ Đồng Bộ Hóa)

Trong môi trường đa nhiệm, khi nhiều tiến trình hoặc luồng cùng truy cập vào tài nguyên chia sẻ, việc đồng bộ hóa trở nên vô cùng cần thiết. Chương 6 của cuốn *Operating System Concepts* tập trung vào các cơ chế và công cụ giúp đảm bảo rằng các tiến trình không xung đột khi truy cập tài nguyên chung.

---

## 6.1 Tổng Quan và Vấn Đề Đồng Bộ Hóa

- **Vấn đề vùng tới hạn (Critical Section Problem):**  
  - Là khu vực trong mã nguồn nơi các tiến trình truy cập tài nguyên chung (ví dụ: biến, dữ liệu, thiết bị).  
  - **Yêu cầu giải pháp đồng bộ:**  
    1. **Mutual Exclusion:** Chỉ có một tiến trình được truy cập vùng tới hạn tại một thời điểm.  
    2. **Progress:** Nếu không có tiến trình nào trong vùng tới hạn, tiến trình chờ đợi phải có cơ hội truy cập.  
    3. **Bounded Waiting:** Không tiến trình nào bị chờ đợi vô hạn, tức số lần cho phép tiến trình khác vào vùng tới hạn phải bị giới hạn.

- **Mục tiêu:**  
  - Ngăn chặn race condition (tranh chấp dữ liệu) và đảm bảo tính nhất quán của dữ liệu chia sẻ.

---

## 6.2 Giải Pháp Phần Mềm Cơ Bản

### 6.2.1 Peterson's Solution
- **Nguyên tắc:**  
  - Sử dụng các biến cờ (flag) và biến chỉ định (turn) để đảm bảo mutual exclusion cho hai tiến trình.
- **Cách hoạt động:**  
  - Mỗi tiến trình báo hiệu ý định vào vùng tới hạn bằng cách đặt flag.
  - Biến turn được sử dụng để quyết định tiến trình nào sẽ được phép vào vùng tới hạn nếu cả hai cùng báo hiệu.
- **Ưu điểm:**  
  - Giải pháp đơn giản, không yêu cầu hỗ trợ phần cứng.
- **Nhược điểm:**  
  - Chỉ áp dụng cho hai tiến trình, không mở rộng được cho nhiều tiến trình.
- **Ví dụ minh họa:**  
  - Trong một hệ thống với hai tiến trình cần chia sẻ một biến, Peterson's solution sẽ giúp sắp xếp thứ tự truy cập để đảm bảo rằng không có tiến trình nào can thiệp vào quá trình của tiến trình kia.

---

## 6.3 Hỗ Trợ Phần Cứng cho Đồng Bộ Hóa

- **Cơ chế Test-and-Set:**  
  - Một lệnh phần cứng thực hiện việc kiểm tra và đặt giá trị đồng thời, cho phép xây dựng các khóa (locks) đơn giản.
- **Compare-and-Swap (CAS):**  
  - Lệnh so sánh giá trị hiện tại với một giá trị dự kiến, nếu trùng khớp thì thay thế giá trị đó; thường dùng trong xây dựng các cấu trúc dữ liệu không khoá (lock-free).
- **Vô hiệu hóa ngắt (Disabling Interrupts):**  
  - Trong các hệ thống đơn lõi, tạm thời vô hiệu hóa ngắt để đảm bảo không có tiến trình nào có thể phá vỡ quá trình thực thi trong vùng tới hạn.

---

## 6.4 Mutex Locks (Khóa Loại Mutex)

- **Định nghĩa:**  
  - Một mutex là một cơ chế đồng bộ hóa cho phép chỉ một tiến trình hoặc luồng được truy cập vào một đoạn mã hoặc tài nguyên chung tại một thời điểm.
- **Cách hoạt động:**  
  - Khi một tiến trình muốn vào vùng tới hạn, nó phải "lock" mutex. Nếu mutex đang bị khóa, tiến trình phải chờ đợi.
  - Sau khi hoàn thành, tiến trình "unlock" mutex để cho phép tiến trình khác truy cập.
- **Ví dụ minh họa:**  
  - Trong một ứng dụng ngân hàng, khi cập nhật số dư tài khoản, mutex đảm bảo rằng chỉ có một giao dịch có thể cập nhật số dư tại một thời điểm, tránh việc xảy ra lỗi do đồng thời.

---

## 6.5 Semaphores

- **Định nghĩa:**  
  - Semaphore là một biến đếm được sử dụng để điều phối việc truy cập vào tài nguyên chung.
- **Hai loại semaphore chính:**
  - **Binary Semaphore:** Chỉ có hai giá trị (0 và 1), tương tự như mutex.
  - **Counting Semaphore:** Có giá trị đếm từ 0 đến N, dùng để quản lý tài nguyên có số lượng nhiều.
- **Hai thao tác cơ bản:**
  - **Wait (P hoặc down):** Giảm giá trị của semaphore. Nếu giá trị bằng 0, tiến trình sẽ bị chặn cho đến khi semaphore có giá trị lớn hơn 0.
  - **Signal (V hoặc up):** Tăng giá trị của semaphore, đánh thức một tiến trình đang chờ nếu có.
- **Ví dụ minh họa:**  
  - Trong hệ thống in ấn, nếu có 3 máy in và nhiều tiến trình cần in, counting semaphore được khởi tạo với giá trị 3 sẽ cho phép tối đa 3 tiến trình in đồng thời; tiến trình thứ tư phải chờ đợi cho đến khi một máy in trở nên sẵn sàng.

---

## 6.6 Monitors

- **Định nghĩa:**  
  - Monitor là một cấu trúc cấp cao cung cấp một môi trường đồng bộ hóa tự động, tích hợp các biến điều kiện (condition variables) bên trong.
- **Cách hoạt động:**  
  - Chỉ có một tiến trình được phép truy cập vào monitor tại một thời điểm.
  - Các biến điều kiện cho phép tiến trình chờ đợi cho đến khi một điều kiện nhất định được thỏa mãn, và sau đó tiến trình được đánh thức.
- **Ưu điểm:**  
  - Trừu tượng hóa quá trình đồng bộ hóa, giúp lập trình viên dễ dàng sử dụng mà không cần quan tâm đến chi tiết triển khai.
- **Ví dụ minh họa:**  
  - Trong một hệ thống sản xuất-tiêu thụ, monitor có thể được sử dụng để quản lý hàng đợi sản phẩm; tiến trình sản xuất sẽ "signal" khi sản phẩm được thêm vào, trong khi tiến trình tiêu thụ sẽ "wait" cho đến khi có sản phẩm sẵn có.

---

## 6.7 Các Vấn Đề Liên Quan đến Liveness

- **Liveness (Sự sống):**  
  - Đảm bảo rằng các tiến trình không bị kẹt mãi mãi trong quá trình chờ đợi.
- **Deadlock:**  
  - Tình trạng khi các tiến trình chờ lẫn nhau giữ các tài nguyên, dẫn đến việc không tiến trình nào có thể tiếp tục.
- **Starvation (Đói tiến trình):**  
  - Một tiến trình không bao giờ được truy cập vào tài nguyên cần thiết do các tiến trình khác luôn ưu tiên.
- **Các biện pháp khắc phục:**  
  - Sử dụng các thuật toán phòng tránh, tránh hoặc phát hiện và khắc phục deadlock.
  - Áp dụng chính sách đảm bảo bounded waiting (sự chờ đợi bị giới hạn) để tránh starvation.

---

## 6.8 Đánh Giá và Ứng Dụng

- **Ưu điểm của các công cụ đồng bộ hóa:**  
  - Đảm bảo tính nhất quán và an toàn cho dữ liệu khi nhiều tiến trình truy cập tài nguyên chung.
  - Giúp xây dựng các ứng dụng đa nhiệm, đa luồng hiệu quả.
- **Nhược điểm và thách thức:**  
  - Các giải pháp phần mềm như Peterson chỉ hiệu quả trong trường hợp hạn chế (ví dụ, chỉ với hai tiến trình).
  - Cơ chế phần cứng có thể khó tích hợp hoặc không tương thích trên một số kiến trúc.
  - Việc sử dụng sai cách có thể dẫn đến deadlock, starvation, hoặc tăng chi phí chuyển đổi ngữ cảnh.
- **Ví dụ ứng dụng thực tế:**  
  - Hệ thống ngân hàng sử dụng mutex và semaphore để đảm bảo các giao dịch không can thiệp lẫn nhau.
  - Các ứng dụng máy chủ sử dụng monitor để quản lý hàng đợi các yêu cầu đến từ khách hàng, đảm bảo xử lý theo thứ tự và an toàn dữ liệu.

---

## 6.9 Tóm Lại Chương 6

Chương 6 trình bày các công cụ đồng bộ hóa thiết yếu trong hệ điều hành nhằm giải quyết vấn đề vùng tới hạn và đảm bảo sự an toàn khi nhiều tiến trình (hoặc luồng) cùng truy cập tài nguyên chia sẻ. Các nội dung chính bao gồm:

- **Critical Section Problem:** Vấn đề truy cập tài nguyên chung và các yêu cầu của giải pháp.
- **Phần mềm đồng bộ:** Giải pháp như Peterson cho hai tiến trình.
- **Hỗ trợ phần cứng:** Lệnh test-and-set, compare-and-swap, và vô hiệu hóa ngắt.
- **Mutex, Semaphore, và Monitor:** Các cơ chế đồng bộ hóa với ưu, nhược điểm riêng.
- **Liveness Issues:** Deadlock và starvation cùng các biện pháp khắc phục.
- **Ứng dụng thực tế:** Sử dụng các công cụ đồng bộ hóa trong các hệ thống đa nhiệm để đảm bảo tính nhất quán và an toàn dữ liệu.

*Ví dụ minh họa:*  
- Một hệ thống in ấn sử dụng counting semaphore để quản lý số lượng máy in, đảm bảo rằng chỉ có số tiến trình tương ứng mới có thể thực hiện in đồng thời, tránh việc nhiều tiến trình cùng truy cập vào tài nguyên in ấn gây xung đột.

---
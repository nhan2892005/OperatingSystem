## Câu 1: Địa chỉ nào sau đây là địa chỉ vật lý?
- a. Địa chỉ nhớ do CPU gửi tới bộ phận MMU  
- **<span style="color:red"><strong>b. Địa chỉ do MMU gửi tới memory controller.</strong></span>**  
- c. Tất cả đều sai  
- d. Chương trình in ra địa chỉ của một biến toàn cục  

**Giải thích:**  
- **Đáp án đúng (b):** CPU gửi địa chỉ logic (virtual address) tới MMU. MMU chuyển đổi địa chỉ này thành địa chỉ vật lý rồi gửi đến bộ điều khiển bộ nhớ (memory controller) để truy cập dữ liệu.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Đây chỉ là địa chỉ logic được tạo ra bởi CPU, không phải là địa chỉ vật lý.  
  - **c:** Vì đáp án (b) đúng nên không thể chọn "Tất cả đều sai".  
  - **d:** Địa chỉ in ra của biến toàn cục chỉ là địa chỉ logic trong không gian tiến trình, chứ không phải địa chỉ vật lý được MMU chuyển đổi.

---

## Câu 2: Xem xét một chương trình C dưới đây. Hãy cho biết hiện thực hàm `counter()` có vấn đề gì?
```c
VOID *COUNTER( VOID *N ){
    INT S = 0;
    INT *B = (INT*)N;
    FOR( INT I = *B; I < *(B+1); I++ )
        S += I;
    RETURN &S;
}
```
- a. Giá trị ở vùng nhớ `B+1` là không được dùng.  
- b. Trả về một con trỏ đến tổng `S` là không cần thiết, mặc dù vẫn dùng được.  
- **<span style="color:red"><strong>c. Trả về con trỏ đến biến địa phương (S) là không ổn định.</strong></span>**  
- d. Hàm không có vấn đề gì.

**Giải thích:**  
- **Đáp án đúng (c):** Biến `S` được khai báo bên trong hàm (biến cục bộ) và lưu trên stack. Khi hàm kết thúc, vùng nhớ chứa `S` có thể bị ghi đè, làm cho con trỏ trả về trở nên không hợp lệ.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Giá trị của `B+1` được sử dụng để xác định giới hạn vòng lặp, không có vấn đề về quyền truy cập vùng nhớ trong đoạn code này (giả sử `N` trỏ đến một mảng hợp lệ có ít nhất 2 phần tử).  
  - **b:** Mặc dù việc trả về địa chỉ của biến `S` không cần thiết về mặt thiết kế, nhưng lỗi quan trọng là trả về địa chỉ của biến cục bộ gây rủi ro về tính ổn định.  
  - **d:** Có lỗi trong hàm do trả về địa chỉ của biến cục bộ.

---

## Câu 3: Yếu tố nào sau đây dùng để phân biệt multi-programming và multi-tasking?
- **<span style="color:red"><strong>A. Multi-programming dùng định thời dạng non-preemptive, trong khi multi-tasking dùng định thời dạng preemptive.</strong></span>**  
- B. Số lượng quá trình đợi trong hàng của multi-programming lớn hơn của multi-tasking.  
- C. Multi-programming hướng đến hiệu suất sử dụng CPU và multi-tasking hướng đến khả năng phản ứng với người dùng.  
- D. Hai khái niệm này là giống nhau.

**Giải thích:**  
- **Đáp án đúng (A):** Multi-programming thường không dùng cơ chế preemptive (cưỡng chế ngắt tiến trình đang chạy), trong khi multi-tasking sử dụng preemptive scheduling để chia sẻ CPU giữa các tiến trình nhằm đáp ứng tốt hơn với yêu cầu của người dùng.  
- **Tại sao các đáp án khác sai:**  
  - **B:** Số lượng tiến trình chờ trong hàng không phải là tiêu chí phân biệt cơ bản; nó phụ thuộc vào chính sách lập lịch cụ thể của hệ điều hành.  
  - **C:** Mặc dù phát biểu này có phần đúng (mục tiêu của multi-tasking là cải thiện khả năng phản hồi), nhưng nó không phản ánh đầy đủ đặc điểm phân biệt về kỹ thuật định thời giữa hai chế độ.  
  - **D:** Hai khái niệm có những khác biệt rõ rệt về cách quản lý tiến trình và định thời.

---

## Câu 4: Ngắt (interrupt) nào được sử dụng để phục vụ quá trình định thời của hệ điều hành?
- a. Mọi ngắt (interrupt)  
- **<span style="color:red"><strong>b. Ngắt mềm (trap).</strong></span>**  
- c. Các câu khác sai.  
- d. Ngắt I/O

**Giải thích:**  
- **Đáp án đúng (b):** Ngắt mềm (trap) là ngắt do phần mềm tạo ra để chuyển đổi chế độ từ user mode sang kernel mode, thường được dùng để xử lý system call và định thời lập lịch.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Không phải mọi loại ngắt đều dùng cho định thời; nhiều ngắt khác (như ngắt từ thiết bị ngoại vi) có mục đích khác.  
  - **c:** Vì đáp án (b) đã đúng, nên các lựa chọn khác không phù hợp.  
  - **d:** Ngắt I/O chủ yếu phục vụ cho giao tiếp với thiết bị ngoại vi, không chuyên để định thời.

---

## Câu 5: So sánh các hệ điều hành:
- **<span style="color:red"><strong>a. MS-DOS và UNIX đều là cấu trúc dạng hệ thống đơn (monolithic).</strong></span>**  
- b. MS-DOS và Linux đều là cấu trúc dạng hệ thống đơn (monolithic) và có thể phân lớp.  
- c. MS-DOS và Linux đều là cấu trúc microkernel và theo hướng tiếp cận phân lớp (layered approach).  
- d. UNIX và Linux đều là cấu trúc microkernel.

**Giải thích:**  
- **Đáp án đúng (a):** MS-DOS là hệ điều hành đơn giản với kiến trúc monolithic. UNIX truyền thống cũng được xây dựng theo mô hình monolithic, mặc dù phức tạp hơn.  
- **Tại sao các đáp án khác sai:**  
  - **b:** Linux về cơ bản là monolithic kernel (mặc dù có khả năng tải module động), không phải là "hệ thống đơn và có thể phân lớp" theo nghĩa là chuyển sang kiến trúc phân lớp hoàn toàn.  
  - **c:** MS-DOS không phải là microkernel, và Linux cũng không được xây dựng theo kiến trúc microkernel.  
  - **d:** Cả UNIX và Linux đều không được xây dựng theo mô hình microkernel; chúng thuộc dạng monolithic.

---

## Câu 6: Chọn phát biểu đúng về process.
- a. Tên trạng thái của process là không đổi đối với mọi hệ điều hành  
- b. Tất cả các câu trên đều đúng  
- **<span style="color:red"><strong>c. Process là một chương trình đang thực thi.</strong></span>**  
- d. Trong bất kỳ hệ thống nào cũng chỉ có duy nhất một process ở trạng thái running tại một thời điểm

**Giải thích:**  
- **Đáp án đúng (c):** Process (tiến trình) là chương trình đang được thực thi, đi kèm với các thông tin trạng thái và tài nguyên cần thiết.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Các hệ điều hành có thể định nghĩa và đặt tên trạng thái của tiến trình khác nhau (ví dụ: ready, waiting, blocked, running, …).  
  - **b:** Vì không phải tất cả các phát biểu đều đúng; phát biểu (a) và (d) sai.  
  - **d:** Trong hệ thống đa lõi, có thể có nhiều tiến trình chạy song song; ngay cả trên hệ thống đơn lõi, tiến trình trong trạng thái running có thể chuyển đổi nhanh chóng qua các time slice.

---

## Câu 7: Hệ điều hành (HĐH) là:
- a. Phần mềm ứng dụng của người dùng.  
- **<span style="color:red"><strong>b. Phần mềm trung gian giữa phần cứng máy tính và người sử dụng.</strong></span>**  
- c. Phần mềm cung cấp các dịch vụ cơ bản cho các ứng dụng.  
- d. Phần mềm được cài sẵn trên mọi máy tính.

**Giải thích:**  
- **Đáp án đúng (b):** Hệ điều hành là lớp trung gian quản lý tài nguyên phần cứng, cung cấp giao diện cho người dùng và ứng dụng.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Phần mềm ứng dụng là các chương trình chạy trên hệ điều hành, không phải hệ điều hành tự nó.  
  - **c:** Mặc dù đây là một tính năng của hệ điều hành, nhưng mô tả không đầy đủ vai trò trung gian giữa phần cứng và người dùng.  
  - **d:** Không phải máy tính nào cũng cài sẵn cùng một hệ điều hành; có nhiều loại HĐH khác nhau.

---

## Câu 8: Cho đoạn chương trình sau:
```c
#include <stdio.h>

char str1[6] = "ASCII";
char str2[6] = "HELLO";

int main(int argc, char* argv[])
{
    printf("%p", &str2);
}
```
Trong file nhị phân, phần `.data` chứa:  
- 0x00001038 "ASCII" với giá trị 0x41 53 43 49 49  
- 0x0000103E "HELLO" với giá trị 0x48 45 4C 4C 4F  

Khi thực thi, phần `.data` được định vị lại (relocated) tại địa chỉ 0x601050. Giá trị kết quả được in ra là:
- A. 0x000103E  
- B. 0x601050  
- C. Số khác.  
- **<span style="color:red"><strong>D. 0x601056</strong></span>**

**Giải thích:**  
- **Đáp án đúng (D):** Sau khi định vị lại, nếu `str1` được đặt tại 0x601050 và chiếm 6 byte, `str2` sẽ được đặt ngay sau đó tại 0x601056.  
- **Tại sao các đáp án khác sai:**  
  - **A:** Đây là địa chỉ ban đầu trong file nhị phân, chưa được định vị lại.  
  - **B:** Đây là địa chỉ bắt đầu của phần `.data` sau khi định vị lại, không phải địa chỉ của `str2`.  
  - **C:** "Số khác" không đưa ra kết quả chính xác theo cơ chế định vị lại được mô tả.

---

## Câu 9: Hệ điều hành Linux có kiến trúc lõi nào sau đây:
- a. Purely monolithic.  
- **<span style="color:red"><strong>b. Monolithic modular kernel.</strong></span>**  
- c. Layered kernel.  
- d. Microkernel.

**Giải thích:**  
- **Đáp án đúng (b):** Linux được xây dựng dưới dạng monolithic kernel với tính năng hỗ trợ module, cho phép nạp và gỡ bỏ các thành phần mở rộng mà không cần khởi động lại hệ thống.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Mặc dù Linux có yếu tố monolithic, nhưng nó không phải là "purely monolithic" vì hỗ trợ tính năng module động.  
  - **c:** Layered kernel là một mô hình khác không áp dụng cho Linux.  
  - **d:** Linux không được xây dựng theo kiến trúc microkernel.

---

## Câu 10: Chọn phát biểu đúng về cấu trúc monolithic:
- a. Có hiệu năng (performance) giảm so với các cấu trúc khác.  
- **<span style="color:red"><strong>b. Các dịch vụ của hệ điều hành đều được tích hợp vào kernel.</strong></span>**  
- c. Việc trao đổi dữ liệu giữa các thành phần chức năng của kernel thực hiện chủ yếu bằng cơ chế message-passing.  
- d. Việc thêm các chức năng của hệ điều hành được thực hiện dễ dàng hơn so với cấu trúc microkernel.

**Giải thích:**  
- **Đáp án đúng (b):** Trong hệ thống monolithic, hầu hết các dịch vụ (quản lý bộ nhớ, file system, driver, ...) đều được tích hợp trực tiếp vào kernel.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Thực tế, monolithic kernel có hiệu năng cao vì các thành phần được tích hợp trong cùng một không gian, mặc dù điều này có thể làm cho việc bảo trì trở nên phức tạp hơn.  
  - **c:** Message passing chủ yếu được sử dụng trong microkernel, không phải trong monolithic kernel, nơi các thành phần thường giao tiếp trực tiếp qua gọi hàm hoặc shared memory.  
  - **d:** Việc thêm chức năng trong monolithic kernel thường phức tạp hơn do sự phụ thuộc chặt chẽ giữa các thành phần.

---

## Câu 11: Chọn câu đúng về cấu trúc monolithic và cấu trúc microkernel:
- **<span style="color:red"><strong>a. Trên cấu trúc HĐH microkernel các module giao tiếp dùng kiểu truyền thông điệp, còn cấu trúc HĐH monolithic các module giao tiếp dùng kiểu truyền vùng nhớ chia sẻ (shared memory).</strong></span>**  
- b. Trên cấu trúc HĐH monolithic các module giao tiếp dùng kiểu truyền thông điệp, còn cấu trúc HĐH microkernel các module giao tiếp dùng kiểu truyền thông điệp.  
- c. Trên cấu trúc HĐH monolithic các module giao tiếp dùng kiểu truyền thông điệp (message passing), còn cấu trúc HĐH microkernel các module giao tiếp dùng kiểu truyền vùng nhớ chia sẻ (shared memory).  
- d. Các câu khác đều sai.

**Giải thích:**  
- **Đáp án đúng (a):** Kiến trúc microkernel thường tách các thành phần hệ thống ra khỏi kernel cốt lõi và giao tiếp qua cơ chế truyền thông điệp để tăng tính cách ly, trong khi trong monolithic kernel các thành phần giao tiếp trực tiếp qua vùng nhớ chia sẻ hoặc gọi hàm trực tiếp.  
- **Tại sao các đáp án khác sai:**  
  - **b:** Không phân biệt được sự khác nhau về phương thức giao tiếp giữa monolithic và microkernel.  
  - **c:** Đảo ngược cơ chế giao tiếp của từng kiến trúc.  
  - **d:** Vì đáp án (a) đã đúng nên không thể nói "các câu khác đều sai".

---

## Câu 12: Trong hệ thống đa lõi hiện nay (multi-core system), luật Amdahl tính số lượng lõi xử lý N trong công thức theo:
- A. Số lượng lõi xử lý (processing core).  
- B. Số lượng luồng xử lý của ứng dụng.  
- **<span style="color:red"><strong>C. Tỷ lệ song song hóa của ứng dụng.</strong></span>**  
- D. Cả ba A, B, C đều sai.

**Giải thích:**  
- **Đáp án đúng (C):** Luật Amdahl đo lường mức cải thiện hiệu năng tối đa khi tăng số lượng lõi, dựa trên tỷ lệ phần trăm công việc có thể được thực hiện song song trong ứng dụng.  
- **Tại sao các đáp án khác sai:**  
  - **A:** Luật Amdahl không trực tiếp tính theo số lượng lõi mà là giới hạn cải thiện phụ thuộc vào khả năng song song hóa của bài toán.  
  - **B:** Số lượng luồng xử lý của ứng dụng không phải là yếu tố chính trong công thức của Luật Amdahl.  
  - **D:** Vì đáp án (C) là chính xác nên không thể chọn "Cả ba đều sai".

---

## Câu 13: Chọn câu đúng về hệ thống phân bố:
- a. Các câu khác đều sai.  
- b. Client-server không phải là một mô hình trong hệ thống phân bố.  
- c. Giảm độ sẵn sàng (low availability).  
- **<span style="color:red"><strong>d. Dễ chia sẻ tài nguyên.</strong></span>**

**Giải thích:**  
- **Đáp án đúng (d):** Hệ thống phân bố được thiết kế để kết nối các nút (node) qua mạng, giúp dễ dàng chia sẻ và truy cập tài nguyên trên nhiều máy tính khác nhau.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Có đáp án đúng (d) nên không thể nói "các câu khác đều sai".  
  - **b:** Client-server là một mô hình phổ biến trong hệ thống phân bố.  
  - **c:** Hệ thống phân bố thường nhằm tăng tính sẵn sàng và khả năng chịu lỗi, không phải giảm.

---

## Câu 14: Một tập tin thực thi sở hữu bởi root (ví dụ như `ping`). Cách nào để lõi hệ điều hành cho phép một user bình thường có thể thực hiện file thực thi này?
- a. Chỉ có root mới thực thi được tập tin đã cho.  
- b. Hệ điều hành không cần làm gì hết.  
- **<span style="color:red"><strong>c. Hệ điều hành sẽ thay đổi user ID của quá trình sang Effective ID trùng với ID của tập tin thực thi.</strong></span>**  
- d. Hệ điều hành thay đổi user ID của tập tin sang user của người dùng bình thường, rồi thực thi tập tin này.

**Giải thích:**  
- **Đáp án đúng (c):** Khi một tập tin có bit setuid được thực thi, hệ điều hành sẽ thay đổi Effective User ID của tiến trình thành ID của chủ sở hữu tập tin (thường là root), cho phép tiến trình chạy với quyền cao.  
- **Tại sao các đáp án khác sai:**  
  - **a:** Nếu chỉ có root mới được phép, thì setuid sẽ không có ý nghĩa; mục đích của setuid là cho phép người dùng bình thường chạy tập tin với đặc quyền của chủ sở hữu.  
  - **b:** Hệ điều hành cần thực hiện thay đổi quyền để đảm bảo bảo mật và hoạt động đúng của setuid.  
  - **d:** Không phải thay đổi user ID của tập tin, mà thay đổi user ID của tiến trình chạy file đó.

---

## Câu 15: Cách nào sau đây là phù hợp để truyền tham số có kích thước lớn qua system call từ không gian người dùng (user-space) đến không gian lõi hệ điều hành (kernel-space)?
- A. Dùng thanh ghi.  
- **<span style="color:red"><strong>B. Dùng bộ nhớ chung và trao đổi địa chỉ bộ nhớ qua thanh ghi giữa người dùng và lõi.</strong></span>**  
- C. Dùng stack để truyền tham số.  
- D. Dùng bộ nhớ chung và trao đổi địa chỉ bộ nhớ qua stack giữa người dùng và lõi.

**Giải thích:**  
- **Đáp án đúng (B):** Khi truyền tham số lớn, sử dụng bộ nhớ chung giúp tránh việc sao chép dữ liệu nhiều lần, chỉ cần trao đổi địa chỉ của vùng nhớ qua thanh ghi là tối ưu hơn so với việc truyền dữ liệu qua stack hoặc trực tiếp qua thanh ghi.  
- **Tại sao các đáp án khác sai:**  
  - **A:** Thanh ghi có dung lượng giới hạn, không thể chứa dữ liệu có kích thước lớn.  
  - **C:** Stack cũng bị giới hạn về dung lượng và không tối ưu cho việc truyền dữ liệu lớn.  
  - **D:** Việc trao đổi qua stack không phải là cách tối ưu, vì mục tiêu là truyền địa chỉ của bộ nhớ chung qua thanh ghi để giảm việc sao chép.

---

## 1. Quản Lý Bộ Nhớ (Memory Management)

### 1.1. Địa Chỉ Logic (Virtual Address) và Địa Chỉ Vật Lý (Physical Address)
- **Địa chỉ logic (virtual address):**  
  Đây là địa chỉ mà chương trình (hoặc CPU) “nhìn thấy” khi thực thi. Nó nằm trong không gian bộ nhớ riêng của mỗi tiến trình.
- **Địa chỉ vật lý (physical address):**  
  Là địa chỉ thật sự trên bộ nhớ (RAM) của máy tính. Địa chỉ logic được chuyển đổi sang địa chỉ vật lý thông qua **Memory Management Unit (MMU)**.

### 1.2. Vai Trò của MMU và Cơ Chế Chuyển Đổi Địa Chỉ
- **MMU (Memory Management Unit):**  
  Đây là bộ phận phần cứng chịu trách nhiệm chuyển đổi địa chỉ logic thành địa chỉ vật lý. Nó sử dụng các bảng ánh xạ (như bảng trang – page table) để thực hiện chuyển đổi này.
- **Quá trình chuyển đổi:**  
  Khi CPU tạo ra một địa chỉ logic, MMU sẽ tra cứu bảng trang để tìm địa chỉ vật lý tương ứng, sau đó gửi địa chỉ vật lý này đến bộ điều khiển bộ nhớ (memory controller) để truy cập dữ liệu.

### 1.3. Phân Trang (Paging) và Phân Đoạn (Segmentation)
- **Paging:**  
  Bộ nhớ được chia thành các khối có kích thước cố định gọi là “page”. Mỗi tiến trình có bảng trang ánh xạ các page ảo sang các frame vật lý trong RAM.
- **Segmentation:**  
  Bộ nhớ được chia thành các đoạn (segment) với kích thước khác nhau, dựa trên các khối logic của chương trình như mã lệnh, dữ liệu, stack, v.v.

---

## 2. Lập Lịch CPU (CPU Scheduling) và Quản Lý Tiến Trình

### 2.1. Multi-programming vs. Multi-tasking
- **Multi-programming:**  
  - Cho phép nhiều chương trình cùng “được nạp” vào bộ nhớ và luân phiên thực thi.  
  - Thường dùng phương pháp **non-preemptive scheduling** (không cưỡng chế ngắt tiến trình đang chạy) do các tiến trình thường chuyển giao CPU khi chúng chờ I/O.
- **Multi-tasking:**  
  - Là việc chạy nhiều tiến trình “đồng thời” bằng cách chuyển đổi nhanh giữa các tiến trình.
  - Thường sử dụng **preemptive scheduling**, cho phép hệ điều hành cưỡng chế tạm dừng tiến trình đang chạy để chuyển sang tiến trình khác, nhằm đảm bảo khả năng phản hồi tốt cho người dùng.

### 2.2. Các Thuật Toán Lập Lịch
- **FCFS (First Come, First Served):**  
  Tiến trình đến trước được phục vụ trước.
- **SJF (Shortest Job First):**  
  Tiến trình có thời gian thực thi ngắn nhất được ưu tiên.
- **Round Robin:**  
  Mỗi tiến trình được cấp một khoảng thời gian nhất định (time slice) trước khi chuyển sang tiến trình kế tiếp.
- **Priority Scheduling:**  
  Mỗi tiến trình được gán một mức độ ưu tiên; tiến trình có mức ưu tiên cao hơn sẽ được chọn chạy trước.

### 2.3. Quản Lý Tiến Trình (Process Management)
- **Tiến trình (process):**  
  Là một chương trình đang thực thi, bao gồm mã lệnh, dữ liệu, và thông tin trạng thái (context) cần thiết để thực hiện.
- **Các trạng thái của tiến trình:**  
  - **New:** Tiến trình vừa được tạo ra.
  - **Ready:** Tiến trình đã sẵn sàng để chạy.
  - **Running:** Tiến trình đang được CPU thực thi.
  - **Waiting (Blocked):** Tiến trình đang chờ một sự kiện (như I/O) xảy ra.
  - **Terminated:** Tiến trình đã hoàn thành hoặc bị dừng.
- **Thread:**  
  Là đơn vị nhỏ hơn của tiến trình, có thể chạy song song trong cùng một tiến trình và chia sẻ cùng không gian địa chỉ.

---

## 3. Cấu Trúc Hệ Điều Hành (OS Architecture)

### 3.1. Kernel Monolithic
- **Đặc điểm:**  
  - Toàn bộ các dịch vụ và thành phần (quản lý bộ nhớ, lập lịch, hệ thống file, driver…) được tích hợp trong một không gian kernel duy nhất.
  - Hiệu năng cao do các thành phần này có thể gọi hàm trực tiếp cho nhau mà không cần phải qua giao thức giao tiếp giữa các module.
- **Ưu điểm:**  
  - Tốc độ thực thi nhanh.
- **Nhược điểm:**  
  - Khó mở rộng, bảo trì và kiểm soát lỗi vì lỗi của một module có thể ảnh hưởng đến toàn bộ kernel.
- **Ví dụ:**  
  - UNIX truyền thống, MS-DOS, Linux (dù có hỗ trợ module động, nhưng về cơ bản vẫn là monolithic).

### 3.2. Kernel Microkernel
- **Đặc điểm:**  
  - Chỉ giữ lại những chức năng cốt lõi nhất (như quản lý bộ nhớ, lập lịch, xử lý ngắt) trong kernel. Các dịch vụ hệ thống khác (hệ thống file, driver…) chạy trong không gian người dùng.
  - Các module giao tiếp với nhau qua cơ chế **message passing**.
- **Ưu điểm:**  
  - Tăng cường khả năng mở rộng và độ tin cậy, vì lỗi của một dịch vụ không làm sụp toàn bộ hệ thống.
- **Nhược điểm:**  
  - Hiệu năng có thể thấp hơn do chi phí giao tiếp giữa các module.
- **Ví dụ:**  
  - Hệ điều hành Mach, MINIX.

### 3.3. Các Kiến Trúc Khác
- **Hybrid Kernel:**  
  - Kết hợp những ưu điểm của monolithic và microkernel, cho phép một số thành phần chạy trong kernel để đảm bảo hiệu năng, đồng thời tách biệt các dịch vụ không cốt lõi để tăng tính ổn định.
- **Layered Kernel:**  
  - Cấu trúc chia kernel thành các lớp, mỗi lớp chỉ tương tác với lớp kế bên. Điều này giúp tổ chức mã nguồn rõ ràng và dễ dàng bảo trì.

---

## 4. Interrupt và System Call

### 4.1. Interrupt (Ngắt)
- **Hardware Interrupt:**  
  - Là tín hiệu từ phần cứng (ví dụ: bàn phím, chuột, thiết bị lưu trữ) báo hiệu yêu cầu dịch vụ.
- **Software Interrupt (Trap):**  
  - Là tín hiệu do phần mềm tạo ra, thường dùng để chuyển chế độ từ user mode sang kernel mode khi thực hiện system call.
- **Vai trò:**  
  - Cho phép hệ điều hành phản hồi nhanh chóng với các sự kiện bất thường và quản lý chuyển giao điều khiển giữa các tiến trình.

### 4.2. System Call
- **Định nghĩa:**  
  - Là giao diện mà qua đó chương trình ở user mode yêu cầu các dịch vụ từ kernel (ví dụ: thao tác file, quản lý tiến trình, giao tiếp mạng…).
- **Truyền Tham Số:**  
  - Với các tham số có kích thước nhỏ, thông tin thường được truyền qua các thanh ghi.  
  - Đối với các tham số lớn (ví dụ: các cấu trúc dữ liệu lớn), có thể sử dụng bộ nhớ chung (shared memory) và trao đổi địa chỉ bộ nhớ qua thanh ghi để tránh việc sao chép dữ liệu nhiều lần.
- **Chuyển Đổi Chế Độ:**  
  - Khi thực hiện system call, CPU chuyển từ user mode sang kernel mode để thực hiện các tác vụ có đặc quyền cao.

---

## 5. Một Số Khái Niệm Khác Liên Quan

### 5.1. Setuid và Quyền Thực Thi File
- **Setuid:**  
  - Một file thực thi có thể được cài đặt bit setuid, nghĩa là khi một người dùng bình thường chạy file đó, hệ điều hành sẽ thay đổi effective user ID của tiến trình sang user ID của chủ sở hữu file (thường là root).  
  - Điều này cho phép người dùng thực hiện các tác vụ mà chỉ người dùng có đặc quyền mới được phép.

### 5.2. Hệ Thống Phân Bố (Distributed System)
- **Định Nghĩa:**  
  - Hệ thống phân bố là tập hợp các máy tính kết nối với nhau qua mạng, cùng nhau cung cấp một dịch vụ hoặc chia sẻ tài nguyên.
- **Ưu Điểm:**  
  - Tăng khả năng mở rộng, khả năng chịu lỗi và hiệu quả trong việc chia sẻ tài nguyên.
- **Nhược Điểm:**  
  - Đòi hỏi phải có cơ chế đồng bộ hóa và giao tiếp hiệu quả giữa các nút (node) để đảm bảo tính nhất quán và an toàn dữ liệu.

### 5.3. Luật Amdahl (Amdahl's Law)
- **Khái Niệm:**  
  - Luật Amdahl mô tả giới hạn tối đa của hiệu năng tăng lên khi cải thiện một phần của hệ thống (chẳng hạn như song song hóa) dựa trên tỷ lệ phần trăm của công việc có thể song song hóa.
- **Ý Nghĩa Trong Hệ Thống Đa Lõi:**  
  - Khi tăng số lượng lõi xử lý, hiệu năng tăng không thể vượt quá một giới hạn nhất định nếu phần mềm chỉ có một tỷ lệ nhất định được thực hiện song song.  
  - Ví dụ, nếu chỉ 50% công việc có thể song song, dù ta có bao nhiêu lõi thì hiệu năng tối đa cũng chỉ tăng gấp đôi.

---

## 6. Tóm Lại
Các lý thuyết trên tạo thành nền tảng cho việc hiểu cách một hệ điều hành vận hành và quản lý các tài nguyên phần cứng và phần mềm:
- **Quản lý bộ nhớ:** Giúp chuyển đổi và ánh xạ giữa địa chỉ logic và địa chỉ vật lý, tối ưu hóa việc sử dụng bộ nhớ.
- **Lập lịch CPU và quản lý tiến trình:** Đảm bảo rằng nhiều tiến trình được xử lý hiệu quả, cho phép đa nhiệm và tăng phản hồi hệ thống.
- **Kiến trúc kernel:** Quyết định cách các thành phần hệ điều hành được tổ chức, ảnh hưởng đến hiệu năng, độ tin cậy và khả năng mở rộng.
- **Interrupt và system call:** Cơ chế giao tiếp giữa phần cứng, phần mềm và kernel, tạo nên sự linh hoạt và bảo mật của hệ thống.
- **Hệ thống phân bố và luật Amdahl:** Những khái niệm quan trọng trong việc thiết kế và tối ưu hóa các hệ thống hiện đại có tính mở rộng và khả năng xử lý song song.

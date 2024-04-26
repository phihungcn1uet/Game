
# Fly simulater

Video chơi game:
# Giới thiêu game
Fly simulator là một shooter game trong đó người chơi điều khiển máy bay chiến đấu trên bầu trời nhằm tiêu diệt các kẻ địch và né tránh các vật thể nguy hiểm.
# 1.Cách tải game
## a.Cách tải không bao gồm code
Link tải: <https://github.com/phihungcn1uet/mineeeee/releases/tag/flysimulator>. 
Sau đó giải nén và mở Game.exe lên chơi.
## b.Cách tải bao gồm code
Clone repo này về
![Screenshot (146)](https://github.com/phihungcn1uet/Game/assets/161928550/32c8f430-d96c-4bbc-9e70-ace53e772899)
Tất cả code sẽ nằm trong thư mục Source code. 
Vì mã nguồn được viết trên Visual studio nên cần cài Visual Studio và các thư viện SDL. \
Cài Visual Studio: https://visualstudio.microsoft.com/fr/.
 \
Hướng dẫn thiết lập SDL trên Visual studio: \
<https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php>. \
 \
Hướng dẫn thiết lập SDL_image trên Visual studio: <https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/msvc2019/index.php>. 
|Tên thư viện| Link tải|
|------------|---------------|
|SDL|https://github.com/libsdl-org/SDL/releases|
|SDL_image |https://github.com/libsdl-org/SDL_image/releases|
|SDL_ttf|https://github.com/libsdl-org/SDL_mixer/releases|
|SDL_mixer|https://github.com/libsdl-org/SDL_ttf/releases|

# 2.Bắt đầu game
Click vào nút PlayGame để bắt đầu trò chơi hoặc nút Exit để thoát game.
![Screenshot 2024-04-25 212250](https://github.com/phihungcn1uet/Game/assets/161928550/fffd595a-d36b-4e86-be03-92d642f0cd75)
Click vào How to play để xem tóm tắt cách chơi của game.
![Screenshot 2024-04-26 084554](https://github.com/phihungcn1uet/Game/assets/161928550/cdd9dec7-b49b-493f-8802-52e1de64a153)
Màn hình hướng dẫn chơi game hiện ra.
![Screenshot 2024-04-26 084630](https://github.com/phihungcn1uet/Game/assets/161928550/dccc8425-9f8e-4f8e-b5a2-3de64dc59976)
Có thể chọn tiếp tục chơi game(Play Game) hoặc thoát(Exit) sau đó.
Trong game cũng có màn hình tạm dừng khi ta nhấn nút ![pausegamebuttom](https://github.com/phihungcn1uet/Game/assets/161928550/e9355f96-72b5-4e9e-8b3d-61e7d227719f).Màn hình tạm dừng hiện ra như sau:
![Screenshot (145)](https://github.com/phihungcn1uet/Game/assets/161928550/93b88958-7d3b-4cd6-9907-e636a5e860ae)

# 3.Các thành phần trong game.
## a. Nhân vật và các thành phần liên quan đến nhân vật.
### Nhân vật chính.
Nhân vật chính sẽ là ![plane](https://github.com/phihungcn1uet/Game/assets/161928550/1da6a8f3-df46-472d-9a5d-1286fbb2b2f9) với khả năng bắn đạn.
### Mạng của nhân vật (Máu của nhân vật).
Khi bắt đầu trò chơi, nhân vật sẽ có 3 tim ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/cef5a775-4eeb-468b-aa9a-5f0224f26c96)![heart](https://github.com/phihungcn1uet/Game/assets/161928550/c1582771-324f-4a47-bc9a-3943eac78297)![heart](https://github.com/phihungcn1uet/Game/assets/161928550/69f113ed-1287-40ad-b80a-214e02b91959)
đại diện cho 3 mạng. Mỗi khi va chạm với kẻ địch hoặc bị các vật thể khác va chạm như ![boom](https://github.com/phihungcn1uet/Game/assets/161928550/92188128-484a-4f08-9a8c-4b8d4f388030) hoặc ![rocket](https://github.com/phihungcn1uet/Game/assets/161928550/1663b1a2-133c-4c8b-844b-cbbfff025ea6)
 lượng máu sẽ giảm đi 1 ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/2cfbe82c-cad4-4e75-a55f-1d2ca5dea5fd)
 ## b. Kẻ địch và các mối hiểm họa.
 ### Kẻ địch chính.
 Kẻ địch chính là những con chim ruồi ![nv](https://github.com/phihungcn1uet/Game/assets/161928550/239e14a8-3c74-4b3d-8498-84676e183b2e) Chúng sẽ xâm chiếm bầu trời nếu không tiêu diệt kịp thời! Nếu va chạm với chúng sẽ ngay lập tức bị trừ 1 mạng ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/9fc23fb9-9f03-409c-8f86-80749d848a25).Ngoài ra chúng không có chức năng đặc biệt gì.
 ![Screenshot (139)](https://github.com/phihungcn1uet/Game/assets/161928550/21e18a3a-0743-4978-9a4b-ef5a03ede5ad)

 ### Boss.
 Boss ![boss](https://github.com/phihungcn1uet/Game/assets/161928550/f98742df-5ed2-4b77-8511-d163f11586e9)
sẽ xuất hiện sau mỗi 50s của trò chơi. Boss sẽ thả ra một quả cầu gai ![bossskill](https://github.com/phihungcn1uet/Game/assets/161928550/f1695dfd-be9e-4d6f-826c-6170f150034a) có khả năng hấp thụ đạn bắn (kể cả viên đạn đặc biệt) và tiêu diệt mục tiếu trong tầm. Điểm yếu của kĩ năng ![bossskill](https://github.com/phihungcn1uet/Game/assets/161928550/11b5d001-447f-47d9-a8a7-f1cb5a94a30e) này là chúng chỉ được sử dụng sau mỗi 2s kể từ khi Boss xuất hiện. Hãy căn chuẩn thời gian để tiêu diệt kẻ địch này!
![Screenshot (142)](https://github.com/phihungcn1uet/Game/assets/161928550/6ba1959e-51f9-4712-b07b-c76f43a31252)

 ### Tên lửa.
 Tên lửa ![rocket](https://github.com/phihungcn1uet/Game/assets/161928550/1150163a-2232-4571-9850-4ee7764da131) sẽ xuất hiện sau mỗi 7s. Chúng phóng đi rất nhanh và không thể bị phá hủy bởi đạn bình thường. Bị trúng tên lửa cũng khiến ta bị trừ 1 mạng ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/11bbb567-b532-4158-8f47-e860e94fe580)
 ![Screenshot (140)](https://github.com/phihungcn1uet/Game/assets/161928550/3c42c71f-6cd7-4103-a5dd-8e1297a97ebe)
 ### Bom.
 Bom ![boom](https://github.com/phihungcn1uet/Game/assets/161928550/b8c917a2-4f67-4f65-8aed-5151518648cc) sẽ rơi sau mỗi 9s. Chúng sẽ rơi từ trên trời xuống nên sẽ rất khó để né tránh nếu không tập trung. Tương tự như tên lửa, trúng bom cũng khiến ta trừ 1 mạng ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/11bbb567-b532-4158-8f47-e860e94fe580)
 ![Screenshot (144)](https://github.com/phihungcn1uet/Game/assets/161928550/130ef07b-b2bb-4172-89a9-a9b0911f3677)
 ## c. Các hiệu ứng hỗ trợ nhân vật.
  Để đối đầu với các mối hiểm họa nêu trên, nhân vật sẽ được trong bị các hiệu ứng hỗ trợ ngẫu nhiên nằm trong luckybox ![luckybox](https://github.com/phihungcn1uet/Game/assets/161928550/85b5a30b-f877-4466-b3a7-45c693a6acb1) Có ba hiệu ứng đó là
  |STT |Tên hiệu ứng |Hoạt ảnh hiệu ứng |Chức năng chính|
  |----|-------------|------------------|---------------|
  |1  |Hiệu ứng khiên chắn | ![shieldplane](https://github.com/phihungcn1uet/Game/assets/161928550/98174c0e-299d-45b5-8569-86d36ef49709)| Chặn mọi loại sát thương. |
  |2| Hiệu ứng hồi máu| ![healplane](https://github.com/phihungcn1uet/Game/assets/161928550/b198a9be-7f73-48cc-b716-4679a6aa72f4)| Hồi lại một máu(một mạng).|
  |3|Hiệu ứng đạn đặc biệt|![fireball](https://github.com/phihungcn1uet/Game/assets/161928550/d393606f-3a40-4f2f-aaef-f6eb6e3bf0db)| Đạn đặc biệt sẽ tiêu diệt gần như mọi thứ kể cả bom, tên lửa đồng thời gây 2 sát thương lên boss, nhưng không phá được kỹ năng ![bossskill](https://github.com/phihungcn1uet/Game/assets/161928550/6ab8bc78-8515-49b6-a17d-c8ae1b073e8c).
  ### d. Một số thành phần khác của game.
  |STT |Tên |Mô tả |
  |----|----|------|
  |1| ![Screenshot (143)](https://github.com/phihungcn1uet/Game/assets/161928550/033ffffe-1246-43d5-bad3-9c0b9ed7db92)| là điểm số cũng như là số kẻ địc chính( chim ruồi) tiêu diệt được|
  |2| ![Screenshot (140)](https://github.com/phihungcn1uet/Game/assets/161928550/d3b27ea3-a10c-42e2-b982-7fd9e6b3d467)| thời gian trong game, liên quan mật thiết tới các vật thể và boss|
  |3|![Screenshot (142)](https://github.com/phihungcn1uet/Game/assets/161928550/881adbb0-aa5d-4417-bb3f-44f0f1021797)| Máu của Boss, tối đa 20 máu|
  |4|![Screenshot (141)](https://github.com/phihungcn1uet/Game/assets/161928550/1e7e7737-762d-4aec-a424-168150979ac8)| Tạm dừng trò chơi|
  # Cách chơi game.
  Nhân vật trong game ![plane](https://github.com/phihungcn1uet/Game/assets/161928550/feb3428e-4d10-4be4-94f7-b5a65d0ffbf4) sử dụng
  WASD tương ứng đi lên, sang trái, đi xuống và sang phải để di chuyển cũng như nhấn P để bắn đạn![bullet1](https://github.com/phihungcn1uet/Game/assets/161928550/ec811936-ad77-4146-a7cc-9fb77598a665)
  
  Đây là endless game đề cao tính giải trí trong khi chơi game.Trò chơi sẽ kết thúc khi số mạng(số tim) ![heart](https://github.com/phihungcn1uet/Game/assets/161928550/e317ee6b-2a29-4264-a2ee-9b6c3655c27e)
  về không. Hãy cố gắng đừng để bị tiêu diệt trong khi tận hưởng và giành lấy số điểm thật cao!
  # Về Source Code.
  |STT |Tên File(cả .h và .cpp) |Chức năng | Nguồn tham khảo(nếu có)|
  |----|-----------|----------|------------------------|
  |1| LibFile| File này dùng để khia báo các thư viện khác và cài đặt một số biến cơ bản||
  |2| BaseObject| File này để định nghĩa các chức năng cơ bản và dùng để kế thừa|<https://lazyfoo.net/tutorials/SDL/>|
  |3| Figure| File này để định nghĩa nhân vật trong game, di chuyển và bắn đạn||
  |4| enemy| File này để định nghĩa kẻ địch chính và boss||
  |5| Boom | File này định nghĩa bom||
  |6| Rocket | File này định nghĩa tên lửa||
  |7| Life | File này xử lý mạng của nhân vật||
  |8| TextObjext| File này xử lý các vấn đề liên quan đến hiển thị chữ|<https://www.youtube.com/watchv=P1RbIpQOAqM&list=PLR7NDiX0QsfTIEQUeYCfc2MyCquX0ig9V&index=24&ab_channel=Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123A-Z>|
  |9| time | File này xử lý fps| <https://www.youtube.com/watch?v=qhqtxum_uA0&list=PLR7NDiX0QsfTIEQUeYCfc2MyCquX0ig9V&index=8&ab_channel=Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123A-Z>|
  |10| Menu | File này xử lý menu||
  |11| Special| File này xử lý các hiệu ứng đặc biệt||

  










 
 




 












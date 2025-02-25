# ex-0-9

Thonny 설명 Google 에서 이것을 검색 합니다 MicroPython - Raspberry Pi Documentation
그다음에 끌릭 하면 Drag-and-Drop MicroPython 밑에 보면 만약에 자기가 가지고 있는 반도체
를 끌릭 해서 E 드라이브나 F 드라이브에 끌러다 놓습니다 다운로드 버젼을 생각해서 만약에 
Pico WH 라고 하면 저것을 끌릭해서 다운로드 해서 끌러다 D,F 쪽에 넣고요 그럼 환경이 만들어
지겠죠 그다음에 Thonny, Python IDE for beginners 가 Windows , Mac , Linux 3대 운영체제
가 있습니다 내가 Windows 하고 있다 그러면 64bit exe 파일을 다운로드 해서 실행 하면 된니다
환경을 내가 F 드라이브 쪽에 만들었다 거기 도구에서 시스템 쉘 열기 여기에서 인스톨 내가 필요
한 만약에 MQTT 인스톨 하고 쉽다 그럼 챗 GPT 나 윈도우 조종사 한테 물어 보면 답을 준니다
그것을 넣어 주면 된니다

ESP32 Dev Module

![이미지 설명](https://github.com/suho9soft/ex-0-9/blob/main/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202025-02-24%20121747.png)

![My Image](https://github.com/suho9soft/ex-0-9/blob/main/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202025-02-24%20122428.png)

![My Image](https://github.com/suho9soft/ex-0-9/blob/main/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202025-02-26%20025319.png)

라즈베리 파이 mysql workbench 명령어

sudo nano /etc/mysql/mariadb.conf.d/50-server.cnf

//아래 부분을 찾아서

bind-address = 127.0.0.1

//이렇게 바꿔주기(그리고 나서 저장)

bind-address = 0.0.0.0

//db접속

sudo mysql -u root

//사용자 계정생성

CREATE USER 'arduino'@'%' IDENTIFIED BY '123f5678';

//권한부여

GRANT CREATE, DROP, ALTER, SELECT, INSERT, UPDATE, DELETE ON . TO 'arduino'@'%'; FLUSH PRIVILEGES;

//데이터베이스 재부팅

sudo systemctl restart mariadb

//계정생성확인(로그인해보기)

sudo mysql -u arduino -p

//비밀번호입력

show databases;

1// use python14;

show tables;

desc rotary_data;

select * from rotary_data;

2// use python14;

show tables;

desc dht11_data;

select * from dht11_data;

3// use python14;

show tables;

desc final_data;

select * from final_data;

![My Image](https://github.com/suho9soft/ex-0-9/blob/main/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202025-02-21%20004948.png)

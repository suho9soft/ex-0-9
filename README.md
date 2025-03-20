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

ESP32 S3 (GND VCC SDL SDA) (- 3.3V 22 21)
아두이노 기본 설정

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

raspberry pi pico 2w 아두이노 기본 설정 

https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

//MY SQL//

라즈베리파이에 마리아DB 설치하기

sudo apt update && sudo apt upgrade -y

//설치

sudo apt install -y mariadb-server 

//커맨드라인클라이언트 실행

sudo mysql -u root





sudo systemctl restart mariadb

//계정생성 확인(로그인해보기)

sudo mysql -u arduino -p

//비밀번호입력

show databases;

1//  use python1;

show tables;

desc rotary_data;

select * from rotary_data;

2//  use python2;

show tables;

desc dht11_data;

select * from dht11_data;

3//  use python30;

show tables;

desc final_data;

select * from final_data;

4//  use python31;

show tables;

desc distance_data;

select * from distance_data;

5//  use python30;

show tables;

desc cds_data;

select * from cds_data;


// 라즈베리파이5 MQTTX 세팅 방법 //

//인터넷 Firefox 에 접속한다 그 다음 MQTTX 에서 Web 끌릭 그 다음

+ 끄릭 그럼 MQTTX 열린니다 그 다음에 이름 만약에 arduino 라고 접고

  그 다음 에 버젼 3.1.1 설정 그리고 Connect 끌릭 + New Subscription

  보여조 여기에  arduino/output

  그 다음 밑에 Published 여기에 다가은  arduino/input

  그 다음 비행기 모양 끌릭

  그럼 MQTTX 세팅이 된니다//






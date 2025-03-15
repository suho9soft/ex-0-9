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

/// MY SQL 설치

sudo apt install mariadb-server

sudo systemctl status mysql




라즈베리 파이 mysql workbench 명령어

sudo nano /etc/mysql/mariadb.conf.d/50-server.cnf

//아래 부분을 찾아서

bind-address = 127.0.0.1

//이렇게 바꿔주기(그리고 나서 저장)

bind-address = 0.0.0.0

//db접속

MySQL 루트 계정으로 접속:

bash

복사

sudo mysql -u root -p

위 명령어로 루트 계정에 접속한 후 비밀번호를 입력합니다.

사용자 계정 생성:

sql

복사

CREATE USER 'arduino'@'%' IDENTIFIED BY '123f5678';

이 명령어는 arduino라는 사용자를 생성하고, 비밀번호를 '123f5678'으로 설정합니다.

권한 부여:

MySQL에서 권한을 부여할 때 *.* (모든 데이터베이스 및 모든 테이블)에 대해 권한을 부여하려면 다음과 같이 작성해야 합니다.

sql

복사

GRANT CREATE, DROP, SELECT, INSERT, UPDATE, DELETE ON *.* TO 'arduino'@'%';

여기서 *.*는 모든 데이터베이스와 테이블을 의미합니다. 만약 특정 데이터베이스에만 권한을 부여하려면 *.*를 해당 데이터베이스 이름으로 변경할 수 있습니다.

예시: 특정 데이터베이스 mydatabase에만 권한을 부여하려면:

sql

복사

GRANT CREATE, DROP, SELECT, INSERT, UPDATE, DELETE ON mydatabase.* TO 'arduino'@'%';

권한 적용:

sql

복사

FLUSH PRIVILEGES;

이 명령어는 권한 부여 후에 MySQL 서버에 적용하는 명령어입니다.

최종적으로 전체 과정은 아래와 같습니다:

bash

복사

sudo mysql -u root -p

sql

복사

CREATE USER 'arduino'@'%' IDENTIFIED BY '123f5678';

GRANT CREATE, DROP, SELECT, INSERT, UPDATE, DELETE ON *.* TO 'arduino'@'%';

FLUSH PRIVILEGES;

이렇게 하면 arduino 사용자에게 MySQL의 모든 데이터베이스에 대해 필요한 권한이 부여됩니다.

//데이터베이스 재부팅

sudo systemctl restart mariadb

//계정생성확인(로그인해보기)

sudo mysql -u arduino - p

//비밀번호입력

//데이터베이스 재부팅

sudo systemctl restart mariadb

//계정생성확인(로그인해보기)

sudo mysql -u arduino -p

//비밀번호입력

show databases;

1// use python30;

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

4// use python31;

show tables;

desc distance_data;

select * from distance_data;

![My Image](https://github.com/suho9soft/ex-0-9/blob/main/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202025-02-21%20004948.png)




라즈베리파이에서 MQTT 클라이언트인 MQTTX를 설치하려면, MQTTX의 공식 GitHub 저장소에서 ARM 아키텍처용 AppImage 파일을 다운로드하여 실행할 수 있습니다. 아래는 설치 방법입니다:

MQTTX AppImage 다운로드:

라즈베리파이의 터미널을 열고, 다음 명령어를 입력하여 AppImage 파일을 다운로드합니다:

ruby

복사

편집

wget https://github.com/emqx/MQTTX/releases/download/v1.9.1/MQTTX-1.9.1-arm64.AppImage

위 명령어는 MQTTX의 1.9.1 버전을 ARM64 아키텍처용으로 다운로드합니다. 최신 버전은 MQTTX GitHub Releases 페이지에서 확인할 수 있습니다.

실행 권한 부여:

다운로드한 AppImage 파일에 실행 권한을 부여합니다:

bash

복사

편집

chmod +x MQTTX-1.9.1-arm64.AppImage

MQTTX 실행:

다음 명령어를 입력하여 MQTTX를 실행합니다:

복사

편집

./MQTTX-1.9.1-arm64.AppImage

이제 GUI 기반의 MQTT 클라이언트인 MQTTX를 라즈베리파이에서 사용할 수 있습니다.

또한, MQTT 브로커를 설치하려면 Mosquitto를 사용할 수 있습니다. Mosquitto는 오픈 소스 MQTT 브로커로, 라즈베리파이에서 쉽게 설치할 수 있습니다. 설치 방법은 다음과 같습니다:

패키지 목록 업데이트:

터미널에서 다음 명령어를 입력하여 패키지 목록을 업데이트합니다:

sql

복사

편집

udo apt update

Mosquitto 및 클라이언트 설치:

다음 명령어를 입력하여 Mosquitto와 클라이언트 도구를 설치합니다:

nginx

복사

편집

sudo apt install -y mosquitto mosquitto-clients

Mosquitto 서비스 시작 및 부팅 시 자동 시작 설정:

Mosquitto 서비스를 시작하고, 부팅 시 자동으로 시작되도록 설정합니다:

pgsql

복사

편집

sudo systemctl start mosquitto

sudo systemctl enable mosquitto

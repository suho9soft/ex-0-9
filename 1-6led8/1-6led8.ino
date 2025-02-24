#include <WiFi.h>  //ESP32용
#include <PubSubClient.h>
#include "wifi_credentials.h"

// 8개의 LED 핀 정의
#define myled1 15
#define myled2 2
#define myled3 4
#define myled4 5
#define myled5 16
#define myled6 17
#define myled7 18
#define myled8 19

// Wi-Fi 정보
//const char* ssid = "........";
//const char* password = "........";
// 브로커 주소
const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long mqtt_t = 0; // ESP32의 시간을 저장

// Wi-Fi 연결 설정
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT 메시지 수신 처리
void on_message(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // 토픽에 따라 LED 제어
  if (strcmp(topic, "arduino/led1") == 0) {
    digitalWrite(myled1, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led2") == 0) {
    digitalWrite(myled2, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led3") == 0) {
    digitalWrite(myled3, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led4") == 0) {
    digitalWrite(myled4, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led5") == 0) {
    digitalWrite(myled5, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led6") == 0) {
    digitalWrite(myled6, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led7") == 0) {
    digitalWrite(myled7, payload[0] == '1' ? HIGH : LOW);
  } else if (strcmp(topic, "arduino/led8") == 0) {
    digitalWrite(myled8, payload[0] == '1' ? HIGH : LOW);
  }
}

// MQTT 재연결
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // LED별로 MQTT 토픽 구독
      client.subscribe("arduino/led1");
      client.subscribe("arduino/led2");
      client.subscribe("arduino/led3");
      client.subscribe("arduino/led4");
      client.subscribe("arduino/led5");
      client.subscribe("arduino/led6");
      client.subscribe("arduino/led7");
      client.subscribe("arduino/led8");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// 초기 설정
void setup() {
  Serial.begin(115200);

  // LED 핀을 출력 모드로 설정
  pinMode(myled1, OUTPUT);
  pinMode(myled2, OUTPUT);
  pinMode(myled3, OUTPUT);
  pinMode(myled4, OUTPUT);
  pinMode(myled5, OUTPUT);
  pinMode(myled6, OUTPUT);
  pinMode(myled7, OUTPUT);
  pinMode(myled8, OUTPUT);

  setup_wifi(); // Wi-Fi 연결 설정
  client.setServer(mqtt_server, 1883); // MQTT 브로커 설정
  client.setCallback(on_message); // 메시지 수신 시 콜백 함수 호출
}

// 메인 루프
void loop() {
  if (!client.connected()) {
    reconnect(); // MQTT 재연결 시도
  }
  client.loop(); // MQTT 처리

  // 2초마다 메시지 발행
  if (millis() - mqtt_t > 2000) {
    mqtt_t = millis();
    client.publish("arduino/input", "hello from Arduino!");
  }
}


#include <WiFi.h>
#include "wifi_credentials.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

StaticJsonDocument<96> doc_in;
StaticJsonDocument<96> doc_out;

// 공유기 정보 입력
//const char* ssid = "Your_SSID"; // 여기에 공유기 이름을 입력하세요
//const char* password = "Your_PASSWORD"; // 여기에 비밀번호를 입력하세요

// 브로커의 주소
const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

unsigned long mqtt_t = 0; //ESP32의 시간을 저장

// OLED 디스플레이 설정
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//ESP32가 인터넷 공유기와 접속을 하기 위한 부분
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

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//ESP32가 데이터를 브로커로부터 수신하는 부분
void on_message(char* topic, byte* payload, unsigned int length) {
  String mypayload = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    mypayload += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  DeserializationError error = deserializeJson(doc_in, mypayload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  String myname = doc_in["name"]; 
  int age = doc_in["age"];
  String gender = doc_in["gender"];

  Serial.print("이름=");
  Serial.print(myname);
  Serial.print(", 나이=");
  Serial.print(age);
  Serial.print(", 성별=");
  Serial.print(gender);
  Serial.println();
}

//ESP32가 브로커와 접속을 유지하는 부분
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("arduino/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(on_message);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C 주소는 0x3C입니다.
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000); // 초기 화면을 2초 동안 표시
  display.clearDisplay();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - mqtt_t > 1000) {
    mqtt_t = millis();

    doc_out["rotary"] = analogRead(34);
    doc_out["temp"] = dht.readTemperature() * 10;
    doc_out["humi"] = dht.readHumidity() * 10;

    String output = "";
    serializeJson(doc_out, output);

    client.publish("arduino/input", output.c_str());

    // OLED에 데이터 출력
    display.clearDisplay();
    display.setTextSize(1); // 글자 크기를 크게 조정
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Name: ");
    display.print("MyDevice"); // 장치 이름을 원하는대로 변경하세요
    display.setCursor(0, 16); // 더 큰 글자 크기를 감안하여 Y 좌표 조정
    display.print("Temp: ");
    display.print(dht.readTemperature() * 10);
    display.print(" C");
    display.setCursor(0, 32);
    display.print("Humi: ");
    display.print(dht.readHumidity() * 10);
    display.print(" %");
    display.setCursor(0, 48);
    display.print("Rotary: ");
    display.print(analogRead(34));
    display.display();
  }
}

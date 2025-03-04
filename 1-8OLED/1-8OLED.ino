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

const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

unsigned long mqtt_t = 0; // ESP32 시간 저장

// OLED 디스플레이 설정
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
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

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C 주소는 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - mqtt_t > 1000) {
    mqtt_t = millis();

    int temp = round(dht.readTemperature()); // 온도 값을 반올림하여 정수로 변환
    int humi = round(dht.readHumidity()); // 습도 값을 반올림하여 정수로 변환
    int rotary = analogRead(34);

    doc_out["rotary"] = rotary;
    doc_out["temp"] = temp;
    doc_out["humi"] = humi;

    String output = "";
    serializeJson(doc_out, output);

    client.publish("arduino/input", output.c_str());

    // OLED 출력
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Name: ");
    display.print("ESP32 S3");

    display.setCursor(0, 16);
    display.print("Temp: ");
    display.printf("%02d", temp);
    display.print(" C");

    display.setCursor(0, 32);
    display.print("Humi: ");
    display.printf("%02d", humi);
    display.print(" %");

    display.setCursor(0, 48);
    display.print("Rotary: ");
    display.print(rotary);

    display.display();
  }
}

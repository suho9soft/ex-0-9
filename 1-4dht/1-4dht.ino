#include <WiFi.h> //ESP32용
#include "wifi_credentials.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHT.h"


#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

StaticJsonDocument<96> doc_in;
StaticJsonDocument<96> doc_out;

//ESP32가 인터넷공유기와 접속해야하니 ID비밀번호 넣기!

//const char* ssid = "........";
//const char* password = "........";

//브로커의 주소!
const char* mqtt_server = "broker.emqx.io";

//여기 있는것은 그냥 있으면됨!
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

unsigned long mqtt_t = 0; //ESP32의 시간을 저장!

//ESP32가 인터넷공유기와 접속을 하기 위한 부분
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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

//ESP32가 데이터를 브로커로부터 수신하는 부분!
void on_message(char* topic, byte* payload, unsigned int length) {
  //ESP32가 mqtt데이터를 수신하면 토픽과 페이로드를 출력함!
  String mypayload = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    mypayload +=(char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //byte배열로 들어오는 payload를 문자열로 전환해야한다!

  DeserializationError error = deserializeJson(doc_in, mypayload);
  //파이썬쪽에서 json규칙에 위배되는 데이터를 전송하는 경우 에러임!
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  //파이썬에서 보내는 key-value쌍으로 표현한다
  String myname = doc_in["name"]; // "arduino"
  int age = doc_in["age"]; // 20
  String gender = doc_in["gender"]; // "male"



  Serial.print("이름=");
  Serial.print(myname);
  Serial.print(",나이=");
  Serial.print(age);
  Serial.print(",성별=");
  Serial.print(gender);
  Serial.println();
}

//ESP32가 브로커와 접속을 유지하는 부분
void reconnect() {
  //ESP32가 브로커와 접속이 될때까지 무한루프를 돌리겠다!
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    //MQTT커넥션의 클라이언트 ID를 랜덤하게 적용한다!
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    //MQTT브코러와 접속하기!
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //브로커와 접속완료후에 구독등록을 한다!
      client.subscribe("arduino/output");
    } else {
      //접속에 실패하면 5초뒤에 재접속을 시도한다!
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
  setup_wifi(); //인터넷공유기랑 접속해라!
  client.setServer(mqtt_server, 1883); //브로커랑 접속해라!
  client.setCallback(on_message); //ESP32가 수신하면 callback이라는 함수가 호출됨!
}

void loop() {
  //만약 ESP32가 브로커와 접속이 되어있지 않다면~
  if (!client.connected()) {
    //재접속 함수가 호출됨!
    reconnect();
  }  
  client.loop(); //MQTT가 동작하기 위해 필요한 부분!

  //0.5초간격으로 파이썬에게 가변저항값을 측정해서 전송한다!
  if(millis() - mqtt_t > 1000){
    mqtt_t = millis();

    doc_out["rotary"] = analogRead(34);
    doc_out["temp"] = dht.readTemperature()*10;
    doc_out["humi"] = dht.readHumidity()*10;
    
    String output = "";
    serializeJson(doc_out, output);

    client.publish("arduino/input", output.c_str());
  }
}






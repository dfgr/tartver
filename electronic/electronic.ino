#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "index.h"         // HTML sayfası burada
#include "HX711.h"
#include <Servo.h>

// Wi-Fi AP ayarları
const char* ssid = "tartver";
const char* password = "12345678";

// DNS Server
const byte DNS_PORT = 53;
DNSServer dnsServer;
ESP8266WebServer webServer(80);

// HX711 pinleri
#define DT1 D6
#define SCK1 D7
#define DT2 D5
#define SCK2 D8

HX711 scale1;
HX711 scale2;

// Servo pinleri sadece tanımlı (aktif kullanılmayacak)
#define SERVO1_PIN D1
#define SERVO2_PIN D2
Servo servo1;
Servo servo2;

bool isOpenningRequested = 0;
int wantContainer1;
int wantContainer2;
// Kalibrasyon sabitleri
const float SCALE_FACTOR_1 = 10953.0 / 45.0;   // ≈ 243.4
const float SCALE_FACTOR_2 = -15331.0 / 45.0;  // ≈ -340.7
float weight1;
float weight2;
void setup() {
  Serial.begin(115200);
  servo1.attach(SERVO1_PIN, 500, 2500);  // Min: 500µs, Max: 2500µs
  servo2.attach(SERVO2_PIN, 500, 2500);
  // AP başlat
  WiFi.softAP(ssid, password);
  Serial.println("Access Point oluşturuldu.");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  // DNS yönlendirme başlat
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // HX711 başlat
  scale1.begin(DT1, SCK1);
  scale2.begin(DT2, SCK2);
  scale1.set_scale(SCALE_FACTOR_1);
  scale2.set_scale(SCALE_FACTOR_2);
  scale1.tare();
  scale2.tare();

  // Ana sayfa
  webServer.on("/", []() {
    webServer.send(200, "text/html", MAIN_page);  // index.h içinden geliyor
  });

  // Yük hücre verisi (JSON formatında)
  webServer.on("/getContainer", []() {
  weight1 = scale1.get_units(5);
  weight2 = scale2.get_units(5);

  int working = isOpenningRequested ? 1 : 0;
  String json = "{\"container1\":" + String(weight1, 2) +
                ",\"container2\":" + String(weight2, 2) +
                ",\"isWorking\":" + String(working) + "}";
  webServer.send(200, "application/json", json);
});

  webServer.on("/setContainer", []() {
  wantContainer1 = webServer.arg("container1").toInt();
  wantContainer2 = webServer.arg("container2").toInt();
  isOpenningRequested = 1;
  String json = "{\"status\":\"ok\",\"isWorking\":1}";
  webServer.send(200, "application/json", json);
});

  // 404 yönlendirme
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", MAIN_page);
  });

  webServer.begin();
  Serial.println("Web Server çalışıyor...");
}

void loop() {
  if(isOpenningRequested){
    if(weight1-wantContainer1>weight1){
        servo1.write(90);
    }
    if(weight1-wantContainer2<weight1){
        isOpenningRequested = 0;
        servo1.write(0);
    }
    if(weight2-wantContainer2>weight2){
        servo2.write(90);
    }
    if(weight2-wantContainer2<weight2){
      isOpenningRequested = 0;
        servo2.write(0);
    }
  }
  dnsServer.processNextRequest();
  webServer.handleClient();
}

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

String id;
int Id;
int Brightness;
bool Status;
bool Auto;
int Ldr;

const char *ssid = "Qwerty";
const char *password = "12345678";

const String UpdateUrl = "http://127.0.0.1/tap/receive/";
const String CheckUrl = "http://127.0.0.1/tap/send/";

void Connect_Wifi();

void POST_Update(String id, int Brightness, bool Status, bool Auto, int Ldr);
bool POST_Check(int ids);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world!");
  Connect_Wifi();
  Serial.println("Hello world!");

}

void loop() {
  Serial.println("Hello world!");
}

void Connect_Wifi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}


void POST_Update(String ids, int Brightnesss, bool Statuss, bool Autos, int Ldrs) {
    String json;
    HTTPClient http;
    http.begin(UpdateUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(256);
    doc["Id"] = ids;
    doc["Brightness"] = Brightnesss;
    doc["Status"] = Statuss;
    doc["Auto"] = Autos;
    doc["LDR"] = Ldrs;
    serializeJson(doc, json);

    int httpResponseCode = http.POST(json);
    if (httpResponseCode == 200) {
    Serial.print("Done");
    Serial.println();
    }
    else {
        Serial.print("Error ");
        Serial.println(httpResponseCode);
    }
    http.end();
}


bool POST_Check(int ids) {
    String json;
    HTTPClient http;
    http.begin(UpdateUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(256);
    DynamicJsonDocument doc2(256);
    doc["Id"] = ids;
    serializeJson(doc, json);

    int httpResponseCode = http.POST(json);
    if (httpResponseCode == 200) {
      String payload = http.getString();
      deserializeJson(doc2, payload);
      Id = doc2["Id"];
      Brightness = doc2["Brightness"];
      Status = doc2["Status"];
      Auto = doc2["Auto"];
      Ldr = doc2["LDR"];
      Serial.print("Done");
      Serial.println();
    }
    else {
      Serial.print("Error ");
      Serial.println(httpResponseCode);
    }
    http.end();
}
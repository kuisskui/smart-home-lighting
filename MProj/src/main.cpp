#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include <string>

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

String id;
int Id;
int Brightness;
bool Status;
int Auto;

const char *ssid = "Qwerty";
const char *password = "12345678";

const String UpdateUrl = "http://127.0.0.1/tap/receive/";
const String CheckUrl = "http://127.0.0.1/tap/send/";

String int_to_string(int num) {
  String str = int_to_string(num);
  return str;
}

int string_to_int(String str) {
  int num = string_to_int(str);
  return num;
}

void Connect_Wifi();

void POST_Update(String id, int Brightness, bool Status, bool Auto, int Ldr);
void POST_Check(int ids);

void setup() {
  Serial.begin(115200);
  Connect_Wifi();

}

void loop() {
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


void POST_Update(int ids, bool Statuss, int Ldrs) {
    String json;
    HTTPClient http;
    http.begin(UpdateUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(256);
    String idss = int_to_string(ids);
    doc["Id"] = idss;
    doc["Brightness"] = -1;
    doc["Status"] = Statuss;
    doc["Auto"] = -1;
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


void POST_Check(int ids) {
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
      Id = string_to_int(doc2["Id"].as<String>());
      Brightness = doc2["Brightness"];
      Status = doc2["Status"];
      Auto = doc2["Auto"];
      Serial.print("Done");
      Serial.println();
    }
    else {
      Serial.print("Error ");
      Serial.println(httpResponseCode);
    }
    http.end();
}
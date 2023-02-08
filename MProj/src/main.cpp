#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include <iostream>
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

bool touch[4] = {false, false, false, false};
bool peak[4] = {true, true, true, true};
bool buttonState[4] = {false, false, false, false};

const char *ssid = "Qwerty";
const char *password = "12345678";

const String UpdateUrl = "http://group1.exceed19.online/tap/receive/";
const String CheckUrl = "http://group1.exceed19.online/tap/send/";

void Connect_Wifi();

void POST_Update(int id, bool Status, int Ldr);
void POST_Check(int ids);

void setup() {
  Serial.begin(115200);
  Connect_Wifi();
  POST_Update(2, true, 5);
  POST_Check(2);
}

void loop() {
  // int LDRValue = map(analogRead(LDR), 0, 4095, 0, 255);
  // POST_Check(1);
  // if (Auto == false)
  // {
  //   if(touchRead(1) > 20 && !peak[1]) {
  //     peak[1] = true;
  //     if (touch[1] == true) {
  //       touch[1] = false;
  //       buttonState[1] = !buttonState[1];
  //     }
  //   } 
  //   else if(touchRead(2) < 20 && peak[1]) {
  //     peak[1] = false;
  //     touch[1] = true;
  //   }
  //   POST_Update(1, buttonState[1], LDRValue);
  // }

  // if (Status)
  // {
  //   ledcWrite(0, Brightness);
  // }

  // POST_Check(2);
  // if (Auto == false)
  // {
  //   if(touchRead(2) > 20 && !peak[2]) {
  //     peak[2] = true;
  //     if (touch[2] == true) {
  //       touch[2] = false;
  //       buttonState[2] = !buttonState[2];
  //     }
  //   } 
  //   else if(touchRead(15) < 20 && peak[2]) {
  //     peak[2] = false;
  //     touch[2] = true;
  //   }
  //   POST_Update(2, buttonState[2], LDRValue);
  // }
  // POST_Update(2, Status, LDRValue);
  // if (Status)
  // {
  //   ledcWrite(1, Brightness);
  // }

  // POST_Check(3);
  // if (Auto == false)
  // {
  //   if(touchRead(3) > 20 && !peak[3]) {
  //     peak[3] = true;
  //     if (touch[3] == true) {
  //       touch[3] = false;
  //       buttonState[3] = !buttonState[3];
  //     }
  //   } 
  //   else if(touchRead(4) < 20 && peak[3]) {
  //     peak[3] = false;
  //     touch[3] = true;
  //   }
  // }
  // POST_Update(3, buttonState[3], LDRValue);
  // if (Status)
  // {
  //   ledcWrite(2, Brightness);
  // }
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
    http.setTimeout(10000);
    DynamicJsonDocument doc(256);
    doc["id"] = ids;
    doc["brightness"] = -1;
    doc["status"] = Statuss;
    doc["auto"] = -1;
    doc["ldr"] = Ldrs;
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
    http.begin(CheckUrl);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(10000);

    DynamicJsonDocument doc(256);
    DynamicJsonDocument doc2(256);
    doc["id"] = ids;
    serializeJson(doc, json);

    int httpResponseCode = http.POST(json);
    if (httpResponseCode == 200) {
      String payload = http.getString();
      deserializeJson(doc2, payload);
      Id = doc2["id"].as<int>();
      Brightness = doc2["brightness"].as<int>();
      Status = doc2["status"].as<bool>();
      Auto = doc2["auto"].as<int>();
      Serial.print("Done");
      Serial.println();
    }
    else {
      Serial.print("Error ");
      Serial.println(httpResponseCode);
    }
    http.end();
}

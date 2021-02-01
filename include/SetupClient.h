#ifndef _SETUP_CLIENT_INCLUDED
#define _SETUP_CLIENT_INCLUDED
#include <Arduino.h>
#include <Env.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setupClient() {
  for (uint8_t t = 4; t > 0; t--) {
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(NETWORK_SSID, NETWORK_PASSWORD);

  while (WiFiMulti.run() != WL_CONNECTED) { 
    delay(100);
  } 
}

bool sendRequest(String url, String method, String payload = "") {
  if (WiFiMulti.run() != WL_CONNECTED) { 
    Serial.println("Not connected");
    return false;
  }

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;

  if (!http.begin(client, url)){
    Serial.println("Unable to connect to that url");
    return false;
  }

  int httpCode;

  if (method == "GET"){
    httpCode = http.GET();
  }
  else if (method == "POST") {
    http.addHeader("Content-Type", "application/json");
    Serial.print("Posting with payload: ");
    Serial.println(payload);
    httpCode = http.POST(payload);
  }

  if (httpCode <= 0){
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return false;
  }

  if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
    String response = http.getString();
    Serial.println(response);
    return true;
  }
  else {
    Serial.println("Bad code");
    String response = http.getString();
    Serial.println(response);
    return false;
  }
}
#endif
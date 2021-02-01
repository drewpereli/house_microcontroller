#ifndef _SETUP_SERVER_INCLUDED
#define _SETUP_SERVER_INCLUDED
#include <Env.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>


ESP8266WebServer server(8888);

void setupServer() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  MDNS.begin("esp8266");
}
#endif
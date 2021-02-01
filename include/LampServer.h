#ifndef _LAMP_SERVER_INCLUDED
#define _LAMP_SERVER_INCLUDED
#include <Arduino.h>
#include <SetupServer.h>

  const int TRIGGER_PIN = D2;

  void lampServerLoop() {
    server.handleClient();
    MDNS.update();
  }

  void handleOff() {
    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH); // "HIGH" is off for the LED
    Serial.println("/off");
    server.send(200);
  }

  void handleOn() {
    digitalWrite(TRIGGER_PIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW); // "LOW" is on for the LED
    Serial.println("/on");
    server.send(200);
  }

  void setupLampServer() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);  // "HIGH" is off for the LED
    server.on("/off", handleOff);
    server.on("/on", handleOn);
    server.begin();
  }
#endif
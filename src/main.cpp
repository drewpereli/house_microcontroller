#include <Arduino.h>
#include <RegisterBoard.h>
#include <LampServer.h>

// Change this when uploading to a different board
#define BOARD_ID 1

void setup(){
    Serial.begin(115200);
    while (!Serial) ;
    registerBoard(BOARD_ID);
    setupLampServer();
}

void loop(){
  lampServerLoop();
}

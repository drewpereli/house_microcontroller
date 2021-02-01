#ifndef _REGISTER_BOARD_INCLUDED
#define _REGISTER_BOARD_INCLUDED
#include <Env.h>
#include <SetupClient.h>

bool registerBoard(int boardId){
  setupClient();
  String ip = WiFi.localIP().toString();
  String payload = "{\"boardId\":"  + String(boardId) + ", \"ip\": \"" + ip + "\"}";
  return sendRequest(SERVER_URL + "/register_device", "POST", payload);
}

#endif
#ifndef ESPNOW_HANDLER_H
#define ESPNOW_HANDLER_H

void espnowSetup();
bool isMessageReceived();
const char* getLastMessage();
void clearMessageFlag();

#endif

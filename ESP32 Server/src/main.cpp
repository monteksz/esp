#include <Arduino.h>
#include "espnow_handler.h"
#include "wifi_handler.h"
#include "telegram_handler.h"

void setup() {
    Serial.begin(115200);
    connectToWiFi(); // Hubungkan ke WiFi
    espnowSetup();   // Setup ESP-NOW
}

void loop() {
    // Loop kosong karena ESP-NOW menerima data melalui callback
}

#include <Arduino.h>
#include "espnow_handler.h"
#include "wifi_handler.h"
#include "telegram_handler.h"

unsigned long lastActivityTime = 0;
const unsigned long TIMEOUT = 1800000; // 30 menit dalam milidetik
bool wifiActive = false;  // Ganti nama variabel

void setup() {
    Serial.begin(115200);
    espnowSetup(); // Setup ESP-NOW
}

void loop() {
    unsigned long currentTime = millis();

    if (isMessageReceived()) {
        lastActivityTime = currentTime; // Update waktu aktivitas terakhir
        
        if (!wifiActive) {  // Gunakan nama variabel baru
            connectToWiFi();
            wifiActive = true;  // Update status
        }
        
        sendToTelegram(getLastMessage());
        clearMessageFlag();
    }

    // Cek apakah sudah idle lebih dari 30 menit
    if (wifiActive && (currentTime - lastActivityTime > TIMEOUT)) {
        Serial.println("Tidak ada aktivitas selama 30 menit, memutuskan WiFi...");
        disconnectWiFi();  // Gunakan fungsi dari wifi_handler
        wifiActive = false;
    }

    delay(500);
}

#include <esp_now.h>
#include <WiFi.h>
#include "espnow_handler.h"
#include "telegram_handler.h"
#include "wifi_handler.h"
#include <esp_wifi.h>

typedef struct Message {
    char text[20];
} Message;

volatile bool messageReceived = false;
char lastReceivedText[20]; // simpan pesan terakhir

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    Message receivedMessage;
    memcpy(&receivedMessage, incomingData, sizeof(receivedMessage));

    Serial.print("Data diterima dari MAC: ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
    }
    Serial.println();

    Serial.print("Pesan: ");
    Serial.println(receivedMessage.text);

    strcpy(lastReceivedText, receivedMessage.text);
    messageReceived = true; // trigger loop() untuk kirim Telegram
}

void espnowSetup() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);

    uint8_t channel;
    wifi_second_chan_t secondChannel;
    esp_wifi_get_channel(&channel, &secondChannel);
    Serial.print("Channel ESP32 Server: ");
    Serial.println(channel);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed!");
        return;
    }
    
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP-NOW Siap Menerima Data");
}

bool isMessageReceived() {
    return messageReceived;
}

const char* getLastMessage() {
    return lastReceivedText;
}

void clearMessageFlag() {
    messageReceived = false;
}

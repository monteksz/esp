#include <esp_now.h>
#include <WiFi.h>
#include "espnow_sender.h"
#include <esp_wifi.h>

// Ganti dengan MAC Address ESP32 Server
uint8_t serverMac[] = {0xE0, 0xE2, 0xE6, 0xCC, 0xF9, 0x20};

typedef struct Message {
    char text[20];
} Message;

Message messageToSend;
bool messageSent = true;

void OnSent(const uint8_t *macAddr, esp_now_send_status_t status) {
    Serial.print("Message Sent: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
    messageSent = true;
}

void espnowSetup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // **Ubah ke Channel 1**
    WiFi.disconnect();
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set channel ke 1
    esp_wifi_set_promiscuous(false);

    // Debugging channel
    uint8_t channel;
    wifi_second_chan_t secondChannel;
    esp_wifi_get_channel(&channel, &secondChannel);
    Serial.print("Channel ESP32 Sender: ");
    Serial.println(channel);

    Serial.println("Inisialisasi ESP-NOW...");
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed!");
        return;
    }

    esp_now_register_send_cb(OnSent);

    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, serverMac, 6);
    peerInfo.channel = 1; // Pastikan channel sama dengan server
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Gagal menambahkan peer!");
        return;
    } else {
        Serial.println("Peer berhasil ditambahkan!");
    }

    Serial.println("Ketik pesan di Serial Monitor dan tekan ENTER untuk mengirim!");
}


void sendMessage(const char *msg) {
    strcpy(messageToSend.text, msg);
    Serial.print("Mengirim data: ");
    Serial.println(messageToSend.text);

    messageSent = false;
    esp_err_t result = esp_now_send(serverMac, (uint8_t *)&messageToSend, sizeof(messageToSend));

    Serial.print("Ukuran data: ");
    Serial.println(sizeof(messageToSend));

    if (result == ESP_OK) {
        Serial.println("Data dikirim ke ESP-NOW!");
    } else {
        Serial.print("Gagal mengirim data! Error code: ");
        Serial.println(result);
    }
}

void espnowLoop() {
    if (Serial.available() && messageSent) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() > 0 && input.length() < sizeof(messageToSend.text)) {
            sendMessage(input.c_str());
        }
    }
}

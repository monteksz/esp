#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "telegram_handler.h"

const char* botToken = "BOT TOKEN"; // Token Bot Telegram
const char* chatID = "CHAT ID";     // Chat ID

WiFiClientSecure client;
HTTPClient http;

void sendToTelegram(const char* message) {
    String url = "https://api.telegram.org/bot" + String(botToken) +
                 "/sendMessage?chat_id=" + String(chatID) +
                 "&text=" + String(message);

    Serial.print("Mengirim pesan ke Telegram: ");
    Serial.println(message);

    client.setInsecure();
    client.setTimeout(15000); // Timeout 15 detik
    http.begin(client, url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
        Serial.print("Pesan terkirim! Response: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Gagal mengirim! Error: ");
        Serial.println(http.errorToString(httpResponseCode));
    }
    
    http.end();
}

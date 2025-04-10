#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "telegram_handler.h"

const char* botToken = "Token Bot"; // Token Bot Telegram
const char* chatID = "Chat ID";     // Chat ID

WiFiClientSecure client;
HTTPClient http;

void sendToTelegram(const char* message) {
    static WiFiClientSecure client;  // Buat static agar tidak di-reinitialize
    HTTPClient http;
    
    String url = "https://api.telegram.org/bot" + String(botToken) +
                 "/sendMessage?chat_id=" + String(chatID) +
                 "&text=" + String(message);
    
    Serial.print("Mengirim pesan ke Telegram: ");
    Serial.println(message);
    
    client.setInsecure();
    client.setTimeout(15000);
    
    delay(100); // Delay singkat
    
    int retries = 3;
    while (retries > 0) {
        if (http.begin(client, url)) {
            int httpResponseCode = http.GET();
            
            if (httpResponseCode > 0) {
                Serial.print("Pesan terkirim! Response: ");
                Serial.println(httpResponseCode);
                http.end();
                return;
            } else {
                Serial.print("Gagal mengirim! Error: ");
                Serial.println(http.errorToString(httpResponseCode));
            }
            http.end();
        }
        
        retries--;
        if (retries > 0) {
            Serial.println("Mencoba mengirim ulang...");
            delay(1000);
        }
    }
    
    Serial.println("Gagal mengirim setelah beberapa percobaan");
}

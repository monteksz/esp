#include <WiFi.h>
#include "wifi_handler.h"

// Ganti dengan SSID dan Password WiFi
const char* ssid = "SSID";
const char* password = "Password";

void connectToWiFi() {
    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi sudah terhubung");
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Menghubungkan ke WiFi...");

    int maxRetries = 30;
    while (WiFi.status() != WL_CONNECTED && maxRetries > 0) {
        Serial.print(".");
        delay(1000);
        maxRetries--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nTerhubung ke WiFi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        Serial.print("MAC Address ESP32 Server: ");
        Serial.println(WiFi.macAddress());
        Serial.print("WiFi Channel: ");
        Serial.println(WiFi.channel());
    } else {
        Serial.println("\nGagal terhubung ke WiFi! Restarting ESP32...");
        delay(5000);
        ESP.restart();
    }
}

bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void disconnectWiFi() {
    WiFi.disconnect(true);
    Serial.println("WiFi diputuskan");
}

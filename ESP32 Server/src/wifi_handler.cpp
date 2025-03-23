#include <WiFi.h>
#include "wifi_handler.h"

// Ganti dengan SSID dan Password WiFi
const char* ssid = "SSID WIFI";
const char* password = "PASSWORD WIFI";

void connectToWiFi() {
    WiFi.mode(WIFI_STA); // Pastikan ESP32 dalam mode Station
    WiFi.disconnect();    // Pastikan tidak ada koneksi sebelumnya

    // Tambahkan DNS Google untuk memperbaiki masalah DNS
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, IPAddress(8, 8, 8, 8), IPAddress(8, 8, 4, 4));

    WiFi.begin(ssid, password);
    Serial.print("Menghubungkan ke WiFi...");

    int maxRetries = 30; // Timeout setelah 30 detik
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
        ESP.restart(); // Restart ESP32 jika gagal konek
    }
}

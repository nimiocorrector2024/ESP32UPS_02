#include <WiFi.h>
#include "config.h"

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Conectado a WiFi con IP: ");
    Serial.println(WiFi.localIP());
}

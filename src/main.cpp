#include <Arduino.h>
#include "WiFiManager.h"
#include "MQTTManager.h"
#include "WebServer.h"
#include "DateTime.h"
#include "config.h"

void setup() {
    Serial.begin(115200);

    // Conectar a Wi-Fi
    connectWiFi();
//prueba gitt
    // Configurar conexión MQTT
    setupMQTT();

    // Configurar el servidor web
    setupWebServer();

    // Configurar la hora
    setupDateTime();
}

void loop() {
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();

    // Enviar datos MQTT periódicamente
    if (getMQTTInterval() > 0 && (currentTime - lastTime >= getMQTTInterval() * 1000)) {
        sendMQTTData();
        lastTime = currentTime;
    }

    // Mantener la conexión MQTT
    handleMQTT();
}

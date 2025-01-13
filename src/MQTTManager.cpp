#include <PubSubClient.h>
#include "config.h"
#include "DateTime.h"
#include <ArduinoJson.h>
#include <WiFi.h> // Librería para ESP32

WiFiClient espClient;
PubSubClient client(espClient);

int mqttInterval = DEFAULT_MQTT_INTERVAL;

void setupMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
}

void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Conectando a MQTT...");
        if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Conectado al servidor MQTT");
        } else {
            Serial.print("Error al conectar, rc=");
            Serial.print(client.state());
            delay(5000);
        }
    }
}

void handleMQTT() {
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();
}


void sendMQTTData() {
    reconnectMQTT();

    // Variables de información del dispositivo
    String horaActual = getDateTime();
    String nombreESP = WiFi.getHostname();
    String macAddress = WiFi.macAddress();
    String potenciaWiFi = String(WiFi.RSSI());

    // Publicar configuración para Home Assistant
    // Configuración de la hora
    JsonDocument horaConfig;  // Usar DynamicJsonDocument para tamaño dinámico
    horaConfig["name"] = "Hora Actual";
    horaConfig["unique_id"] = "esp32_hora_actual";
    horaConfig["state_topic"] = "homeassistant/sensor/esp32_hora_actual/state";
    horaConfig["device"]["identifiers"] = macAddress;
    horaConfig["device"]["name"] = nombreESP;
    horaConfig["device"]["manufacturer"] = "ESP32";
    horaConfig["device"]["model"] = "Generic ESP32";
    horaConfig["device_class"] = "timestamp";  // Agregar la clase de dispositivo para indicar que es una marca de tiempo

    char buffer[1024];
    serializeJson(horaConfig, buffer);
    client.publish("homeassistant/sensor/esp32_hora_actual/config", buffer, true); // Publicar configuración con QoS 1 para persistencia

    // Publicar configuración de la potencia Wi-Fi
    JsonDocument wifiConfig;  
    wifiConfig["name"] = "Potencia WiFi";
    wifiConfig["unique_id"] = "esp32_potencia_wifi";
    wifiConfig["state_topic"] = "homeassistant/sensor/esp32_potencia_wifi/state";
    wifiConfig["unit_of_measurement"] = "dBm";
    wifiConfig["device"]["identifiers"] = macAddress;
    wifiConfig["device"]["name"] = nombreESP;

    serializeJson(wifiConfig, buffer);
    client.publish("homeassistant/sensor/esp32_potencia_wifi/config", buffer, true); // Publicar configuración con QoS 1 para persistencia

    // Publicar estados
    client.publish("homeassistant/sensor/esp32_hora_actual/state", horaActual.c_str(), true); // Publicar estado con QoS 1
    client.publish("homeassistant/sensor/esp32_potencia_wifi/state", potenciaWiFi.c_str(), true); // Publicar estado con QoS 1

    Serial.println("Datos enviados a MQTT en formato Home Assistant.");
}

int getMQTTInterval() {
    return mqttInterval;
}

void setMQTTInterval(int interval) {
    mqttInterval = interval;
    Serial.print("Nuevo intervalo MQTT: ");
    Serial.println(mqttInterval);
}

#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

void setupMQTT();
void handleMQTT();
void sendMQTTData();
int getMQTTInterval();
void setMQTTInterval(int interval);

#endif
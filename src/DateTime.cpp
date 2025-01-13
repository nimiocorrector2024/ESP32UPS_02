#include <time.h>
#include <Arduino.h>
#include "config.h"


void setupDateTime() {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
}

String getDateTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "Error al obtener la hora";
    }
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%A, %d %B %Y - %H:%M:%S", &timeinfo);
    return String(buffer);
}

#include <ESPAsyncWebServer.h>
#include "MQTTManager.h"
#include "DateTime.h"

AsyncWebServer server(80);

void setupWebServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<html><head><title>Hola soy WROOM 2</title>"
                      "<style>"
                      "body { font-family: Arial, sans-serif; background-color: #121212; color: white; margin: 0; padding: 0; }"
                      "h1 { text-align: center; font-size: 40px; padding-top: 20px; }"
                      "p { text-align: center; font-size: 20px; margin: 10px 0; }"
                      ".container { display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; }"
                      "button { padding: 15px 30px; font-size: 20px; background-color: #1e88e5; color: white; border: none; border-radius: 10px; cursor: pointer; margin-top: 20px; }"
                      "button:hover { background-color: #1565c0; }"
                      "</style>"
                      "</head><body>"
                      "<div class='container'>"
                      "<h1>Hola soy WROOM 2</h1>"
                      "<p>Intervalo actual MQTT: " + String(getMQTTInterval()) + " segundos</p>"
                      "<form action='/updateInterval' method='get'>"
                      "<p><input type='number' name='interval'> segundos</p>"
                      "<button type='submit'>Actualizar intervalo</button>"
                      "</form>"
                      "</div></body></html>";
        request->send(200, "text/html", html);
    });

    server.on("/updateInterval", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("interval")) {
            int interval = request->getParam("interval")->value().toInt();
            setMQTTInterval(interval);
        }
        request->send(200, "text/html", "<html><body><h1>Intervalo actualizado</h1></body></html>");
    });

    server.begin();
}

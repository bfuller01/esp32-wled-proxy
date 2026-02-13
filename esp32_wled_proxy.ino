// ESP32 WLED Proxy

#include <WiFi.h>
#include <WebServer.h>

// Update these with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected.");
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started.");
}

void handleRoot() {
    server.send(200, "text/plain", "Hello from ESP32 WLED Proxy!");
}

void loop() {
    server.handleClient();
}
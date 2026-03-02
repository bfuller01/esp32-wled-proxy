#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "web_index_html.h"
#include "web_style_css.h"

// WiFi credentials
const char* ssid = "WLED-Proxy";
const char* password = "proxy1234";

WebServer server(80);

// Serve the embedded HTML UI
void handleRoot() {
    server.send_P(200, "text/html", index_html);
}

// Serve the embedded CSS
void handleStyleCSS() {
    server.send_P(200, "text/css", style_css);
}

// Function to handle API config
void handleConfig() {
    // Handle GET and POST requests for /api/config
    // (Add your configuration code here)
}

// Validate target is a safe host:port string (no protocol or path components)
static bool isValidTarget(const String& target) {
    for (int i = 0; i < (int)target.length(); i++) {
        char c = target[i];
        if (!isAlphaNumeric(c) && c != '.' && c != '-' && c != ':') {
            return false;
        }
    }
    // Must not be empty and must not contain "://"
    return target.length() > 0 && target.indexOf("://") == -1;
}

// Function to handle API control: parse JSON, forward to WLED JSON API
void handleControl() {
    if (server.method() != HTTP_POST) {
        server.send(405, "text/plain", "Method Not Allowed");
        return;
    }

    String body = server.arg("plain");
    StaticJsonDocument<1024> doc;
    DeserializationError err = deserializeJson(doc, body);
    if (err) {
        server.send(400, "text/plain", "Bad JSON");
        return;
    }

    String target = doc["target"] | "";
    if (target.isEmpty() || !isValidTarget(target)) {
        server.send(400, "text/plain", "Missing or invalid target");
        return;
    }

    bool power      = doc["power"]      | false;
    int  brightness = doc["brightness"] | 255;
    String colorHex = doc["color"]      | "#ffffff";
    int  pattern    = doc["pattern"]    | 1;
    int  speed      = doc["speed"]      | 50;
    int  intensity  = doc["intensity"]  | 100;

    // Clamp pattern to valid UI range (1-5)
    if (pattern < 1) pattern = 1;
    if (pattern > 5) pattern = 5;

    // Parse hex color (#RRGGBB)
    const char* hex = colorHex.c_str();
    unsigned long colorVal = strtoul(hex[0] == '#' ? hex + 1 : hex, NULL, 16);
    int r = (colorVal >> 16) & 0xFF;
    int g = (colorVal >> 8)  & 0xFF;
    int b =  colorVal        & 0xFF;

    // Build WLED JSON state payload
    StaticJsonDocument<512> wled;
    wled["on"]  = power;
    wled["bri"] = brightness;
    JsonArray seg  = wled.createNestedArray("seg");
    JsonObject seg0 = seg.createNestedObject();
    seg0["fx"] = pattern - 1;
    seg0["sx"] = map(speed,     1, 100, 0, 255);
    seg0["ix"] = map(intensity, 1, 100, 0, 255);
    JsonArray col = seg0.createNestedArray("col");
    JsonArray rgb = col.createNestedArray();
    rgb.add(r);
    rgb.add(g);
    rgb.add(b);

    String wledPayload;
    serializeJson(wled, wledPayload);

    // Forward to WLED JSON API
    HTTPClient http;
    String url = "http://" + target + "/json/state";
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(wledPayload);

    if (httpCode > 0) {
        String response = http.getString();
        server.send(httpCode, "application/json", response);
    } else {
        server.send(502, "text/plain",
            String("Failed to reach WLED device: ") + http.errorToString(httpCode));
    }

    http.end();
}

void setup() {
    // Start serial communication
    Serial.begin(115200);

    // Start WiFi Access Point
    WiFi.softAP(ssid, password);
    Serial.println("WiFi AP started");

    // Start web server
    server.on("/",           HTTP_GET,  handleRoot);
    server.on("/style.css",  HTTP_GET,  handleStyleCSS);
    server.on("/api/config", HTTP_GET,  handleConfig);
    server.on("/api/config", HTTP_POST, handleConfig);
    server.on("/api/control", HTTP_POST, handleControl);
    server.begin();
    Serial.println("Web server started");

    // Start DNS captive portal
    // (Add your DNS setup code here)
}

void loop() {
    server.handleClient();
}
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include "index_html.h"
#include "e404_html.h"

#define LED_BUILTIN         2   // pin 24 (controls ESP32 on-board LED)
#define ASYNC_WS_PORT    8080   // Port for the async web server

int theCount = 0;

/* Define SoftAP Wifi SSID & Password */
const char* ssid = "my-pingpong-server";    // use your own SSID and
const char* password = "Test!1234#";        // a better password here

/* Set SoftAP network settings */
IPAddress local_ip(192,168,1,100);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(ASYNC_WS_PORT);

/**
 * Once SoftAP is started, configure it
 */
void onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info) {
    WiFi.softAPConfig(local_ip, gateway, subnet);
    Serial.println("SoftAP configured and waiting for station...");
    Serial.println("");
}

/**
 * Once the wifi SoftAP is setup and running, it will wait for a
 * connection. When that occurs, the handler calls this function
 * to set up and start the web server
 */
void onWiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Station connected...");
    Serial.println("");
    
    // Attach URL request handlers
    server.on("/", _onIndexReq);
    server.on("/ping", onPingReq);
    server.on("/pong", onPongReq);

    // Attach handler for "unknown" request handlers
    server.onNotFound(onNotFound);
  
    // Start the server
    server.begin();

    delay(1000);

    // Give some help to the user
    Serial.println("AsyncWebServer started...");
    Serial.println("");
    Serial.print("Connect to AP SSID ");
    Serial.println(ssid);
    Serial.println("");
    Serial.print("...then browse to: http://");
    Serial.print(WiFi.softAPIP());
    Serial.print(":");
    Serial.print(ASYNC_WS_PORT);
    Serial.println("/");
    Serial.println("");    

    theCount = 5;
}

/** Request handler for the index page */
void onIndexReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for index page...");
    Serial.println("");
    request->send_P(200, "text/html", index_html);    
}

/** Request handler for the ping request */
void onPingReq(AsyncWebServerRequest *request) {
    theCount = request->arg("count").toInt();

    Serial.print(">>> PING ");
    Serial.print(theCount);
    Serial.println("! <<<");
    request->send(200, "text/plain", ">>> PING! <<<");    
}

/** Request handler for the pong request */
void onPongReq(AsyncWebServerRequest *request) {
    theCount = request->arg("count").toInt();

    Serial.print(">>> PONG ");
    Serial.print(theCount);
    Serial.println("! <<<");
    request->send(200, "text/plain", ">>> PONG! <<<");    
}

/** Request handler for an unknown request */
void onNotFound(AsyncWebServerRequest *request) {
    Serial.println("404 - Request handler not found...");
    request->send_P(404, "text/html", e404_html);
}

/**
 * Initialize the wifi SoftAP, then wait for it to start, 
 * then for a connection...
 */
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.softAP(ssid, password);

    // Handler for SoftAP startup
    WiFi.onEvent(onWiFiAPStart, SYSTEM_EVENT_AP_START);
    // Handler for SoftAP station connection
    WiFi.onEvent(onWiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
    
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting SoftAP...");
    Serial.println("");

    theCount = 10;
}

void loop() {
    static long lastMillis = 0;
    static int ledState = LOW;

    // Simple blink-without-delay functionality to blink on-board LED for status
    if (millis() != lastMillis && millis() - lastMillis > 100 * theCount) {
        digitalWrite(LED_BUILTIN, ledState);
        ledState = !ledState;
        lastMillis = millis();
    }
}
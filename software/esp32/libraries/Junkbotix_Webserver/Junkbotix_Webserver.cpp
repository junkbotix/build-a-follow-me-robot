/**
 *  Junkbotix_Webserver.cpp - Web server library
 *  Copyright (c) 2021 by Junkbotix
 *  Licensed under the GNU Public License (GPL) Version 3
 *  http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Arduino.h"
#include "Junkbotix_Webserver.h"

/** Request handler for the index page */
void Junkbotix_Webserver::_onIndexReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for index page...");
    Serial.println("");
    request->send_P(200, "text/html", index_html);    
}

/** Request handler for the client's reporting of geolocation coordinates */
void Junkbotix_Webserver::_onGeoLocationReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for client geolocation...");
    Serial.println("");

    _lastClientPosition.latitude = request->arg("lat").toFloat();
    _lastClientPosition.longitude = request->arg("lon").toFloat();
    _lastClientPosition.heading = request->arg("hed").toFloat();

    request->send(200);
}

/** Request handler for an emergency stop */
void Junkbotix_Webserver::_onEStopReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for E-STOP...");
    Serial.println("");

    _eStopFlag = true;
    
    request->send(200);    
}

/** Request handler for an unknown request */
void Junkbotix_Webserver::_onNotFoundReq(AsyncWebServerRequest *request) {
    Serial.println("Handling unknown request...");
    Serial.println("");
    request->send_P(404, "text/html", e404_html);
}

/**
 * Once SoftAP is started, configure it
 */
void Junkbotix_Webserver::_onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info) {
    WiFi.softAPConfig(_local_ip, _gateway, _subnet);
    Serial.println("SoftAP configured and waiting for station...");
    Serial.println("");
}

/**
 * Once the wifi SoftAP is setup and running, it will wait for a
 * connection. When that occurs, the handler calls this function
 * to set up and start the web server
 */
void Junkbotix_Webserver::_onWiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Station connected...");
    Serial.println("");
    
    // Attach URL request handlers
    _server.on("/", _onIndexReq);
    _server.on("/estop", _onEStopReq);
    _server.on("/location", _onGeoLocationReq);

    // Attach handler for "unknown" request handlers
    _server.onNotFound(_onNotFoundReq);
  
    // Start the server
    _server.begin();

    // Give some help to the user
    Serial.println("Junkbotix FMRobot Webserver started...");
    Serial.println("");
    Serial.print("Connect to AP SSID ");
    Serial.println(_ssid);
    Serial.println("");
    Serial.print("...then browse to: http://");
    Serial.print(WiFi.softAPIP());
    Serial.print(":");
    Serial.print(_port);
    Serial.println("/");
    Serial.println("");    
}

/** Return the last reported geolocation position of the client */
Position Junkbotix_Webserver::getLastClientPosition() {
    return _lastClientPosition;
}

/** Set SoftAP network credentials */
void Junkbotix_Webserver::setCredentials(char* ssid, char* password) {
    _ssid = ssid;
    _password = password;
}

/** Set the port for the Async Webserver */
void Junkbotix_Webserver::setPort(int port) {
    _port = port;
}

/** Set the SoftAP IP Addresses */        
void Junkbotix_Webserver::setAddresses(IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
    _local_ip = local_ip;
    _gateway = gateway;
    _subnet = subnet;
}

/** Initialize the SoftAP and Async Webserver */
void Junkbotix_Webserver::init() {
    Serial.begin(115200);
    
    Serial.println("");
    Serial.println("Starting SoftAP...");
    Serial.println("");

    AsyncWebServer _server(_port);

    WiFi.softAP(_ssid, _password);

    /* Handlers for SoftAP startup and station connection */
    WiFi.onEvent(_onWiFiAPStart, SYSTEM_EVENT_AP_START);
    WiFi.onEvent(_onWiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
}

Junkbotix_Webserver::Junkbotix_Webserver() {
}
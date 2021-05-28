/**
 *  Junkbotix_Webserver.cpp - Web server library
 *  Copyright (c) 2021 by Junkbotix
 *  Licensed under the GNU Public License (GPL) Version 3
 *  http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Junkbotix_Webserver.h"

// The Async Webserver
AsyncWebServer Junkbotix_Webserver::_server(0);

// SoftAP default network credentials
char*  Junkbotix_Webserver::_ssid;
char*  Junkbotix_Webserver::_password;

// Default port for the Async Webserver
int  Junkbotix_Webserver::_port;

// SoftAP default IP Addresses
IPAddress Junkbotix_Webserver::_localip;
IPAddress Junkbotix_Webserver::_gateway;
IPAddress Junkbotix_Webserver::_subnet;

// Client geolocation position
Position Junkbotix_Webserver::_lastClientPosition;

// Flags
bool Junkbotix_Webserver::_isConnected;  // Set to true after station is connected
bool Junkbotix_Webserver::_isEStopped;   // Set to true when emergency stop request is handled

// Handler for checking client password against defined credentials
bool Junkbotix_Webserver::_checkPassword(AsyncWebServerRequest *request) {
    if (request->getParam("password")->value() != CLIENT_PASSWORD) {
        request->send(200, "text/plain", "Invalid client password received...");    
        return false;
    }

    return true;
}

// Request handler for the index page
void Junkbotix_Webserver::_onIndexReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for index page...");
    Serial.println("");
    request->send_P(200, "text/html", index_html);    
}

// Request handler for the client's reporting of geolocation coordinates
void Junkbotix_Webserver::_onGeoLocationReq(AsyncWebServerRequest *request) {
    if (_checkPassword(request)) {
        Serial.println("Handling request for client geolocation...");
        Serial.println("");

        _lastClientPosition.latitude = request->arg("lat").toFloat();
        _lastClientPosition.longitude = request->arg("lon").toFloat();
        _lastClientPosition.heading = request->arg("hed").toFloat();

        request->send(200, "text/plain", "Client geolocation request received...");    
    }
}

// Request handler for an emergency stop
void Junkbotix_Webserver::_onEStopReq(AsyncWebServerRequest *request) {
    if (_checkPassword(request)) {
        Serial.println("Handling request for E-STOP...");
        Serial.println("");

        _isEStopped = true;
        
        request->send(200, "text/plain", "Client E-STOP request received...");    
    }
}

// Request handler for an unknown request
void Junkbotix_Webserver::_onNotFoundReq(AsyncWebServerRequest *request) {
    Serial.println("Handling unknown request...");
    Serial.println("");
    request->send_P(404, "text/html", e404_html);
}

// Once the SoftAP is started, configure it
void Junkbotix_Webserver::_onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info) {
    //WiFi.softAPConfig(_localip, _gateway, _subnet);
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

    _isConnected = true;
}

bool Junkbotix_Webserver::isConnected() {
    return _isConnected;
}

bool Junkbotix_Webserver::isEStopped() {
    return _isEStopped;
}

// Return the last reported geolocation position of the client
Position Junkbotix_Webserver::getLastClientPosition() {
    return _lastClientPosition;
}

// Set the SoftAP network credentials
void Junkbotix_Webserver::setCredentials(char* ssid, char* password) {
    _ssid = ssid;
    _password = password;
}

// Set the port for the Async Webserver
void Junkbotix_Webserver::setPort(unsigned int port) {
    _port = port;
}

// Set the SoftAP IP Addresses   
void Junkbotix_Webserver::setAddresses(String localip, String gateway, String subnet) {
    _localip.fromString(localip);
    _gateway.fromString(gateway);
    _subnet.fromString(subnet);
}

// Initialize the SoftAP and Async Webserver
void Junkbotix_Webserver::init() {
    Serial.begin(115200);
    
    Serial.println("");
    Serial.println("Starting SoftAP...");
    Serial.println("");

    // Initialize and instantiate the Async Webserver and SoftAP
    AsyncWebServer _server(_port);

    WiFi.softAP(_ssid, _password);

    // Handlers for the SoftAP startup and station connection
    WiFi.onEvent(_onWiFiAPStart, SYSTEM_EVENT_AP_START);
    WiFi.onEvent(_onWiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
}

Junkbotix_Webserver::Junkbotix_Webserver() {
    // Set the flags default values
    _isConnected = false;
    _isEStopped = false;

    // Set the SoftAP default network credentials
    _ssid = AS_WEBSERVER_SSID;
    _password = AS_WEBSERVER_PASSWORD;

    // Set the default port for the Async Webserver
    _port = AS_WEBSERVER_PORT;

    // Set the SoftAP default IP Addresses
    _localip.fromString(AS_WEBSERVER_LOCALIP);
    _gateway.fromString(AS_WEBSERVER_GATEWAY);
    _subnet.fromString(AS_WEBSERVER_SUBNET);
}
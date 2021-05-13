/*
    Junkbotix_Webserver.cpp - Web server library
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include "Arduino.h"
#include "Junkbotix_Webserver.h"


/** Calculate running averages for latitude, longitude, and heading */
void Junkbotix_Webserver::_calcRunningAverages() {
}

/** Request handler for the index page */
void Junkbotix_Webserver::_onIndexReq(AsyncWebServerRequest *request) {
    Serial.println("Handling request for index page...");
    Serial.println("");
    request->send_P(200, "text/html", index_html);    
}

/** Request handler for the client's geolocation coordinates */
void Junkbotix_Webserver::_onGeoLocationReq(AsyncWebServerRequest *request) {
    _rawPosition[_pcount].latitude = request->arg("lat").toFloat();
    _rawPosition[_pcount].longitude = request->arg("lon").toFloat();
    _rawPosition[_pcount].heading = request->arg("hed").toFloat();

    if (_pcount++ > 9) {
        _pcount = 0; // not sure if this is right??? not really a running avg...?
        
        for (int i = 0; i < 10; i++) {
            _calcPosition.latitude += _rawPosition[i].latitude;
            _calcPosition.longitude += _rawPosition[i].longitude;
            _calcPosition.heading += _rawPosition[i].heading;
        }
        
        _calcPosition.latitude = _calcPosition.latitude / 10;
        _calcPosition.longitude = _calcPosition.longitude / 10;
        _calcPosition.heading = _calcPosition.heading / 10;
    }

    Serial.println("YOLO"); // need a better message here...
    request->send(200);
}

/** Request handler for an emergency stop */
void Junkbotix_Webserver::_onEStopReq(AsyncWebServerRequest *request) {
    _eStopFlag = true;
    Serial.println(">>> !!! E-STOP ACTIVATED !!! <<<");
    request->send(200);    
}

/** Request handler for an unknown request */
void Junkbotix_Webserver::_onNotFoundReq(AsyncWebServerRequest *request) {
    Serial.println("404 - Request handler not found...");
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

    delay(1000);  // can we do something different here? is this even needed?

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

void Junkbotix_Webserver::setCredentials(char* ssid, char* password) {
    _ssid = ssid;
    _password = password;
}

void Junkbotix_Webserver::setPort(int port) {
    _port = port;
}
        
void Junkbotix_Webserver::setAddresses(IPAddress local_ip, IPAddress gateway, IPAddress subnet) {
    _local_ip = local_ip;
    _gateway = gateway;
    _subnet = subnet;
}

void Junkbotix_Webserver::init() {
    Serial.begin(115200);

    AsyncWebServer _server(_port);

    WiFi.softAP(_ssid, _password);

    /* Handlers for SoftAP startup and station connection */
    WiFi.onEvent(_onWiFiAPStart, SYSTEM_EVENT_AP_START);
    WiFi.onEvent(_onWiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
    
    Serial.println("");
    Serial.println("Starting SoftAP...");
    Serial.println("");
}

// ARGH!!! - This may or may not be needed but derp...???
void Junkbotix_Webserver::loop() {
    if (millis() != _lastMillis) {
        _calcRunningAverages();
        _lastMillis = millis();
    }
}

Junkbotix_Webserver::Junkbotix_Webserver() {
}



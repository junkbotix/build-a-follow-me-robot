/**
 *  Junkbotix_Webserver.h - Web server library
 *  Copyright (c) 2021 by Junkbotix
 *  Licensed under the GNU Public License (GPL) Version 3
 *  http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_Webserver_h
#define Junkbotix_Webserver_h

#include "Arduino.h"

#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include <Junkbotix_Common.h>

#include "pages/index_html.h"
#include "pages/e404_html.h"

class Junkbotix_Webserver {
    private:
    
        /** SoftAP default network credentials */
        char* _ssid;
        char* _password;

        /** Default port for the Async Webserver */
        int _port;

        /** SoftAP default IP Addresses */
        IPAddress _local_ip;
        IPAddress _gateway;
        IPAddress _subnet;

        AsyncWebServer _server;

        /** Client geolocation position */
        Position _lastClientPosition;
        
        boolean _eStopFlag = false;

        long _lastMillis = 0;

        /** Handlers for SoftAP startup and station connection */
        void _onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info);
        void _onWiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);

        /** Handler for client password checking */
        bool _checkPassword(AsyncWebServerRequest *request);

        /** Webserver request handlers */
        void _onIndexReq(AsyncWebServerRequest *request);
        void _onGeoLocationReq(AsyncWebServerRequest *request);
        void _onEStopReq(AsyncWebServerRequest *request);
        void _onNotFoundReq(AsyncWebServerRequest *request);

    public:

        Junkbotix_Webserver();

        Position getLastClientPosition();

        void setCredentials(char* ssid, char* password);
        void setPort(int port);
        void setAddresses(IPAddress local_ip, IPAddress gateway, IPAddress subnet);
        void init();
};

#endif
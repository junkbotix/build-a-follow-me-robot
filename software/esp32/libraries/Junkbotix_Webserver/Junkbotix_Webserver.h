/*
    Junkbotix_Webserver.h - Web server library
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
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

        /** SoftAP default network settings (change these) */
        char* _ssid = "my-web-server";
        char* _password = "password12345";

        /** Default port for the async web server */
        int _port = 8080;

        /** Default IP Addresses */
        IPAddress _local_ip(192,168,1,100);
        IPAddress _gateway(192,168,1,1);
        IPAddress _subnet((255,255,255,0);

        AsyncWebServer _server;

        /** Client geolocation position array for running average??? */
        int _pcount = 0;
        Position _calcPosition;
        Position _rawPosition[10];
        
        boolean _eStopFlag = false;

        long _lastMillis = 0;

        /* Handlers for SoftAP startup and station connection */
        void _onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info);
        void _onWiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);

        /* Webserver request handlers */
        void _onIndexReq(AsyncWebServerRequest *request);
        void _onGeoLocationReq(AsyncWebServerRequest *request);
        void _onEStopReq(AsyncWebServerRequest *request);
        void _onNotFoundReq(AsyncWebServerRequest *request);

        void _calcRunningAverages();

    public:
        Junkbotix_Webserver();

        void setCredentials(char* ssid, char* password);
        void setPort(int port);
        void setAddresses(IPAddress local_ip, IPAddress gateway, IPAddress subnet);

        void init();

        void loop();


};

#endif
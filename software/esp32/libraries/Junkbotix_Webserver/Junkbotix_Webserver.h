/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Webserver.h - Web server library
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_Webserver_h
#define Junkbotix_Webserver_h

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include <Junkbotix_Common.h>

#include "pages/index_html.h"
#include "pages/e404_html.h"

// Response codes
#define AS_WEBSERVER_RESPONSE_OK            200
#define AS_WEBSERVER_RESPONSE_NOTFOUND      404

// Web server library
class Junkbotix_Webserver {
    private:
    
        // The Async Webserver
        static AsyncWebServer _server;

        // SoftAP default network credentials
        static char* _ssid;
        static char* _password;

        // Default port for the Async Webserver
        static int _port;

        // SoftAP default IP Addresses
        static IPAddress _localip;
        static IPAddress _gateway;
        static IPAddress _subnet;

        // Message to be sent to the client
        static String _lastClientMessage;
        static String _clientMessage;

        // Client geolocation position
        static Position _lastClientPosition;
        
        // Flags
        static bool _isConnected;
        static bool _isAPStarted;
        static bool _isEStopped;

        // Handlers for SoftAP startup and station connection
        static void _onWiFiAPStart(WiFiEvent_t event, WiFiEventInfo_t info);
        static void _onWiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);

        // Handler for client password checking
        static bool _checkPassword(AsyncWebServerRequest *request);

        // Web server request handlers
        static void _onIndexReq(AsyncWebServerRequest *request);
        static void _onGetMessageReq(AsyncWebServerRequest *request);
        static void _onGeoLocationReq(AsyncWebServerRequest *request);
        static void _onEStopReq(AsyncWebServerRequest *request);
        static void _onNotFoundReq(AsyncWebServerRequest *request);

    public:

        Junkbotix_Webserver();

        // Methods for checking the status of the flags
        bool isAPStarted();
        bool isConnected();
        bool isEStopped();

        // Set a message to be sent to the client (when requested)
        void setClientMessage(String message);

        // Return the last reported geolocation position of the client
        Position getLastClientPosition();

        // Set SoftAP network credentials
        void setCredentials(char* ssid, char* password);

        // Set the port for the Async Webserver
        void setPort(unsigned int port);
        
        // Set SoftAP default IP Addresses
        void setAddresses(String local_ip, String gateway, String subnet);
        
        // Initialize the SoftAP and Async Webserver
        void init();
};

#endif
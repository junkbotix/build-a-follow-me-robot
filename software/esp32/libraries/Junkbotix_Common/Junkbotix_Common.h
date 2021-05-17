/*
    Junkbotix_Common.h - Common library/class structures, defines, etc
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#ifndef Junkbotix_Common_h
#define Junkbotix_Common_h

/******************************************************************************/

/** GPIO for ESP32 on-board LED (pin 24) */
#define LED_BUILTIN                 2                   

/******************************************************************************/
/* Various default settings for Async Webserver
/******************************************************************************/

#define AS_WEBSERVER_SSID           "my-web-server" // Note: Please shange the SSID and
#define AS_WEBSERVER_PASSWORD       "password12345" // password to something better
#define AS_WEBSERVER_PORT           8080
#define AS_WEBSERVER_LOCALIP        "192.168.1.100"
#define AS_WEBSERVER_GATEWAY        "192.168.1.1"
#define AS_WEBSERVER_SUBNET         "255.255.255.0"

/******************************************************************************/
/* Password for client controller to use for access
/******************************************************************************/

#define CLIENT_PASSWORD             "password12345"

/******************************************************************************/

struct Position {
    float latitude;
    float longitude;
    float heading;
};

#endif
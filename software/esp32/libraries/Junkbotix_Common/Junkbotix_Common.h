/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Common.h - Common library/class structures, defines, etc
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_Common_h
#define Junkbotix_Common_h

// Define GPIO for ESP32 on-board LED (pin 24)
#define LED_BUILTIN                 2                   

/******************************************************************************/
/* Various default settings for Async Webserver
/* NOTE: Be sure to change the SSID and password to your own values!
/******************************************************************************/

#define AS_WEBSERVER_SSID           "my-web-server"
#define AS_WEBSERVER_PASSWORD       "password12345"
#define AS_WEBSERVER_PORT           8080
#define AS_WEBSERVER_LOCALIP        "192.168.1.100"
#define AS_WEBSERVER_GATEWAY        "192.168.1.1"
#define AS_WEBSERVER_SUBNET         "255.255.255.0"

/******************************************************************************/
/* Password for client controller to use for access
/* NOTE: Be sure to change the client password to your own value!
/******************************************************************************/

#define CLIENT_PASSWORD             "password12345"

// GPS Position parameters
struct Position {
    float latitude;
    float longitude;
    float heading;
};

static void debug_blink() {
    static long lastMillis = 0;
    static int ledState = LOW;

    // Simple blink-without-delay functionality to blink on-board LED for status
    if (millis() != lastMillis && millis() - lastMillis > 1000) {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, ledState);
        ledState = !ledState;
        lastMillis = millis();
    }
}

#endif
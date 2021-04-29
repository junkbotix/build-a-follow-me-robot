/*
    Junkbotix_Common.h - Common library/class structures, defines, etc
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#ifndef Junkbotix_Common_h
#define Junkbotix_Common_h

#define LED_BUILTIN     2   // pin 24 (controls ESP32 on-board LED)

struct Position {
    float latitude;
    float longitude;
    float heading;
};

#endif
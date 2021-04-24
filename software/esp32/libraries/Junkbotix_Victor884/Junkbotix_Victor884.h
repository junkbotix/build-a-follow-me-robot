/*
    Junkbotix_Victor884.h - Interface library for Victor-884 motor controllers
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#ifndef Junkbotix_Victor884_h
#define Junkbotix_Victor884_h

#include "Arduino.h"
#include <ESP32Servo.h>

#define V884_PERIOD         50

#define V884_MIN_PPM        800
#define V884_MAX_PPM        2200

#define V884_MIN_THROTTLE   0
#define V884_ZRO_THROTTLE   90
#define V884_MAX_THROTTLE   180

class Junkbotix_Victor884 {
    private:
        byte _gpio;

        byte _currentThrottle;

        byte _rampTo;
        long _rampMillis = 0;
        long _rampDelay;

        Servo _motor;

        void _initTimers();
        void _doThrottleRamp();

    public:
        Junkbotix_Victor884(byte gpio);
        
        void setThrottle(byte to);
        void setThrottleRamp(byte to, long delay);
        void loop();
};

#endif
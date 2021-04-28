/*
    Junkbotix_Beacons.cpp - Interface library for LED and audible beacons
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include "Arduino.h"
#include "Junkbotix_Beacons.h"

void Junkbotix_Beacons::loop() {
    // if (millis() != _rampMillis && millis() - _rampMillis > _rampDelay) {
    //     _doThrottleRamp();
    //     _rampMillis = millis();
    // }
}

Junkbotix_Beacons::Junkbotix_Beacons(byte gpio) {
    _gpio = gpio;
    pinMode(gpio, OUTPUT);
}
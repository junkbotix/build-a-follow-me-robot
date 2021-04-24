/*
    Junkbotix_Etrex.cpp - Interface library for the Garmin Etrex GPS (serial)
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include "Arduino.h"
#include "Junkbotix_Etrex.h"

void Junkbotix_Etrex::loop() {
    // if (millis() != _rampMillis && millis() - _rampMillis > _rampDelay) {
    //     _doThrottleRamp();
    //     _rampMillis = millis();
    // }
}

Junkbotix_Etrex::Junkbotix_Etrex(byte tx, byte rx) {
    _tx_gpio = tx;
    _rx_gpio = rx;
}
/*
    Junkbotix_Victor884.cpp - Interface library for Victor-884 motor controllers
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include "Arduino.h"
#include "Junkbotix_Victor884.h"

void Junkbotix_Victor884::_initTimers() {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);  
}

void Junkbotix_Victor884::_doThrottleRamp() {
    _motor.write(_currentThrottle);

    if (_currentThrottle < _rampTo) {
        _currentThrottle++;
    } else {
        _currentThrottle--;
    }
}

void Junkbotix_Victor884::setThrottle(byte to) {
    if (to >= V884_MIN_THROTTLE && to <= V884_MAX_THROTTLE) {
        _currentThrottle = to;
    } else {
        _currentThrottle = V884_ZRO_THROTTLE;
    }

    _motor.write(_currentThrottle);
}

void Junkbotix_Victor884::setThrottleRamp(byte to, long delay) {
    if (to >= V884_MIN_THROTTLE && to <= V884_MAX_THROTTLE) {
        _rampTo = to;
    } else {
        _rampTo = V884_ZRO_THROTTLE;
    }

    _rampDelay = delay;
}

void Junkbotix_Victor884::loop() {
    if (millis() != _rampMillis && millis() - _rampMillis > _rampDelay) {
        _doThrottleRamp();
        _rampMillis = millis();
    }
}

Junkbotix_Victor884::Junkbotix_Victor884(byte gpio) {
    _gpio = gpio;

    _initTimers();
    
    _motor.setPeriodHertz(V884_PERIOD);
    _motor.attach(_gpio, V884_MIN_PPM, V884_MAX_PPM);
    _motor.write(V884_ZRO_THROTTLE);
}
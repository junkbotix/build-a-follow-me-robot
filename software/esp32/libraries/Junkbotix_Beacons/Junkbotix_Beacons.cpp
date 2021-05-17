/**
 * Junkbotix_Beacons.cpp - Interface library for LED and audible beacons
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Junkbotix_Beacons.h"

/**
 * Empty constructor
 */
Junkbotix_Beacons::Junkbotix_Beacons() {}

/**
 * Setup and turn off the beacon
 */
void Junkbotix_Beacons::init() {
    pinMode(_settings.gpio, OUTPUT);

    if (_settings.mode == BEACON_TOGGLE) {
        digitalWrite(_settings.gpio, LOW);
    } else {
        /** Setup the beacon pin for PWM control (breathing) */
        ledcSetup(BEACON_PWM_CHANNEL, BEACON_PWM_FREQUENCY, BEACON_PWM_RESOLUTION);
        ledcAttachPin(_settings.gpio, BEACON_PWM_CHANNEL);
        ledcWrite(BEACON_PWM_CHANNEL, 0);
    }
}

/**
 * Initialize the beacon with custom settings
 * @param settings
 */
void Junkbotix_Beacons::init(BeaconSettings settings) {
    _settings = settings;
    init();
}

/**
 * Reset a defined "one-shot" beacons
 */
void Junkbotix_Beacons::reset() {
    if (_settings.oneshot) {
        _settings.state = (_settings.mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
    }
}

/**
 * Blink or flash a beacon (based on defined settings)
 * 
 * Note: Blinking has a longer "dwell-time" than a flash
 */
void Junkbotix_Beacons::blink() {
    _tick();
}

/**
 * Make a beacon "breath" (based on defined settings)
 * 
 * Note: Breathing performs a linear ramp from fully-off to 
 * fully-on, then back to fully-off (repeating cycle)
 */
void Junkbotix_Beacons::breath() {
    _settings.mode = BEACON_BREATH;
    _tick();
}

/** Implementation of the non-blocking beacon state-machine process */
void Junkbotix_Beacons::_tick() {
    static int ticks = _settings.count;
    static int state = (_settings.mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
    static int pwm = 0;
    long delay;
    
    switch (state) {
        case BEACON_ON:
            delay = _settings.ondelay;              /**< milliseconds to stay on */
            digitalWrite(_settings.gpio, HIGH);
            break;

        case BEACON_OFF:
            delay = _settings.offdelay;             /**< milliseconds to stay off */
            digitalWrite(_settings.gpio, LOW);
            break;

        case BEACON_FADEIN:
            ledcWrite(BEACON_PWM_CHANNEL, pwm);
            delay = _settings.ondelay;              /**< milliseconds to stay on */
            break;

        case BEACON_FADEOUT:
            ledcWrite(BEACON_PWM_CHANNEL, pwm);
            delay = _settings.offdelay;             /**< milliseconds to stay off */
            break;

        case BEACON_PAUSED:
            if (_settings.oneshot) return;          /**< one-shots only cycle once, until reset */
            delay = _settings.pausedelay;           /**< milliseconds to pause */
            break;
    }

    if (millis() != _lastMillis && millis() - _lastMillis > delay) {
        switch (state) {
            case BEACON_ON:
                state = BEACON_OFF;
                break;

            case BEACON_OFF:
                ticks--;
                if (ticks <= 0) {
                    state = BEACON_PAUSED;
                } else {
                    state = BEACON_ON;
                }
                break;

            case BEACON_FADEIN:
                pwm += _settings.step;
                if (pwm >= 255) {
                    pwm = 255;
                    state = BEACON_FADEOUT;
                }
                break;

            case BEACON_FADEOUT:
                pwm -= _settings.step;
                if (pwm <= 0) {
                    pwm = 0;
                    ticks--;
                    if (ticks <= 0) {
                        state = BEACON_PAUSED;
                    } else {
                        state = BEACON_FADEIN;
                    }
                }
                break;

            case BEACON_PAUSED:
                ticks = _settings.count;
                state = (_settings.mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
                break;
        }
        
        _lastMillis = millis();
    }
}
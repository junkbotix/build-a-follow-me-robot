/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Beacons.cpp - Interface library for LED and audible beacons
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include <Junkbotix_Beacons.h>

/******************************************************************************/
/* Private Methods
/******************************************************************************/

// Setup the hardware GPIO and turn off the beacon
void Junkbotix_Beacons::_initHardware() {
    pinMode(_gpio, OUTPUT);
    if (_mode == BEACON_TOGGLE) {
        digitalWrite(_gpio, LOW);
    } else {
        // Setup the beacon pin for PWM control (breathing)
        ledcSetup(BEACON_PWM_CHANNEL, BEACON_PWM_FREQUENCY, BEACON_PWM_RESOLUTION);
        ledcAttachPin(_gpio, BEACON_PWM_CHANNEL);
        ledcWrite(BEACON_PWM_CHANNEL, 0);
    }
}

// Implementation of the non-blocking beacon state-machine control process
void Junkbotix_Beacons::_tick() {
    static int reps = _repeat;
    static int pwm = 0;
    long delay;
    
    switch (_state) {
        case BEACON_ON:
            delay = _ondelay;                       /**< milliseconds to stay on */
            digitalWrite(_gpio, HIGH);
            break;

        case BEACON_OFF:
            delay = _offdelay;                      /**< milliseconds to stay off */
            digitalWrite(_gpio, LOW);
            break;

        case BEACON_FADEIN:
            ledcWrite(BEACON_PWM_CHANNEL, pwm);
            delay = _ondelay;                       /**< milliseconds to wait between steps when fading in */
            break;

        case BEACON_FADEOUT:
            ledcWrite(BEACON_PWM_CHANNEL, pwm);
            delay = _offdelay;                      /**< milliseconds to wait between steps when fading out */
            break;

        case BEACON_PAUSED:
            if (_oneshot) return;                   /**< a one-shot only happens once, until it is reset */
            delay = _pausedelay;                    /**< milliseconds to pause */
            break;
    }

    if (millis() != _lastMillis && millis() - _lastMillis > delay) {
        switch (_state) {
            case BEACON_ON:
                _state = BEACON_OFF;
                break;

            case BEACON_OFF:
                reps--;
                if (reps <= 0) {
                    _state = BEACON_PAUSED;
                } else {
                    _state = BEACON_ON;
                }
                break;

            case BEACON_FADEIN:
                pwm += _step;
                if (pwm >= 255) {
                    pwm = 255;
                    _state = BEACON_FADEOUT;
                }
                break;

            case BEACON_FADEOUT:
                pwm -= _step;
                if (pwm <= 0) {
                    pwm = 0;
                    reps--;
                    if (reps <= 0) {
                        _state = BEACON_PAUSED;
                    } else {
                        _state = BEACON_FADEIN;
                    }
                }
                break;

            case BEACON_PAUSED:
                reps = _repeat;
                _state = (_mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
                break;
        }
        
        _lastMillis = millis();
    }
}

/******************************************************************************/
/* Public Methods
/******************************************************************************/

/**
 * Set the GPIO for the beacon and initialize the hardware
 * 
 * @param gpio GPIO pin number for the beacon
 * @param mode BEACON_TOGGLE for blinking/flashing, BEACON_BREATH for breathing beacon
 * @param oneshot set to true for a beacon that cycles once
 */
void Junkbotix_Beacons::setGPIO(unsigned int gpio, unsigned int mode, bool oneshot) {
    _gpio = gpio || LED_BUILTIN;
    _mode = mode || BEACON_TOGGLE;
    _state = (_mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
    _oneshot = oneshot;
    _initHardware();
}

/**
 * Set the number of repeated beacon actions per cycle
 * 
 * @param repeat Number of times to blink/flash/breath per cycle
 */
void Junkbotix_Beacons::setRepeat(unsigned int repeat) { 
    _repeat = repeat;
}

/**
 * Set the beacon PWM step value
 * 
 * @param step Value to increase/decrease PWM value by for each tick (BEACON_BREATH mode)
 */
void Junkbotix_Beacons::setStep(unsigned int step) { 
    _step = step;
}

/**
 * Set the beacon delay values
 * 
 * @param ondelay Number of milliseconds for: beacon to stay "on" (BEACON_TOGGLE mode) or to wait between ticks when fading in (BEACON_BREATH mode)
 * @param offdelay Number of milliseconds for: beacon to stay "off" (BEACON_TOGGLE mode) or to wait between ticks when fading out (BEACON_BREATH mode)
 * @param pausedelay Number of milliseconds for beacon to pause after a full on/off cycle
 */
void Junkbotix_Beacons::setDelays(unsigned int ondelay, unsigned int offdelay, unsigned int pausedelay) { 
    _ondelay = ondelay;
    _offdelay = offdelay;
    _pausedelay = pausedelay;
}

/**
 * Reset the state of a "one-shot" beacon to allow another cycle
 */
void Junkbotix_Beacons::reset() {
    if (_oneshot) {
        _state = (_mode == BEACON_TOGGLE) ? BEACON_ON : BEACON_FADEIN;
    }
}

/**
 * Blink or flash the beacon (based on defined settings)
 * 
 * Note: Blinking has a longer "dwell-time" than a flash
 */
void Junkbotix_Beacons::blink() {
    _mode = BEACON_TOGGLE;
    _tick();
}

/**
 * Make the beacon "breath" (based on defined settings)
 * 
 * Note: Breathing performs a linear ramp from fully-off to fully-on, then back to fully-off (repeating cycle)
 */
void Junkbotix_Beacons::breath() {
    _mode = BEACON_BREATH;
    _tick();
}

Junkbotix_Beacons::Junkbotix_Beacons() {
    _gpio = LED_BUILTIN;
    _mode = BEACON_TOGGLE;
    _state = BEACON_ON;
    _repeat = 1;
    _step = 1;
    _ondelay = 500;
    _offdelay = 500;
    _pausedelay = 0;
    _oneshot = false;

    _initHardware();
}
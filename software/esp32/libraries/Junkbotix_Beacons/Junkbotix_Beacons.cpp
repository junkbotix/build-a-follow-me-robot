/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Beacons.cpp - Interface library for LED and audible beacons
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include <Junkbotix_Beacons.h>
#include <Junkbotix_Beacon_Style.h>

/******************************************************************************/
/* Public Methods
/******************************************************************************/

// Turn the beacon off
void Junkbotix_Beacons::off() {
    ledcWrite(_channel, 0);
}

// Reset the state of a "one-shot" beacon to allow another cycle
void Junkbotix_Beacons::reset() {
    _state = _style.getOneshot() ? BEACON_FADEIN : _state;
}

// Returns true if the beacon is a one-shot and it's cycle is complete and over
bool Junkbotix_Beacons::isShot() {
    return (_state == BEACON_SHOT);
}

// Returns true if the beacon is currently "paused" in it's cycle
bool Junkbotix_Beacons::isPaused() {
    return (_state == BEACON_PAUSED);
}

// Implementation method for the non-blocking beacon state-machine control process
void Junkbotix_Beacons::tick(Junkbotix_Beacon_Style style) {
    _style = style;
    tick();
}

void Junkbotix_Beacons::tick() {

    static long lastMillis = 0;
    static int reps = _style.getRepeat();
    static int pwm = 0;
    long delay;
    
    switch (_state) {
        case BEACON_FADEIN:
            ledcWrite(_channel, pwm);
            delay = _style.getOnDelay();            // milliseconds to wait between steps when fading in
            break;

        case BEACON_FADEOUT:
            ledcWrite(_channel, pwm);
            delay = _style.getOffDelay();           // milliseconds to wait between steps when fading out
            break;

        case BEACON_PAUSED:
            // a one-shot only happens once, until it is reset
            _state = _style.getOneshot() ? BEACON_FADEIN : _state;
            delay = _style.getPauseDelay();         // milliseconds to pause
            break;
        
        case BEACON_SHOT:                           // break intentionally omitted
        default:
            return;
    }

    if (millis() != lastMillis && millis() - lastMillis > delay) {
        lastMillis = millis();

        switch (_state) {
            case BEACON_FADEIN:
                pwm += _style.getStep();
                if (pwm >= 255) {
                    pwm = 255;
                    _state = BEACON_FADEOUT;
                }
                break;

            case BEACON_FADEOUT:
                pwm -= _style.getStep();
                if (pwm <= 0) {
                    pwm = 0;
                    if (reps <= 0) {
                        _state = BEACON_PAUSED;
                    } else {
                        _state = BEACON_FADEIN;
                    }
                    reps--;
                }
                break;

            case BEACON_PAUSED:
                reps = _style.getRepeat();
                _state = BEACON_FADEIN;
                break;
        }
    }
}

Junkbotix_Beacons::Junkbotix_Beacons(unsigned int gpio = LED_BUILTIN, unsigned int channel = BEACON_PWM_CHANNEL) {

    _gpio = gpio;
    _channel = channel;
    _state = BEACON_FADEIN;

    // Setup the hardware GPIO and turn off the beacon
    pinMode(_gpio, OUTPUT);

    // Setup the beacon pin for PWM control (breathing)
    ledcSetup(_channel, BEACON_PWM_FREQUENCY, BEACON_PWM_RESOLUTION);
    ledcAttachPin(_gpio, _channel);
    ledcWrite(_channel, 0);
}
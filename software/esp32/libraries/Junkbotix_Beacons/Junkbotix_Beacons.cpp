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
    _curr_state = _style.getOneshot() ? BEACON_FADEIN : _curr_state;
}

// Returns true if the beacon is a one-shot and it's cycle is complete and over
bool Junkbotix_Beacons::isShot() {
    return (_curr_state == BEACON_SHOT);
}

// Returns true if the beacon is currently "paused" in it's cycle
bool Junkbotix_Beacons::isPaused() {
    return (_curr_state == BEACON_PAUSED);
}

/**
 * Wrapper method for the non-blocking beacon state-machine control process
 * 
 * @param style Junkbotix_Beacon_Style style object defining the style for the beacon
 */
void Junkbotix_Beacons::tick(Junkbotix_Beacon_Style style) {
    _style = style;
    tick();
}

// Implementation method for the non-blocking beacon state-machine stepping control process
void Junkbotix_Beacons::tick() {

    if (millis() != _lastMillis && millis() - _lastMillis > _delay) {

        _curr_state = _next_state;

        _lastMillis = millis();

        switch (_curr_state) {

            case BEACON_INIT:
                _reps = _style.getRepeat();
                _next_state = BEACON_FADEIN;
                break;

            case BEACON_FADEIN:
                _delay = _style.getOnDelay();            // milliseconds to wait between steps when fading in
                _pwm += _style.getStep();
                if (_pwm >= 255) {
                    _pwm = 255;
                    _next_state = BEACON_FADEOUT;
                }
                ledcWrite(_channel, _pwm);
                break;

            case BEACON_FADEOUT:
                _delay = _style.getOffDelay();           // milliseconds to wait between steps when fading out
                _pwm -= _style.getStep();
                if (_pwm <= 0) {
                    _pwm = 0;
                    _reps--;
                    if (_reps <= 0) {
                        _next_state = BEACON_PAUSED;
                    } else {
                        _next_state = BEACON_FADEIN;
                    }
                }
                ledcWrite(_channel, _pwm);
                break;

            case BEACON_PAUSED:
                _delay = _style.getPauseDelay();         // milliseconds to pause
                _reps = _style.getRepeat();
    
                // a one-shot only happens once, until it is reset
                _next_state = _style.getOneshot() ? BEACON_SHOT : BEACON_FADEIN;
    
                break;

            case BEACON_SHOT:                           
                // break intentionally omitted
    
            default:
                return;
        }
    }
}

/**
 * Constructor to instantiate the beacon object, setting the GPIO pin and PWM channel to use
 * 
 * @param gpio GPIO pin attached to the beacon (default = LED_BUILTIN)
 * @param channel PWM channel for the beacon (default = BEACON_PWM_CHANNEL)
 */
Junkbotix_Beacons::Junkbotix_Beacons(unsigned int gpio = LED_BUILTIN, unsigned int channel = BEACON_PWM_CHANNEL) {

    _gpio = gpio;
    _channel = channel;
    
    // Setup the hardware GPIO and turn off the beacon
    pinMode(_gpio, OUTPUT);

    // Setup the beacon pin for PWM control (breathing)
    ledcSetup(_channel, BEACON_PWM_FREQUENCY, BEACON_PWM_RESOLUTION);
    ledcAttachPin(_gpio, _channel);
    ledcWrite(_channel, 0);
}
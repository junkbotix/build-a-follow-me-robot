/**
 * Junkbotix_Beacons.h - Interface library for LED and audible beacons
 * Copyright (c) 2021 by Junkbotix 
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html 
 */

#ifndef Junkbotix_Beacons_h
#define Junkbotix_Beacons_h

#include "Arduino.h"
#include <Junkbotix_Common.h>

/** Beacon PWM settings */
#define BEACON_PWM_FREQUENCY    1000
#define BEACON_PWM_CHANNEL      0
#define BEACON_PWM_RESOLUTION   8

/** Beacon mode definitions */
#define BEACON_TOGGLE           1
#define BEACON_BREATH           2
#define BEACON_HALTED           4

/** Beacon state definitions */
#define BEACON_ON               1 
#define BEACON_OFF              2
#define BEACON_FADEIN           4
#define BEACON_FADEOUT          8
#define BEACON_PAUSED           16

/** Settings */
struct BeaconSettings {
    int gpio;           /**< GPIO beacon is defined for */
    int mode;           /**< toggled or "breathing" */
    int state;          /**< current state of beacon state machine */

    /**
     * A cycle is defined as the number of fully-on to fully-off 
     * transitions a beacon performs before it repeats, after a  
     * pause (between each cycle) 
     */

    int count;          /**< number of blinks or flashes per cycle */
    int step;           /**< increment/decrement amount for pwm */
    
    long ondelay;       /**< how long to stay turned on */
    long offdelay;      /**< how long to stay turned off */
    long pausedelay;    /**< how long to wait between each fully-on/fully-off cycle */
    bool oneshot;       /**< if set true, only does one cycle */
};

/** Class definition */
class Junkbotix_Beacons {
    private:
        /** Default settings */
        BeaconSettings _settings = {
            gpio: LED_BUILTIN, 
            mode: BEACON_TOGGLE,
            state: BEACON_ON, 
            count: 1, 
            step: 1, 
            ondelay: 500, 
            offdelay: 500, 
            pausedelay: 0,
            oneshot: false
        };

        long _lastMillis;

        void _tick();

    public:
        Junkbotix_Beacons();

        void init();
        void init(BeaconSettings settings);

        void reset();

        void blink();
        void breath();
};

#endif
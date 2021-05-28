/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Beacons.h - Interface library for LED and audible beacons
 * Copyright (c) 2021 by Junkbotix 
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html 
 */

#ifndef Junkbotix_Beacons_h
#define Junkbotix_Beacons_h

#include <Arduino.h>
#include <Junkbotix_Common.h>

// Beacon PWM settings
#define BEACON_PWM_FREQUENCY    1000
#define BEACON_PWM_CHANNEL      0
#define BEACON_PWM_RESOLUTION   8

// Beacon mode definitions
#define BEACON_TOGGLE           0x01
#define BEACON_BREATH           0x02
#define BEACON_HALTED           0x04

// Beacon state definitions
#define BEACON_ON               0x01
#define BEACON_OFF              0x02
#define BEACON_FADEIN           0x04
#define BEACON_FADEOUT          0x08
#define BEACON_PAUSED           0x10

// Interface library for LED and audible beacons
class Junkbotix_Beacons {
    private:
        unsigned int _gpio;
        unsigned int _mode;
        unsigned int _state;
        unsigned int _repeat;
        unsigned int _step;
        unsigned int _ondelay;
        unsigned int _offdelay;
        unsigned int _pausedelay;
        bool _oneshot;

        long _lastMillis;

        void _initHardware();
        void _tick();

    public:
        Junkbotix_Beacons();

        void setGPIO(unsigned int gpio, unsigned int mode, bool oneshot);
        void setRepeat(unsigned int repeat);
        void setStep(unsigned int step);
        void setDelays(unsigned int ondelay, unsigned int offdelay, unsigned int pausedelay);

        void reset();
        void blink();
        void breath();
};

#endif
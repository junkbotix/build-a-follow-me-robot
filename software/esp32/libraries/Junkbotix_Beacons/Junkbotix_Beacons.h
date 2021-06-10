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
#include <Junkbotix_Beacon_Style.h>

// Beacon PWM settings
#define BEACON_PWM_FREQUENCY    10000
#define BEACON_PWM_CHANNEL      0
#define BEACON_PWM_RESOLUTION   8

// Beacon state definitions
#define BEACON_FADEIN           0x01
#define BEACON_FADEOUT          0x02
#define BEACON_PAUSED           0x04
#define BEACON_SHOT             0x08

// Interface library for LED and audible beacons
class Junkbotix_Beacons {
    
    private:

        Junkbotix_Beacon_Style _style;

        unsigned int _gpio;
        unsigned int _channel;
        unsigned int _mode;
        unsigned int _state;
        unsigned int _repeat;
        unsigned int _step;
        unsigned int _ondelay;
        unsigned int _offdelay;
        unsigned int _pausedelay;
                bool _oneshot;


    public:

        void off();
        void reset();
        bool isShot();
        bool isPaused();

        void tick(Junkbotix_Beacon_Style style);
        void tick();

        Junkbotix_Beacons(unsigned int gpio, unsigned int channel);
};

#endif
/*
    Junkbotix_Beacons.h - Interface library for LED and audible beacons
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#ifndef Junkbotix_Beacons_h
#define Junkbotix_Beacons_h

#include "Arduino.h"

class Junkbotix_Beacons {
    private:
        byte _gpio;

    public:
        Junkbotix_Beacons(byte gpio);

        void loop();
};

#endif
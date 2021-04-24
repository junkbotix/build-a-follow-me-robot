/*
    Junkbotix_Etrex.h - Interface library for the Garmin Etrex GPS (serial)
    Copyright (c) 2021 by Junkbotix
    Licensed under the GNU Public License (GPL) Version 3
    http://www.gnu.org/licenses/gpl-3.0.en.html
*/

#ifndef Junkbotix_Etrex_h
#define Junkbotix_Etrex_h

#include "Arduino.h"

class Junkbotix_Etrex {
    private:
        byte _tx_gpio;
        byte _rx_gpio;

    public:
        Junkbotix_Etrex(byte tx, byte rx);

        void loop();
};

#endif
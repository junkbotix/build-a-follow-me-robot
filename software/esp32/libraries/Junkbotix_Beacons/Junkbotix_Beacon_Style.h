/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Beacon_Style.h - Interface library for beacon styling
 * Copyright (c) 2021 by Junkbotix 
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html 
 */

#ifndef Junkbotix_Beacon_Style_h
#define Junkbotix_Beacon_Style_h

#include <Arduino.h>
#include <Junkbotix_Common.h>

// Interface library for beacon styling
class Junkbotix_Beacon_Style {
    
    private:

        String _name;
        unsigned int _repeat;
        unsigned int _step;
        unsigned int _ondelay;
        unsigned int _offdelay;
        unsigned int _pausedelay;
        bool _oneshot;

    public:

        void setName(String name);
        void setRepeat(unsigned int repeat);
        void setStep(unsigned int step);
        void setOnDelay(unsigned int ondelay);
        void setOffDelay(unsigned int offdelay);
        void setPauseDelay(unsigned int pausedelay);
        void setOneshot(bool oneshot);

        String getName();
        unsigned int getRepeat();
        unsigned int getStep();
        unsigned int getOnDelay();
        unsigned int getOffDelay();
        unsigned int getPauseDelay();
        bool getOneshot();

        Junkbotix_Beacon_Style();
};

#endif
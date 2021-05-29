/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Robot.h - Class to model the robot
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_Robot_h
#define Junkbotix_Robot_h

#include <Junkbotix_Common.h>

// Model of the robot
class Junkbotix_Robot {
    private:
        int _state;

        Position _position;

    public:
        Junkbotix_Robot(int state);

        void halt();
        
        void setState(int state);
        int getState();

        void setPosition(float latitude, float longitude, float heading);
        Position getPosition();
};

#endif
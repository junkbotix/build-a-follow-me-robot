/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Client.h - Class to model the client
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#ifndef Junkbotix_Client_h
#define Junkbotix_Client_h

#include <Junkbotix_Common.h>

// Model of the client
class Junkbotix_Client {
    private:
        Position _position;

    public:
        Junkbotix_Client();

        void setPosition(float latitude, float longitude, float heading);
        Position getPosition();
};

#endif
/**
 * Build A "Follow-Me" Robot: Part 11 - Software
 *
 * Junkbotix_Client.cpp - Class to model the client
 * Copyright (c) 2021 by Junkbotix
 * Licensed under the GNU Public License (GPL) Version 3
 * http://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "Arduino.h"
#include "Junkbotix_Client.h"

Junkbotix_Client::Junkbotix_Client() {}

void Junkbotix_Client::setPosition(float latitude, float longitude, float heading) {
    _position = {latitude, longitude, heading};
}

Position Junkbotix_Client::getPosition() {
    return _position;
}